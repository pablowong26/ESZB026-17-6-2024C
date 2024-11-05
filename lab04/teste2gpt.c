#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <wiringPi.h>
#include <softPwm.h> 
#include <stdlib.h> 

int main(){
   int file, count;
   struct termios options;             // cria estruturas para configurar a comunicacao
   
   if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Falha ao abrir o arquivo.\n");
      return -1;
   }
   
   tcgetattr(file, &options);          // ajusta os parametros do arquivo
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   // ignora erros de paridade
   tcflush(file, TCIFLUSH);            // descarta informacao no arquivo
   tcsetattr(file, TCSANOW, &options); // aplica alteracoes imediatamente
   
   unsigned char receive[100];         // cria um buffer para receber os dados
   if ((count = read(file, (void*)receive, 100))<0){        // recebe os dados
      perror("Falha ao ler da entrada\n");
      return -1;
   }
                  
   int pino_PWM = 23;                         // pwm por software na GPIO23
   int brilho;
   int range = 100;  // periodo do PWM = 100us*range
	
   wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
   pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
   softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
   count = atoi((char*)receive); 
   brilho = count;
   while (1) {
      for (brilho = 0; brilho < range; brilho++) {
         softPwmWrite (pino_PWM, brilho); // altera o duty cycle do PWM
         delay (10) ;                     // aguarda 10ms
      }
      for (brilho = range; brilho > 0; brilho--) {
         softPwmWrite (pino_PWM, brilho);
         delay (10);
      }
   }
   return 0;
}
