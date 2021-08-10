#include "process.h"

namespace Programs {

    class CountUp: public Sense::Process
    {
        public:
            int* power;
            CountUp(int* i);
            void run_func();
    };
    class CountDown: public Sense::Process
    {
        public:
            int* power;
            CountDown(int* i);
            void run_func();
    };
}