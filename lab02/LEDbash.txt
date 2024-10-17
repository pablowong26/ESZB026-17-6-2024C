#!/bin/bash

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

RED_GPIO=20     # GPIO para LED vermelho
GREEN_GPIO=21   # GPIO para LED verde
YELLOW_GPIO=16  # GPIO para LED amarelo

# Funções Bash
function setLED {
    echo $1 > "/sys/class/gpio/gpio$2/value"
}

# Habilitar GPIOs
echo "$RED_GPIO" > "/sys/class/gpio/export"
echo "$GREEN_GPIO" > "/sys/class/gpio/export"
echo "$YELLOW_GPIO" > "/sys/class/gpio/export"
sleep 1  # Esperar um segundo para garantir que as GPIOs foram exportadas
echo "out" > "/sys/class/gpio/gpio$RED_GPIO/direction"
echo "out" > "/sys/class/gpio/gpio$GREEN_GPIO/direction"
echo "out" > "/sys/class/gpio/gpio$YELLOW_GPIO/direction"

# Sequência de LEDs
for i in {1..5}; do
    echo "Acendendo LED vermelho"
    setLED 1 $RED_GPIO  # Acender LED vermelho
    sleep 2             # Esperar 2 segundos

    echo "Desligando LED vermelho"
    setLED 0 $RED_GPIO  # Desligar LED vermelho

    echo "Acendendo LED verde"
    setLED 1 $GREEN_GPIO  # Acender LED verde
    sleep 1               # Esperar 1 segundo

    echo "Desligando LED verde"
    setLED 0 $GREEN_GPIO  # Desligar LED verde

    echo "Acendendo LED amarelo (vermelho + verde)"
    setLED 1 $YELLOW_GPIO  # Acender LED amarelo
    sleep 1                # Esperar 1 segundo

    echo "Desligando LED amarelo"
    setLED 0 $YELLOW_GPIO   # Desligar LED amarelo
done

# Desabilitar GPIOs
echo "$RED_GPIO" > "/sys/class/gpio/unexport"
echo "$GREEN_GPIO" > "/sys/class/gpio/unexport"
echo "$YELLOW_GPIO" > "/sys/class/gpio/unexport"
