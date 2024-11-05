#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h> 
#include <stdlib.h> 

int main(){
   int file, count;
   if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Falha ao abrir o arquivo.\n");
      return -1;
   }
   
   struct termios options;             
   tcgetattr(file, &options); 
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   
   tcflush(file, TCIFLUSH);            
   tcsetattr(file, TCSANOW, &options);
                  
   int pino_PWM = 23;                         // pwm por software na GPIO23
   int brilho;
   int range = 100;  // periodo do PWM = 100us*range
	
   wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
   pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
   softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
   
   
   while (1) {
   unsigned char receive[100];               
   if ((count = read(file, (void*)receive, 100))<0){        
      perror("Falha ao ler da entrada\n");
      return -1;
   }
   softPwmWrite (pino_PWM, brilho);
   
}

close(file);
return 0;

}
