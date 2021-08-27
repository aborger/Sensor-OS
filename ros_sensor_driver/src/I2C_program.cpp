#include "I2C_program.h"


Programs::GetSensor::GetSensor(int* _power) {
    if ((bus = i2c_open("/dev/i2c-1")) == -1) {
        std::cout << "Error!" << std::endl;
        exit(-4);        
    } else {std::cout << "Initiated bus!" << std::endl;}

    memset(&device, 0, sizeof(device));
    i2c_init_device(&device);

    device.bus = bus;
    device.addr = 0x8;
    device.iaddr_bytes = 0;
    device.page_bytes = 16;
    power = _power;
}

int Programs::GetSensor::read_int() {
    unsigned char buf[1];
    size_t buf_size = sizeof(buf);
    ssize_t ret = 0;
    ret = i2c_ioctl_read(&device, 0x0, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {
        std::cout << "Error Reading!" << std::endl;
        exit(-5);
    }
    return (int)buf[0];    
}

void Programs::GetSensor::write_bool(int val) {
    unsigned char buf[1];
    size_t buf_size = sizeof(buf);
    if (val == 0) {buf[0] = 0x0;}
    if (val == 1) {buf[0] = 0x1;}

    ssize_t ret = 0;

    ret = i2c_write(&device, 0x0, buf, buf_size);
    if (ret != 1 || (size_t)ret != buf_size)
    {
        std::cout << "Error Writing: ret:" << ret << "ret_size: " << (size_t)ret << "buf_size: " << buf_size << std::endl;
        exit(-4);
    }    
}

void Programs::GetSensor::run_func() {
    while (true) {
        write_bool(1);
        int ans = read_int();
        if (ans == 1)
        {
            *power = 0;
        }
        std::cout << "Button State: " << ans << std::endl;
        write_bool(0);
        sleep();
    }
}

void Programs::GetSensor::close_process() {
    i2c_close(bus);
}