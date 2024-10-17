#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para usleep

#define RED_GPIO "20"
#define GREEN_GPIO "21"
#define YELLOW_GPIO "16"
#define GPIO4_PATH "/sys/class/gpio/gpio"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]) {
    FILE *fp; // cria um ponteiro fp
    fp = fopen(filename, "w+"); // abre o arquivo para escrita
    fprintf(fp, "%s", value); // grava o valor no arquivo
    fclose(fp); // fecha o arquivo
}

void setupGPIO(char *gpio_number) {
    writeGPIO(GPIO_SYSFS "export", gpio_number);
    usleep(100000); // aguarda 100 ms
    writeGPIO(GPIO4_PATH gpio_number "/direction", "out");
}

void closeGPIO(char *gpio_number) {
    writeGPIO(GPIO_SYSFS "unexport", gpio_number);
}

int main() {
    // Configurando os GPIOs
    setupGPIO(RED_GPIO);
    setupGPIO(GREEN_GPIO);
    setupGPIO(YELLOW_GPIO);

    // Sequência de LEDs
    for (int i = 0; i < 5; i++) {
        printf("Acendendo LED vermelho\n");
        writeGPIO(GPIO4_PATH RED_GPIO "/value", "1"); // Acender LED vermelho
        usleep(2000000); // Esperar 2 segundos
        writeGPIO(GPIO4_PATH RED_GPIO "/value", "0"); // Desligar LED vermelho

        printf("Acendendo LED verde\n");
        writeGPIO(GPIO4_PATH GREEN_GPIO "/value", "1"); // Acender LED verde
        usleep(1000000); // Esperar 1 segundo
        writeGPIO(GPIO4_PATH GREEN_GPIO "/value", "0"); // Desligar LED verde

        printf("Acendendo LED amarelo\n");
        writeGPIO(GPIO4_PATH YELLOW_GPIO "/value", "1"); // Acender LED amarelo
        usleep(1000000); // Esperar 1 segundo
        writeGPIO(GPIO4_PATH YELLOW_GPIO "/value", "0"); // Desligar LED amarelo
    }

    // Fechando GPIOs
    closeGPIO(RED_GPIO);
    closeGPIO(GREEN_GPIO);
    closeGPIO(YELLOW_GPIO);

    printf("Fim do programa em C.\n");
    return 0;
}
