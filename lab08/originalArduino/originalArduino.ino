const int analogInPin = A0;            // o potenciômetro esta ligado ao pino A0
int iniciaColeta,intervalo_coleta, aumenta, diminui = 0;
long now, antes;
int t=0, atraso=100;

char charRecebido;                     // cria uma variavel para armazenar o caractere recebido

void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
}

void loop(){
   if (Serial.available()){            // verifica se recebeu algum comando
      charRecebido = Serial.read();    // le o caractere recebido
      switch ( charRecebido ){
          case 'i':                    // inicia coleta
             iniciaColeta = 1;
             break;

          case 'p':                    // para a coleta
             iniciaColeta = 0;
             break;

          case 'g':                    // para a intervalo
             Serial.write(t & 0xFF);          // envia byte menos significativo
             Serial.write(t >> 8);            // envia byte mais significativo
             break;

          case 'h':                    // para a intervalo
             atraso += 10;
             break;

          case 'j':                    // para a intervalo
             atraso -= 10;
             break;

          default:                     // outro comando, ignora...
             break;
      }
   }
   if ( iniciaColeta == 1 ){
       int valor = analogRead(analogInPin); // le valor no pino A0 usando conversor ADC de 10-bit
       now = millis();
       t = now - antes;
       antes = now;
       Serial.write(valor & 0xFF);          // envia byte menos significativo
       Serial.write(valor >> 8);            // envia byte mais significativo
   }

   delay(atraso);                          // aguarda 100ms
}
