#include "driver_node.h"

#define MOTOR_PWM 12
#define MOTOR_DIR 26

Driver::Driver()
{
    power = 0;
    // Setup GPIO
    GPIO::setmode(GPIO::BCM);
    GPIO::setup(MOTOR_PWM, GPIO::OUT);
    GPIO::setup(MOTOR_DIR, GPIO::OUT, GPIO::HIGH);

    motor = new GPIO::PWM(MOTOR_PWM, 100);


    up_proc = new Programs::CountUp(&power);
    //down_proc = new Programs::CountDown(&power);
    sense_proc = new Programs::GetSensor(&power);

    sched.add_process(up_proc);
    sched.add_process(sense_proc);
    //sched.add_process(down_proc);
    sched.select_next_process();


}


void Driver::run()
{
    ros::Rate loop_rate(10);
    while (ros::ok())
    {
        motor->start(power);
        ros::spinOnce();
        sched.run();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        ROS_INFO("%i", power);
    }
}

void Driver::driveCallback(const std_msgs::Int32::ConstPtr& msg)
{
    //power = Sense::drive(msg->data, proc);
    ROS_INFO("CallBack detected!");
    sched.run();
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "driver");
    ros::NodeHandle node;

    Driver *driver = new Driver();

    ros::Subscriber sub = node.subscribe("drive", 1000, &Driver::driveCallback, driver);

    driver->run();

    driver->sched.cleanup();
    GPIO::cleanup();
    return 0;
}