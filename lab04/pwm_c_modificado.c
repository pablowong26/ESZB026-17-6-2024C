#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <fcntl.h>   // Para open()
#include <termios.h> // Para configuração da porta serial
#include <unistd.h>  // Para read()
#include <stdlib.h>  // Para atoi()

#define BUFFER_SIZE 10
#define ARDUINO_MAX 1023
#define PWM_MAX 100

// Função para mapear valores de um intervalo para outro
int map(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int main() {
   int file;
   if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY)) < 0) {
      perror("UART: Falha ao abrir o arquivo.\n");
      return -1;
   }

   struct termios options;             // cria estruturas para configurar a comunicacao
   tcgetattr(file, &options);          // ajusta os parametros do arquivo
   options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
   options.c_iflag = IGNPAR;
   options.c_oflag = 0;
   options.c_lflag = 0;
   tcflush(file, TCIFLUSH);
   tcsetattr(file, TCSANOW, &options);

   int pino_PWM = 23;                  // pwm por software na GPIO23
   int brilho = 0;
   int brilho_mapeado = 0;
   char buffer[BUFFER_SIZE];
   int n;

   wiringPiSetupGpio();                // usar a numeracao GPIO, nao WPi
   pinMode(pino_PWM, OUTPUT);          // configura GPIO23 como saida
   softPwmCreate(pino_PWM, 0, PWM_MAX);  // inicializa PWM por software

   while (1) {
      // Tenta ler dados da porta serial
      n = read(file, buffer, BUFFER_SIZE - 1);
      
      if (n > 0) {
         buffer[n] = '\0';  // Adiciona terminador nulo
         brilho = atoi(buffer);  // Converte string para inteiro
         
         // Garante que o brilho esteja dentro do intervalo válido
         if (brilho < 0) brilho = 0;
         if (brilho > ARDUINO_MAX) brilho = ARDUINO_MAX;
         
         // Mapeia o valor do Arduino (0-1023) para o range do PWM (0-100)
         brilho_mapeado = map(brilho, 0, ARDUINO_MAX, 0, PWM_MAX);
         
         // Aplica o novo valor de brilho
         softPwmWrite(pino_PWM, brilho_mapeado);
         
         printf("Valor do Arduino: %d, Brilho mapeado: %d\n", brilho, brilho_mapeado);
      }
      
      delay(100);  // Pequeno delay para evitar uso excessivo da CPU
   }

   close(file);
   return 0;
}
