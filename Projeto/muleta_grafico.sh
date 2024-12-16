#!/bin/sh
ARQUIVODADOS=/home/pi/muleta_dados.txt
ARQUIVOSAIDA=/home/pi/muleta_dados.png

gnuplot << EOF
set title "Medidas coletadas no Arduino"
set ylabel "Valor [V]"
set xlabel "Tempo [s]"
set terminal png
set output "$ARQUIVOSAIDA"

plot "$ARQUIVODADOS" \
     linecolor rgb '#0060ad' \
     linetype 1 \
     linewidth 2 \
     pointtype 2 \
     pointsize 3.0 \
     title "Medidas dos valores de tensão da Ponte de Wheatstone" \
     with linespoints
EOF
