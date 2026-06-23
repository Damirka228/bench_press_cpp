set terminal qt size 900,500
set title 'Прогресс жима лёжа' font ',14'
set xlabel 'Тренировка'
set ylabel 'кг'
set grid
set style fill solid 0.9
set boxwidth 0.5 relative
set yrange [0:*]
plot 'data.txt' using 0:2:xtic(1) with boxes lc rgb '#3d6fbb' title 'Вес штанги', \
     'data.txt' using 0:3 with linespoints lc rgb '#e07040' pt 7 ps 1.5 lw 2 dt 2 title 'Максимум'
