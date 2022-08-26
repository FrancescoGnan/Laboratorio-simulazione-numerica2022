#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <vector>

#include "random.h"
#include "Position.h"

class Chromosome: public Posizione{

    public:

    Chromosome();
    ~Chromosome();

    std::vector<Posizione> NewChrom();

    
    private:
    
    int m_N;
    std::vector<int> Chrom;
    Random m_rnd;
};
