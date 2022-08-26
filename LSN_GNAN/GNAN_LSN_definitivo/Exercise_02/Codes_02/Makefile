CC = g++
CFLAGS = -Wall -03 --std=c++11

EXECUTABLES = es02.1 es02.2

all:
		make $(EXECUTABLES)
        
es02.1: es02.1.o random.o Integrali.o Blocks.o
	$(CC) es02.1.o random.o Integrali.o Blocks.o -o $@

es02.1.o: es02.1.cpp 
	$(CC) -c es02.1.cpp -o $@

es02.2: es02.2.o random.o Blocks.o position.o RandomWalk.o
	$(CC) es02.2.o random.o Blocks.o position.o RandomWalk.o -o $@

es02.2.o: es02.2.cpp
	$(CC) -c es02.2.cpp -o $@

Integrali.o: Integrali.cpp 
	$(CC) -c Integrali.cpp -o $@

random.o: ../Generatore/random.cpp ../Generatore/random.h
	$(CC) -c ../Generatore/random.cpp -o $@

Blocks.o: Blocks.cpp Blocks.h 
	$(CC) -c Blocks.cpp -o $@

RandomWalk.o: RandomWalk.cpp RandomWalk.h
	$(CC) -c RandomWalk.cpp -o $@

position.o: position.cpp position.h 
	$(CC) -c position.cpp -o $@