#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>   
#include <fstream> 

#include "../Generatore/random.h"
#include "Blocks.h"


double dev_std(std::vector<double> &v, double mean){

    double errore;
    for(int i{0}; i<v.size(); i++){

        errore += pow( v[i] - mean , 2 );
    }

    errore = sqrt( errore / (v.size()*(v.size() - 1)) );
    return errore;
}

double max(double a, double b){
    if(a<b) return b;
    else return a;
}

using namespace std;

int main(){

    int M = 10000;
    int N = 100;    // # Blocks
    int S_0 = 100;
    int T = 1;
    int K = 100;
    double r = 0.1;
    double sigma = 0.25;

    Random rnd;
    rnd.Inizializza();
    Blocchi BL( M , N );
    

    // 1.
    std::vector<double> C_i(M), P_i(M);
    

    for(int i{0}; i<M; i++){

        double z_i = rnd.Gauss( 0 , 1 );
        double S_i = S_0*exp( ( r - pow(sigma,2)/2 )* T + sigma*z_i*sqrt(T) );

        C_i[i] = exp( -r*T )*max( 0 , S_i - K );
        P_i[i] = exp( -r*T )*max( 0 , K - S_i );
    }

    BL.blocks(C_i, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione03/Risultati/es03.1a.dat");
    BL.blocks(P_i, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione03/Risultati/es03.1b.dat");



    return 0;
}