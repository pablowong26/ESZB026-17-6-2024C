#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h> // Para usleep

using namespace std;

#define RED_GPIO "20"
#define GREEN_GPIO "21"
#define YELLOW_GPIO "16"
#define GPIO_PATH "/sys/class/gpio/gpio"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(string path, string filename, string value) {
    fstream fs;
    fs.open((path + filename).c_str(), fstream::out);
    fs << value;
    fs.close();
}

void setupGPIO(string gpio_number) {
    writeGPIO(string(GPIO_SYSFS), "export", gpio_number);
    usleep(100000); // Aguarda 100 ms
    writeGPIO(string(GPIO_PATH) + gpio_number + "/", "direction", "out");
}

void closeGPIO(string gpio_number) {
    writeGPIO(string(GPIO_SYSFS), "unexport", gpio_number);
}

int main() {
    // Configurando os GPIOs
    setupGPIO(RED_GPIO);
    setupGPIO(GREEN_GPIO);
    setupGPIO(YELLOW_GPIO);

    // Sequência de LEDs
    for (int i = 0; i < 5; i++) {
        cout << "Acendendo LED vermelho" << endl;
        writeGPIO(string(GPIO_PATH) + RED_GPIO + "/", "value", "1"); // Acender LED vermelho
        usleep(2000000); // Esperar 2 segundos
        writeGPIO(string(GPIO_PATH) + RED_GPIO + "/", "value", "0"); // Desligar LED vermelho

        cout << "Acendendo LED verde" << endl;
        writeGPIO(string(GPIO_PATH) + GREEN_GPIO + "/", "value", "1"); // Acender LED verde
        usleep(1000000); // Esperar 1 segundo
        writeGPIO(string(GPIO_PATH) + GREEN_GPIO + "/", "value", "0"); // Desligar LED verde

        cout << "Acendendo LED amarelo" << endl;
        writeGPIO(string(GPIO_PATH) + YELLOW_GPIO + "/", "value", "1"); // Acender LED amarelo
        usleep(1000000); // Esperar 1 segundo
        writeGPIO(string(GPIO_PATH) + YELLOW_GPIO + "/", "value", "0"); // Desligar LED amarelo
    }

    // Fechando GPIOs
    closeGPIO(RED_GPIO);
    closeGPIO(GREEN_GPIO);
    closeGPIO(YELLOW_GPIO);

    cout << "Fim do programa em C++." << endl;
    return 0;
}
