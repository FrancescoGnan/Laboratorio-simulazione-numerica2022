#include <iostream>
#include <fstream>
#include <cmath>

#include "../Generatore/random.h"
#include "Blocks.h"


using namespace std;

int main(){

    int M = 100000;
    int N = 100;

    Random rnd;
    rnd.Inizializza();

    Blocchi Bl( M , N );

//================================ <r>:
    std::vector<double> r(M);
    for(int i=0; i<M; i++){
	    r[i] = rnd.Rannyu();
    }

    Bl.blocks(r, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.1a.dat");

//================================ 𝜎^2:
    std::vector<double> sigma(M);
    for(int i=0; i<M; i++){
	    sigma[i] = pow( r[i] - 0.5, 2 );
    }

    Bl.blocks(sigma, "/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.1b.dat");

//================================ 𝜒^2:
    int n = 10000;
    int m = 100;
    std::vector<double> chi(m);
    std::vector<int> x(m);
    for(int i{0}; i<m; i++){
        x[i] = i;
    }
////////////////////// Calcolo

    for(int i=0; i<m; i++){ //divido (0,1) in m intervalli

        std::vector<int> conta_chi(m);

        for(int j=0; j<n; j++){ //per ogni intervallo faccio n lanci
            
            conta_chi[static_cast<int>(rnd.Rannyu() * m)]++;   

        }
        for (int j=0;j<m;++j) chi[i] += pow( conta_chi[j] - n/m , 2) / (n/m);
    }

//================================ Stampo su file:
    std::ofstream out;
    out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.1c.dat");

    for(int i=0; i<m; i++){

       out << x[i] << " " << chi[i] << endl;

    }

    out.close();

    rnd.SaveSeed();

    return 0;

}