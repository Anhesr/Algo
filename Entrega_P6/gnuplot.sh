#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "grafico.eps"
set key left top
set xlabel "Queens Number"
set ylabel "Time Spent"
plot 'Datos.txt' using 1:2 t "Real Time" w l, 'Datos.txt' using 1:3 t "Estimated Time" w l
_end_
