#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/**
 * @brief Sends and receives data through UART communication.
 * 
 * This program opens the UART device file "/dev/serial0" and sends a message
 * "Hello from Raspberry Pi!" through UART at a baud rate of 9600. It then waits
 * for 10 seconds and reads the data received from the UART.
 * 
 * @return 0 on success, -1 on error.
 */
int main() {

    int fd,len;

    char text[255];
    struct termios options; /* serial ports settings*/

    // Open the UART device file
    fd = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd < 0) {
        perror("Error - Unable to open UART");
        return -1;
    }

    // Setup the serial port settings
    tcgetattr(fd, &options);

    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;

    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    // Send data through UART
    strcpy(text, "Hello from Raspberry Pi!\n");
    len = write(fd, text, strlen(text));
    printf("Sent %d bytes\n", len);

    printf("Have 10 seconds to read the data sent from the UART\n");
    sleep(10);

    // Read data from UART
    memset(text, 0, sizeof(text));
    len = read(fd, text, sizeof(text));
    printf("Received %d bytes: %s\n", len, text);

    // Close the UART device file
    close(fd);
    return 0;
}