TARGET = main
SOURCES = main.cpp calculator/calculator.cpp database/database.cpp diagram/diagram.cpp auth/auth.cpp
FLAGS = -lsqlite3 -lssl -lcrypto -I/opt/homebrew/include -L/opt/homebrew/lib

all:
	g++ $(SOURCES) -o $(TARGET) $(FLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)