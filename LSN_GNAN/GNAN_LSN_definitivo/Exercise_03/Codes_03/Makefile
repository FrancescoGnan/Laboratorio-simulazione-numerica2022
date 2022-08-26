CC = g++
CFLAGS = -Wall -03 --std=c++11

EXECUTABLES = es03.1 es03.2

all:
		make $(EXECUTABLES)
        
es03.1: es03.1.o random.o Blocks.o
	$(CC) es03.1.o random.o Blocks.o -o $@

es03.1.o: es03.1.cpp
	$(CC) -c es03.1.cpp -o $@

es03.2: es03.2.o random.o Blocks.o
	$(CC) es03.2.o random.o Blocks.o -o $@

es03.2.o: es03.2.cpp
	$(CC) -c es03.2.cpp -o $@

random.o: ../Generatore/random.cpp ../Generatore/random.h
	$(CC) -c ../Generatore/random.cpp -o $@

Blocks.o: Blocks.cpp Blocks.h 
	$(CC) -c Blocks.cpp -o $@