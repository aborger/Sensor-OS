#include "programs.h"



Programs::CountUp::CountUp(int* i) {
    power = i;
}

void Programs::CountUp::run_func() {
    while (true) {
        //std::cout << "current up process progress: " << *power << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        *power += 1;
        sleep();
    }
}

Programs::CountDown::CountDown(int* i) {
    power = i;
}

void Programs::CountDown::run_func() {
    while (true) {
        std::cout << "current down process progress: " << *power << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        *power -= 1;
        sleep();
    }
}
