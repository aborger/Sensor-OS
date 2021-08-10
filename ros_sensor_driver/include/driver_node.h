#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "JetsonGPIO.h"
#include "scheduler.h"
#include "process.h"
#include "programs.h"
#include "I2C_program.h"

class Driver
{
    public:
        Driver();
        ~Driver();

        void driveCallback(const std_msgs::Int32::ConstPtr& msg);
        void run();

        Programs::CountUp* up_proc;
        Programs::CountDown* down_proc;
        Programs::GetSensor* sense_proc;

        int power;
        Sense::Scheduler sched;

    private:
        GPIO::PWM *motor;

};