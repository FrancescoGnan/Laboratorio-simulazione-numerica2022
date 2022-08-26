#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>   
#include <fstream> 

#include "../Generatore/random.h"
#include "Blocks.h"




double max(double a, double b){
    if(a<b) return b;
    else return a;
}

using namespace std;

int main(){

    int M = 10000;
    int N = 100;    // # Blocks
    double S_0 = 100;
    double T = 1;
    int K = 100;
    double r = 0.1;
    double sigma = 0.25;


    Random rnd;
    rnd.Inizializza();
    Blocchi BL( M , N );
    

    std::vector<double> C_i(M), P_i(M);
    

    for(int i{0}; i<M; i++){

        double S_1{S_0}, S_2{0.};
        //double h = 0.;

        for(int j{0}; j<100; j++){

            double z_i = rnd.Gauss( 0 , 1 );
            // t_i+1 - t_i = t + h - t = h = 0.01

            S_2 = S_1*exp( ( r - pow(sigma,2)/2 )* 0.01 + sigma*z_i*sqrt(0.01) );
            S_1 = S_2;
            //h += 0.01;
        }


        C_i[i] = exp( -r*T )*max( 0 , S_2 - K );
        P_i[i] = exp( -r*T )*max( 0 , K - S_2 );
    }

    BL.blocks(C_i, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione03/Risultati/es03.2a.dat");
    BL.blocks(P_i, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione03/Risultati/es03.2b.dat");


    return 0;
}