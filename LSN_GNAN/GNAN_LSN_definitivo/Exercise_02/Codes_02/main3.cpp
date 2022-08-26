#include <iostream>
#include <fstream>

#include "../Generatore/random.h"
#include "Blocks.h"

using namespace std;

struct point{
    double x;
    double y;
    double z;
};

int main(){

    int M = 10000;
    int N = 100;
    int a = 1;
    int L = M/N;
    int steps = 100;

    Blocchi BL( M , N );

    for(int i{0}; i<steps; i++){
        vector<double> r2(M);
        




    }







    return 0;
}

 