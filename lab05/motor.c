#include <stdio.h>
#include <wiringPi.h>

#define pino_PWM0 18                    // o PWM sera acionado na GPIO18

int main() {                            // este programa deve ser rodado com 'sudo'
   int dc, ciclos;
   wiringPiSetupGpio();                 // usa a numeracao da GPIO
   pinMode(pino_PWM0, PWM_OUTPUT);      // configura a GPIO18 com o PWM por hardware

   // Ajustando a frequencia do PWM em 10kHz com 128 passos de duty cycle
   // frequencia PWM = 19,2 MHz / (divisor * range)
   // 261.6 = 19200000 / (divisor * range) => divisor = 15
   pwmSetMode(PWM_MODE_MS);             // usando frequencia fixa
   pwmSetRange(128);                    // passos do duty cycle (max=4096)
   pwmSetClock(573); 
   // fornece uma frequencia de 10kHz (max=4096)
   printf("Iniciando...\n");
   dc = 3;
   
 for(ciclos = 0; ciclos < 2; ciclos++){ 
      pwmWrite(pino_PWM0, dc);
      usleep(300000);
      pwmWrite(pino_PWM0, 0);
      usleep(600000);
      pwmWrite(pino_PWM0, dc);
      usleep(300000);
      pwmWrite(pino_PWM0, 0);
      usleep(600000);
      pwmWrite(pino_PWM0, dc);
      usleep(300000);
      pwmWrite(pino_PWM0, 0);
      usleep(600000);
}
      
   printf("Fim.\n");
   return 0; 
}
