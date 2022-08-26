MPI  = mpicxx
CFLAGS = -Wall -O3 --std=c++11

TSP.exe : TSP.o random.o GeneticAlgorithm.o Position.o
	$(MPI) random.o TSP.o GeneticAlgorithm.o Position.o -o TSP.exe

TSP.o : TSP.cpp TSP.h Position.h GeneticAlgorithm.h 
	$(MPI) -c TSP.cpp -o TSP.o $(CFLAGS)
Random.o: Random.cpp Random.h
	$(MPI) -c random.cpp -o random.o $(CFLAGS)
GeneticAlgorithm.o : GeneticAlgorithm.cpp GeneticAlgorithm.h
	$(MPI) -c GeneticAlgorithm.cpp -o GeneticAlgorithm.o $(CFLAGS)
Position.o : Position.cpp Position.h
	$(MPI) -c Position.cpp -o Position.o $(CFLAGS)
clean :
	rm *.o TSP.exe
