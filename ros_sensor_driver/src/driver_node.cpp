#include "ros/ros.h"
#include "std_msgs/String.h"
#include "JetsonGPIO.h"

#define MOTOR_PWM 12
#define MOTOR_DIR 26


void driveCallback(const std_msgs::String::ConstPtr& msg)
{

}

int main(int argc, char **argv)
{
    // Setup GPIO
    GPIO::setmode(GPIO::BCM);
    GPIO::setup(MOTOR_PWM, GPIO::OUT);
    GPIO::setup(MOTOR_DIR, GPIO::OUT, GPIO::HIGH);

    GPIO::PWM motor(MOTOR_PWM, 100);

    // Setup ROS
    ros::init(argc, argv, "driver");
    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("drive", 1000, driveCallback);
    ros::Rate loop_rate(10);
    
    int power = 0;
    while (ros::ok())
    {
        motor.start(power);
        loop_rate.sleep();
        if (power > 99) {
            power = 0;
        }
        else {power++;}
    }

    GPIO::cleanup();
    return 0;
}