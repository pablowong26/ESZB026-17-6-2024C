
#!/usr/bin/python3

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

import sys
from time import sleep

# Definindo os caminhos GPIO
#LED_PATH = "/sys/class/gpio/gpio16/"
#LED_PATH21 = "/sys/class/gpio/gpio21/"
#LED_PATH20 = "/sys/class/gpio/gpio20/"

RED_GPIO = "20"
GREEN_GPIO = "21"
YELLOW_GPIO = "16"

SYSFS_DIR = "/sys/class/gpio/"

def writeGPIO (gpio_number, value, path = SYSFS_DIR ):
   with open(f"{SYSFS_DIR}gpio{gpio_number}/value", "w") as fo:
   fo.write(value)

def setupGPIO(gpio_number):
        with open(f"{SYSFS_DIR}export", "w") as fo:
        fo.write(gpio_number)
    sleep(0.1)  # Aguarda um momento para garantir que o GPIO foi exportado
    with open(f"{SYSFS_DIR}gpio{gpio_number}/direction", "w") as fo:
        fo.write("out")

def closeGPIO(gpio_number):
        with open(f"{SYSFS_DIR}unexport", "w") as fo:
        fo.write(gpio_number)

# Configurando os GPIOs
setupGPIO(RED_GPIO)
setupGPIO(GREEN_GPIO)
setupGPIO(YELLOW_GPIO)

# Sequência de LEDs
for i in range(5):
    print("Acendendo LED vermelho")
    writeGPIO(RED_GPIO, "1")  # Acender LED vermelho
    sleep(2)                   # Esperar 2 segundos
    writeGPIO(RED_GPIO, "0")  # Desligar LED vermelho

    print("Acendendo LED verde")
    writeGPIO(GREEN_GPIO, "1")  # Acender LED verde
    sleep(1)                     # Esperar 1 segundo
    writeGPIO(GREEN_GPIO, "0")  # Desligar LED verde

    print("Acendendo LED amarelo")
    writeGPIO(YELLOW_GPIO, "1")  # Acender LED amarelo
    sleep(1)                      # Esperar 1 segundo
    writeGPIO(YELLOW_GPIO, "0")  # Desligar LED amarelo

# Fechando GPIOs
closeGPIO(RED_GPIO)
closeGPIO(GREEN_GPIO)
closeGPIO(YELLOW_GPIO)

print("Fim do script Python.")
