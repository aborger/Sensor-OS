#include "i2c/i2c.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "ros/ros.h"

void write_bool(int val, I2CDevice* device) {

    unsigned char buf[1];
    size_t buf_size = sizeof(buf);
    if (val == 0) {buf[0] = 0x0;}
    if (val == 1) {buf[0] = 0x1;}

    ssize_t ret = 0;

    ret = i2c_ioctl_write(device, 0x0, buf, buf_size);
    if (ret != 1 || (size_t)ret != buf_size)
    {
        std::cout << "Error Writing: ret:" << ret << "ret_size: " << (size_t)ret << "buf_size: " << buf_size << std::endl;
        exit(-4);
    }
}

int read_bool(I2CDevice* device)
{
    unsigned char buf[1];
    size_t buf_size = sizeof(buf);
    ssize_t ret = 0;
    ret = i2c_ioctl_read(device, 0x0, buf, buf_size);
    if (ret == -1 || (size_t)ret != buf_size)
    {
        std::cout << "Error Reading!" << std::endl;
        exit(-5);
    }
    return (int)buf[0];
}

int main(int argc, char **argv)
{
    int bus;
    if ((bus = i2c_open("/dev/i2c-1")) == -1) {
        std::cout << "Error!" << std::endl;
        exit(-4);
    }
    std::cout << "Initiated bus..." << std::endl;

    I2CDevice device;
    memset(&device, 0, sizeof(device));
    i2c_init_device(&device);

    device.bus = bus;
    device.addr = 0x8;
    device.iaddr_bytes = 0;
    device.page_bytes = 16;

    while (true) {
        int input;
        std::cout << "Input: ";
        std::cin >> input;

        write_bool(input, &device);
        int ans = read_bool(&device);
        std::cout << "answer: " << ans << std::endl;
    }


    i2c_close(bus);
    return 0;
}