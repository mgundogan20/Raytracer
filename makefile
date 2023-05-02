all: main
	./main
	rm main.o

main: main.o
	g++ main.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ main.cpp -c
