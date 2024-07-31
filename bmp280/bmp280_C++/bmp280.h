#ifndef BMP280_H
#define BMP280_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>

class BMP280 {
    public:
        BMP280();
        ~BMP280();
        int init_bmp280(const char *i2c_bus);
        float read_temperature();
    private:
        int i2c_bus;
        uint16_t dig_T1, dig_T2, dig_T3;
        int read_byte_data(uint8_t reg,uint8_t *value );
        int read_word_data(uint8_t reg,uint16_t *value );    
};

#endif // BMP280_H