CC = g++
CFLAGS = -Wall -O3 --std=c++11

TSP.exe : TSP.o random.o GeneticAlgorithm.o Position.o
	$(CC) random.o TSP.o GeneticAlgorithm.o Position.o -o TSP.exe

TSP.o : TSP.cpp TSP.h Position.h GeneticAlgorithm.h 
	$(CC) -c TSP.cpp -o TSP.o $(CFLAGS)
Random.o : Random.cpp Random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)
GeneticAlgorithm.o : GeneticAlgorithm.cpp GeneticAlgorithm.h
	$(CC) -c GeneticAlgorithm.cpp -o GeneticAlgorithm.o $(CFLAGS)
Position.o : Position.cpp Position.h
	$(CC) -c Position.cpp -o Position.o $(CFLAGS)
clean :
	rm *.o TSP.exe
