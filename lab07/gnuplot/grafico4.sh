#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados4.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-6-2024C/lab07/gnuplot/dados4.png

gnuplot << EOF
set title "Quase senoidal"
set ylabel "Y"
set xlabel "X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#0033ff' \
     linetype 2 \
     linewidth 6 \
     pointtype 4 \
     pointsize 5.0 \
     title "Legenda" \
     with linespoints
EOF

