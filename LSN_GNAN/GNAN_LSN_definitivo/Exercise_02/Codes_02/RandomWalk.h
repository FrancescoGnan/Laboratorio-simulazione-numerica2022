#pragma once

#include <cmath>
#include <vector>
#include <iostream>

#include "../Generatore/random.h"
#include "position.h"


class RandomWalk: public Posizione, Random{

    public:

    RandomWalk();
    ~RandomWalk();

    void SetConstant(double);
    Posizione DiscreteStep(Posizione, double, double);  
    Posizione ContinuousStep(Posizione, double , double);
    void PrintDiscreteRW(int, Random, const char*);
    void PrintContinuousRW(int, Random, const char*);

    
    private:

    double m_a;
    
};
