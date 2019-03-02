# Makefile
CXX_FLAG = --std=c++11 -g


all: main.o cards.o utility.o
	g++ $(CXX_FLAG) -o game main.o cards.o utility.o

tests: tests.o
	g++ $(CXX_FLAG) -o tests tests.o cards.o utility.o

tests.o: 
	g++ -c $(CXX_FLAG) tests.cpp cards.cpp utility.cpp

cards.o: cards.cpp
	g++ -c $(CXX_FLAG) cards.cpp

main.o: main.cpp
	g++ -c $(CXX_FLAG) main.cpp 

utility.o: utility.cpp
	g++ -c $(CXX_FLAG) utility.cpp

clean:
	rm -f game *.o
