#ifndef GPIO_H
#define GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>
#include <system_error>

/**
 * @brief The GPIO class represents a GPIO interface.
 * 
 * This class provides methods to control the state of LEDs connected to GPIO pins.
 */
class GPIO
{
    public:
        /**
         * @brief Constructs a GPIO object.
         * 
         * @param devfile The path to the device file.
         */
        GPIO(const char* devfile);

        /**
         * @brief Destroys the GPIO object.
         */
        ~GPIO();

        /**
         * @brief Sets the state of LED1.
         * 
         * @param state The state to set (0 for off, 1 for on).
         */
        void setLed1(int state);

        /**
         * @brief Sets the state of LED2.
         * 
         * @param state The state to set (0 for off, 1 for on).
         */
        void setLed2(int state);
        /**
         * @brief Checks if the GPIO object is valid.
         * 
         * @return true if the GPIO object is valid, false otherwise.
         */
        bool isValid() { return is_initialized; }

    private:
        int fd; ///< The file descriptor for the GPIO device.
        struct gpiohandle_request leds; ///< The GPIO handle request structure.
        struct gpiohandle_data led_state; ///< The GPIO handle data structure.
        bool is_initialized; // Tracks whether GPIO initialization was successful
};


#endif // GPIO_H
