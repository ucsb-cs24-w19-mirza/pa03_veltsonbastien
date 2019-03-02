# Makefile
CXX_FLAG = --std=c++11 -g


all: main.o cards.o 
	g++ $(CXX_FLAG) -o game main.o cards.o 

tests: tests.o
	g++ $(CXX_FLAG) -o tests tests.o cards.o 

tests.o: 
	g++ -c $(CXX_FLAG) tests.cpp cards.cpp

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp 

clean:
	rm -f game *.o
