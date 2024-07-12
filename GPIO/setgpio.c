#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

int main() {

    int fd;
    struct gpiohandle_request led, button;
    struct gpiohandle_data data;

    // Open the GPIO device
    fd = open("/dev/gpiochip0", O_RDWR);
    if (fd < 0) {
        perror("erro opening gpiochip0");
        return -1;
    }

    //set the led
    led.flags = GPIOHANDLE_REQUEST_OUTPUT;
    strcpy(led.consumer_label, "led");
    memset(led.lines, 0, sizeof(led.default_values));
    led.lines = 1;
    led.lineoffsets[0] = 16; // GPIO16

    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &led) < 0) {
        perror("error requesting GPIO line for led");
        return -1;
    }


    //set the button

    button.flags = GPIOHANDLE_REQUEST_INPUT;
    strcpy(button.consumer_label, "button");
    memset(button.lines, 0, sizeof(button.default_values));
    button.lines = 1;
    button.lineoffsets[0] = 20; // GPIO20

    if (ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &button) < 0) {
        perror("error requesting GPIO line for button");
        close(led.fd);
        close(fd);
        return -1;
    }

    // SET the led to 1
    data.values[0] = 1;
    if(ioctl(led.fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data) < 0) {
        perror("error setting GPIO line value");
    }

    // Wait for the button to be pressed
    printf("Press the button to turn off the led\n");
    while(1) {
        if (ioctl(button.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data) < 0) {
            perror("error getting GPIO line value");
            break;
        }
        if (data.values[0] == 0) {
            break;
        }
    }


    return 0;
}