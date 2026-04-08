//UART driver v2 code
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main() {
    int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);
    if (fd == -1) {
        perror("open_port: Unable to open /dev/ttyUSB0");
        return 1;
    }

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    tcsetattr(fd, TCSANOW, &options);

    char buf[] = "Hello UART\n";
    write(fd, buf, sizeof(buf));

    close(fd);
    return 0;
}
