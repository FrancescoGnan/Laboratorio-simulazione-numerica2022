#include <iostream>
#include <fstream>
#include <cmath>

#include "../Generatore/random.h"
#include "Blocks.h"
#include "Buffon.h"


using namespace std;

int main(){

    double L = 0.5;           //Lunghezza sbarra
    double d = 1;          //distanza righe
    int N_thr = 10000;   //lanci

    int M = 10000;       //stime
    int N = 100;         //blocchi

    EsperimentoBuffon buffon(d, L, N_thr);
    Blocchi Bl(M, N);

    //================================ 
    std::vector<double> Pi(M);
    for(int i=0; i<M; i++){
	    Pi[i] = buffon.Esegui();
        //cout << Pi[i] << endl;
    }

    Bl.blocks(Pi, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.3.dat");


    return 0;

}