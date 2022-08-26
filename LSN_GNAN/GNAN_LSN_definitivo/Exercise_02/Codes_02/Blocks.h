#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../Generatore/random.h"
#include "RandomWalk.h"



class Blocchi{

public:
    
    Blocchi();
    Blocchi(int , int );
    ~Blocchi();

    void blocks(std::vector<double>, const char*);
    //void RWblocks(int , int , int ,RandomWalk ,Random , const char* );
    



private:

int m_M; // # throws
int m_N; // # blocks




};