#include <iostream>
#include <fstream>
#include <cmath>

#include "../Generatore/random.h"
#include "Integrali.h"
#include "Funzione.h"
#include "Blocks.h"


using namespace std;

int main(){

    int M = 10000;
    int N = 100;

    Random rnd;
    rnd.Inizializza();
    Blocchi Bl( M , N );
    Coseno mycos( M_PI*0.5 , M_PI*0.5 );
    Integrali Int;


    std::vector<double> r(M);
    for(int i=0; i<M; i++){
	    r[i] = Int.Uniform(mycos, rnd.Rannyu());
        //cout << r[i] << endl; 
    }
    Bl.blocks(r, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/es02.1a.dat");

//=============================
    Coseno2 mycos2( M_PI*0.5 , M_PI*0.5 );

    std::vector<double> k(M);
    for(int i=0; i<M; i++){
	    k[i] = Int.Uniform(mycos2, rnd.Coseno());
       //cout << k[i] << endl; 
    }
    Bl.blocks(k, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/es02.1b.dat");


    rnd.SaveSeed();
    return 0;
}