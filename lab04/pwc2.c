
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 20
#define ARDUINO_MAX 1023
#define PWM_MAX 100

int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
    int file;
    if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
        perror("UART: Falha ao abrir o arquivo.\n");
        return -1;
    }

    struct termios options;
    tcgetattr(file, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(file, TCIFLUSH);
    tcsetattr(file, TCSANOW, &options);

    int pino_PWM = 23;
    int brilho = 0;
    int brilho_mapeado = 0;
    char buffer[BUFFER_SIZE];
    int n;

    wiringPiSetupGpio();
    pinMode(pino_PWM, OUTPUT);
    softPwmCreate(pino_PWM, 0, PWM_MAX);

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        n = read(file, buffer, BUFFER_SIZE - 1);
        
        if (n > 0) {
            buffer[n] = '\0';
            brilho = atoi(buffer);
            
            if (brilho >= 0 && brilho <= ARDUINO_MAX) {
                brilho_mapeado = map(brilho, 0, ARDUINO_MAX, 0, PWM_MAX);
                softPwmWrite(pino_PWM, brilho_mapeado);
                printf("Valor do Arduino: %d, Brilho mapeado: %d\n", brilho, brilho_mapeado);
            }
        }
        
        delay(10);
    }

    close(file);
    return 0;
}
