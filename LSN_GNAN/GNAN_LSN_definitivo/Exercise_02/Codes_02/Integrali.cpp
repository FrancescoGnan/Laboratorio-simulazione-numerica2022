#include <cmath>
#include <vector>
#include <iostream>
#include <cmath>

#include "../Generatore/random.h"
#include "./Integrali.h"
#include "Funzione.h"

using namespace std;


//======================================
Integrali::Integrali(){}

Integrali::~Integrali() {}
//======================================


double Integrali::Uniform(const Funzione &f, double x){


    return f.Eval(x);

}