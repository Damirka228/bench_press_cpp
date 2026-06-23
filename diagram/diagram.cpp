#include <iostream>
#include "../calculator/calculator.h"
#include "../database/database.h"
#include "diagram.h"
#include <vector>
#include <fstream>
using namespace std;

void Diagram :: ShowDiagram(vector<Train>showTrain) {
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        for (Train t : showTrain) {
            outFile << t.date << " " << t.weight << " " << t.max_weight << endl;
        }
        outFile.close();
        cout << "Файл успешно создан и заполнен!" << endl;
    } else {
        cerr << "Не удалось создать файл." << endl;
    }
    
    ofstream plotFile("plot.gp");
    plotFile << "set terminal qt size 900,500" << endl;
    plotFile << "set title 'Прогресс жима лёжа' font ',14'" << endl;
    plotFile << "set xlabel 'Тренировка'" << endl;
    plotFile << "set ylabel 'кг'" << endl;
    plotFile << "set grid" << endl;
    plotFile << "set style fill solid 0.9" << endl;
    plotFile << "set boxwidth 0.5 relative" << endl;
    plotFile << "set yrange [0:*]" << endl;
    plotFile << "plot 'data.txt' using 0:2:xtic(1) with boxes lc rgb '#3d6fbb' title 'Вес штанги', \\" << endl;
    plotFile << "     'data.txt' using 0:3 with linespoints lc rgb '#e07040' pt 7 ps 1.5 lw 2 dt 2 title 'Максимум'" << endl;
    plotFile.close();
    
    system("gnuplot -persistent plot.gp");
}