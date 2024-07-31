#include "bmp280.h"

BMP280::BMP280() : i2c_bus(-1), dig_T1(0), dig_T2(0), dig_T3(0) {}

BMP280::~BMP280() {
    if (i2c_bus != -1) {
        close(i2c_bus);
    }
}

int BMP280::init_bmp280(const char *i2c_bus_path) {
    if ((i2c_bus = open(i2c_bus_path, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        return -1;
    }

    if (ioctl(i2c_bus, I2C_SLAVE, 0x76) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        return -1;
    }

    // Read calibration data
    if (read_word_data(0x88, &dig_T1) < 0 ||
        read_word_data(0x8A, &dig_T2) < 0 ||
        read_word_data(0x8C, &dig_T3) < 0) {
        return -1;
    }

    return 0;
}

float BMP280::read_temperature() {
    int32_t adc_T;
    uint8_t msb, lsb, xlsb;

    if (read_byte_data(0xFA, &msb) < 0 ||
        read_byte_data(0xFB, &lsb) < 0 ||
        read_byte_data(0xFC, &xlsb) < 0) {
        return -1;
    }

    adc_T = ((int32_t)msb << 12) | ((int32_t)lsb << 4) | ((int32_t)xlsb >> 4);

    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
    T = var1 + var2;
    float temperature = (T * 5 + 128) >> 8;
    return temperature / 100.0;
}

int BMP280::read_byte_data(uint8_t reg, uint8_t *value) {
    if (write(i2c_bus, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        return -1;
    }
    if (read(i2c_bus, value, 1) != 1) {
        perror("Failed to read from the i2c bus");
        return -1;
    }
    return 0;
}

int BMP280::read_word_data(uint8_t reg, uint16_t *value) {
    uint8_t data[2];
    if (write(i2c_bus, &reg, 1) != 1) {
        perror("Failed to write to the i2c bus");
        return -1;
    }
    if (read(i2c_bus, data, 2) != 2) {
        perror("Failed to read from the i2c bus");
        return -1;
    }
    *value = (data[1] << 8) | data[0];
    return 0;
}