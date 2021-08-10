#include "i2c/i2c.h"
#include <string.h>
#include "process.h"

namespace Programs {
    class GetSensor: public Sense::Process
    {
        public:
            GetSensor();
            void run_func();
            void close_process();
        private:
            int read_int();
            void write_bool(int val);
            int bus;
            I2CDevice device;
    };
}