const int analogInPin = A0;  // Potenciômetro está ligado ao pino A0
int iniciaColeta = 0;
int t = 0;
long now, antes = 0;
int intervalo_coleta = 100; // Intervalo padrão de 100ms
char charRecebido;  // Armazena o caractere recebido

void setup() {
  // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  if (Serial.available()) {  // Verifica se recebeu algum comando
    charRecebido = Serial.read();  // Lê o caractere recebido
    switch (charRecebido) {
      case 'i':  // Inicia coleta
        iniciaColeta = 1;
        break;

      case 'p':  // Para a coleta
        iniciaColeta = 0;
        break;

      case 'g':  // Solicita o intervalo de coleta atual
        Serial.println(intervalo_coleta);  // Envia o intervalo atual
        break;

      case 'u':  // Aumenta a taxa de coleta (diminui o intervalo)
        intervalo_coleta = max(10, intervalo_coleta - 10);  // Diminui intervalo até o mínimo de 10ms
        break;

      case 'd':  // Diminui a taxa de coleta (aumenta o intervalo)
        intervalo_coleta += 10;  // Aumenta intervalo em 10ms
        break;

      default:  // Outro comando, ignora...
        break;
    }
  }

  if (iniciaColeta == 1) {
    int valor = analogRead(analogInPin);  // Lê valor no pino A0 usando conversor ADC de 10-bit
    now = millis();
    t = now - antes;
    antes = now;
    Serial.write(valor & 0xFF);  // Envia byte menos significativo
    Serial.write(valor >> 8);   // Envia byte mais significativo
  }

  delay(intervalo_coleta);  // Aguarda o intervalo de coleta atual
}
