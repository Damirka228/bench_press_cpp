# bench_press_cpp
#компиляция:
g++ main.cpp calculator/calculator.cpp database/database.cpp diagram/diagram.cpp auth/auth.cpp -o main -lsqlite3 -lssl -lcrypto -I/opt/homebrew/include -L/opt/homebrew/lib
#запуск:
./main


sqlite3
gnuplot
OpenSSL
