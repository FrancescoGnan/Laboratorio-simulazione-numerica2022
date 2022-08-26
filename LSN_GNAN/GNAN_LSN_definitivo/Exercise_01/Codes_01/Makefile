CC = g++
CFLAGS = -Wall -03 --std=c++11

EXECUTABLES = es01.1 es01.2 es01.3

all:
		make $(EXECUTABLES)
        
es01.1: es01.1.o random.o Blocks.o
	$(CC) es01.1.o random.o Blocks.o -o $@

es01.1.o: es01.1.cpp 
	$(CC) -c es01.1.cpp -o $@

es01.2: es01.2.o random.o
	$(CC) es01.2.o random.o -o $@

es01.2.o: es01.2.cpp 
	$(CC) -c es01.2.cpp -o $@

es01.3: es01.3.o random.o Buffon.o Blocks.o
	$(CC) es01.3.o random.o Buffon.o Blocks.o -o $@

es01.3.o: es01.3.cpp 
	$(CC) -c es01.3.cpp -o $@

random.o: ../Generatore/random.cpp ../Generatore/random.h
	$(CC) -c ../Generatore/random.cpp -o $@

Blocks.o: Blocks.cpp Blocks.h 
	$(CC) -c Blocks.cpp -o $@

Buffon.o: Buffon.cpp Buffon.h 
	$(CC) -c Buffon.cpp -o $@

