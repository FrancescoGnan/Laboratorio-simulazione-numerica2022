#pragma once

#include <vector>

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//Positions
#include "Position.h"

//Genetic Algorithm
#include "GeneticAlgorithm.h"


// simulation
int ncity, npop, ngen, nexp, circle; 
double mprob, cprob;



//functions
void Input(void);
std::vector<Posizione> NewPositions(int);
void Print(std::vector< std::vector< Posizione > >, GA);
