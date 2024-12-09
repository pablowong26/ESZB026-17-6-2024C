#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5 import QtGui, QtWidgets, QtCore
import pyqtgraph as pg
import numpy as np
import serial
import atexit
import time

def inicia_coleta():
    conexaoSerial.write(b'i')

def para_coleta():
    conexaoSerial.write(b'p')

def solicita_intervalo():
    conexaoSerial.write(b'g')
    if conexaoSerial.inWaiting():
        # Leia a resposta do Arduino
        intervalo = conexaoSerial.readline().decode('utf-8').strip()
        # Atualize o texto no gráfico
        intervalo_texto.setText(f"Intervalo: {intervalo}ms")

def aumenta_taxa():
    conexaoSerial.write(b'u')

def diminui_taxa():
    conexaoSerial.write(b'd')

def saindo():
    conexaoSerial.write(b'p')
    print('Saindo')

def update():
    global data1, curve1, x_atual, npontos, previousTime
    if conexaoSerial.inWaiting() > 1:
        dado1 = conexaoSerial.read()
        dado2 = conexaoSerial.read()
        novodado = float((ord(dado1) + ord(dado2) * 256.0) * 5.0 / 1023.0)

        data1[x_atual] = novodado
        data1[(x_atual + 1) % npontos] = np.nan
        x_atual += 1
        if x_atual >= npontos:
            x_atual = 0

        curve1.setData(data1, connect="finite")
        actualTime = time.time() * 1000
        taxa = str(round(actualTime - previousTime))
        previousTime = actualTime
        texto.setText(f"Taxa: {taxa.zfill(3)}ms")

app = QtWidgets.QApplication(sys.argv)

# Configuração da janela principal
win = QtWidgets.QWidget()
win.setWindowTitle('Coletando dados do Arduino via Porta Serial')
layout = QtWidgets.QVBoxLayout()

# Plot do gráfico
plot_widget = pg.PlotWidget()
plot_widget.setYRange(0, 5, padding=0)
layout.addWidget(plot_widget)

npontos = 800
x_atual = 0
data1 = np.zeros(npontos)
curve1 = plot_widget.plot(data1)
previousTime = time.time() * 1000
texto = pg.TextItem(text="", color=(255, 255, 0), anchor=(0, 1))
plot_widget.addItem(texto)
texto.setPos(0, 0)

# Intervalo de medição
intervalo_texto = pg.TextItem(text="", color=(0, 255, 255), anchor=(1, 1))
plot_widget.addItem(intervalo_texto)
intervalo_texto.setPos(npontos - 1, 5)

# Layout de botões
button_layout = QtWidgets.QHBoxLayout()

# Inicia
botao_inicia = QtWidgets.QPushButton('Inicia')
botao_inicia.clicked.connect(inicia_coleta)
button_layout.addWidget(botao_inicia)

# Para
botao_para = QtWidgets.QPushButton('Para')
botao_para.clicked.connect(para_coleta)
button_layout.addWidget(botao_para)

# Intervalo
botao_intervalo = QtWidgets.QPushButton('Intervalo')
botao_intervalo.clicked.connect(solicita_intervalo)
button_layout.addWidget(botao_intervalo)

# Aumenta Taxa
botao_aumenta = QtWidgets.QPushButton('Diminui Taxa')
botao_aumenta.clicked.connect(aumenta_taxa)
button_layout.addWidget(botao_aumenta)

# Diminui Taxa
botao_diminui = QtWidgets.QPushButton('Aumenta Taxa')
botao_diminui.clicked.connect(diminui_taxa)
button_layout.addWidget(botao_diminui)

# Adiciona layout de botões ao layout principal
layout.addLayout(button_layout)
win.setLayout(layout)

# Configuração da conexão serial
conexaoSerial = serial.Serial('/dev/ttyACM0', 115200)

# Inicia timer
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(0)

atexit.register(saindo)

# Executa o aplicativo
win.show()
sys.exit(app.exec_())
