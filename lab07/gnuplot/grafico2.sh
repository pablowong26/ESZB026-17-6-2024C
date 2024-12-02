#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados2.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados2.png

gnuplot << EOF
set title "Parábola"
set ylabel "Número quadrado"
set xlabel "Número"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#fffff00' \
     linetype 1 \
     linewidth 1 \
     pointtype 2 \
     pointsize 1.0 \
     title "meus dados" \
     with linespoints
EOF

