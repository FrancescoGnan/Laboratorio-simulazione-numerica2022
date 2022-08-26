#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "../Generatore/random.h"


class Blocchi{

public:
    
    Blocchi();
    Blocchi(int , int );
    ~Blocchi();

    void blocks(std::vector<double>, const char*);
    



private:

int m_M; // # throws
int m_N; // # blocks




};