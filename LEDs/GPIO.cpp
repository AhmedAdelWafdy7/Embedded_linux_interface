#include "GPIO.h"

/**
 * @brief Constructs a GPIO object with the specified device file.
 *
 * This constructor opens the device file specified by `devfile` and initializes the GPIO handle
 * for controlling the GPIO lines. It sets the request parameters for the GPIO handle, including
 * the consumer label, default values, number of lines, line offsets, and flags. It also requests
 * the GPIO handle using the `GPIO_GET_LINEHANDLE_IOCTL` ioctl.
 *
 * @param devfile The path to the device file.
 * @throws std::system_error if the device file fails to open or if the GPIO handle request fails.
 */
GPIO::GPIO(const char* devfile)
{
    // Open the device file
    fd = open(devfile, O_RDWR);
    if (fd < 0)
    {
        throw std::system_error(errno, std::system_category(), "Failed to open device file");
    }

    // Set the request parameters for the GPIO handle
    strcpy(leds.consumer_label, "cp2112_leds");
    memset(leds.default_values,1,sizeof(leds.default_values));
    leds.lines = 2;
    leds.lineoffsets[0] = 0;
    leds.lineoffsets[1] = 1;
    leds.default_values[0] = 0;
    leds.default_values[1] = 0;
    leds.flags = GPIOHANDLE_REQUEST_OUTPUT;

    // Request the GPIO handle
    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &leds) < 0)
    {
        throw std::system_error(errno, std::system_category(), "Failed to request GPIO handle");
        close(fd);
    }
    led_state.values[0] = 1;
    led_state.values[1] = 1;
}

GPIO::~GPIO()
{
    // Close the device file
    close(leds.fd);
    close(fd);
}


void GPIO::setLed1(int state)
{
    led_state.values[0] = state;
    if (ioctl(leds.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &led_state) < 0)
    {
        throw std::system_error(errno, std::system_category(), "Failed to set LED1 state");
    }
}

void GPIO::setLed2(int state)
{
    led_state.values[1] = state;
    if (ioctl(leds.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &led_state) < 0)
    {
        throw std::system_error(errno, std::system_category(), "Failed to set LED2 state");
    }
}

