#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "../Generatore/random.h"
#include "Blocks.h"
#include "RandomWalk.h"
#include "position.h"

using namespace std;

int main(){


    int M = 10000;          // # simulazioni
    int N_blocks = 100;
    int RW_steps = 100;     
    double a = 1;           // lattice constant
    int L = M / N_blocks;   // # RW in ogni blocco

    Random rnd;
    rnd.Inizializza();
    RandomWalk RW;
    RW.SetConstant(a);
    Posizione O(0,0,0);
    
    std::ofstream out1, out2;
    out1.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/es02.2a.dat");
    out2.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/es02.2b.dat");


//========================= Simulo due RW discreto di 1000 passi, uno discreto e uno continuo

    RW.PrintDiscreteRW(1000,rnd,"/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/RWdiscreto.dat" );
    RW.PrintContinuousRW(1000,rnd,"/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione2/Risultati/RWcontinuo.dat" );

//Eseguo la statistica su M simulazioni 

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////              DISCRETO

//------------------------------------------
    //Dichiaro e inizializzo due matrici

    std::vector<double> v1(N_blocks);
    std::vector< vector<double> > AVE, AV2;

    for(int i{0}; i<RW_steps; i++){
        AVE.push_back(v1);
        AV2.push_back(v1);
    }
    //std::vector< vector<double> > AVE(RW_steps, std::vector<double>(N_blocks,0.)), AV2(RW_steps, std::vector<double>(N_blocks,0.));
//------------------------------------------

    
    std::vector<double> Media(RW_steps), Media2(RW_steps), err(RW_steps);

    for(int k{0}; k<N_blocks; k++){ // In ogni blocco

        std::vector<double> sum(RW_steps);
        for(int j{0}; j<L; j++){    // In ogni RW del blocco

            Posizione P(0,0,0);
           
            for(int i{0}; i<RW_steps; i++){  // Per ogni step del RW
                
                double s1 = rnd.Rannyu();
                double s2 = rnd.Rannyu();
                P = RW.DiscreteStep( P , s1, s2 );

                double R2 = pow( P.Distanza( O ), 2 );
                sum[i] += R2;
                
            }   
        }
        for(int i{0}; i<RW_steps; i++){ // per ogni passo del RW calcolo la media del k-esimo blocco
            AVE[i][k] = sqrt( sum[i] / L );

        }
    }

    //===============================
    //Calcolo la media delle medie in ogni blocco e l'incertezza

    for(int i{0}; i<RW_steps; i++){ //per ogni passo

        for(int k{0}; k<N_blocks; k++){ 
            Media[i] += AVE[i][k] / N_blocks; 
            Media2[i] += pow( AVE[i][k] , 2 );
        }

        Media2[i] = Media2[i] / N_blocks;

        err[i] = sqrt( Media2[i] - pow( Media[i], 2 ) ) / sqrt( N_blocks - 1);

        out1 << i << " " << Media[i] << " " << err[i] << endl;

    }
 
    out1.close();
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////              CONTINUO

//------------------------------------------
    //Reinizializzo le due matrici e i vettori

    for(int i{0}; i<RW_steps; i++){
        for(int k{0}; k<N_blocks; k++){
            AVE[i][k] = 0;
            AV2[i][k] = 0;
        }
        Media[i] = 0;
        Media2[i] = 0;
        err[i] = 0;
    }
//------------------------------------------
    for(int k{0}; k<N_blocks; k++){ // In ogni blocco

        std::vector<double> sum(RW_steps);
        for(int j{0}; j<L; j++){    // In ogni RW del blocco

            Posizione P(0,0,0);
           
            for(int i{0}; i<RW_steps; i++){  // Per ogni step del RW
                
                double s1 = rnd.RanTheta();
                double s2 = rnd.RanPhi();
                P = RW.ContinuousStep( P , s1, s2 );

                double R2 = pow( P.Distanza( O ), 2 );
                sum[i] += R2;
                
            }   
        }
        for(int i{0}; i<RW_steps; i++){ // per ogni passo del RW calcolo la media del k-esimo blocco
            AVE[i][k] = sqrt( sum[i] / L );
        }
    }

    //===============================
    //Calcolo la media delle medie in ogni blocco e l'incertezza

    for(int i{0}; i<RW_steps; i++){ //per ogni passo

        for(int k{0}; k<N_blocks; k++){ 
            Media[i] += AVE[i][k] / N_blocks; 
            Media2[i] += pow( AVE[i][k] , 2 );
        }

        Media2[i] = Media2[i] / N_blocks;

        err[i] = sqrt( Media2[i] - pow( Media[i], 2 ) ) / sqrt( N_blocks - 1);

        out2 << i << " " << Media[i] << " " << err[i] << endl;

    }
 
    out2.close();


    return 0;
}






