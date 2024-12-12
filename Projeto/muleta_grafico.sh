#!/bin/sh
ARQUIVODADOS=/home/pi/muleta_dados.txt
ARQUIVOSAIDA=/home/pi/muleta_dados.png

gnuplot << EOF
set title "Medidas coletadas do potenciometro no Arduino"
set ylabel "Valor [V]"
set xlabel "Tempo [s]"
set terminal png
set output "$ARQUIVOSAIDA"

plot "$ARQUIVODADOS" \
     linecolor rgb '#0060ad' \
     linetype 2 \
     linewidth 5 \
     pointtype 4 \
     pointsize 3.0 \
     title "Medidas dos valores de tensão da Ponte de Wheatstone" \
     with linespoints
EOF
