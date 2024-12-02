#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados3.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados3.png

gnuplot << EOF
set title "Módulo"
set ylabel "Y"
set xlabel "X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#ff0000' \
     linetype 2 \
     linewidth 2 \
     pointtype 3 \
     pointsize 5.0 \
     title "Legenda" \
     with linespoints
EOF

