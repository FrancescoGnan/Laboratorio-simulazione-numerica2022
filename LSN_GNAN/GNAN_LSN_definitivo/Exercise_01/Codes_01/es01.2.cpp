#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

#include "../Generatore/random.h"

using namespace std;

int main(int argc, char *argv[]){

//=============================================== inizializzo generatore:
   Random rnd;
   rnd.Inizializza();
//===============================================

    std::ofstream out1;
    std::ofstream out2; 
    std::ofstream out3;  
    std::ofstream out4;  

    out1.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.2a.dat");
    out2.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.2b.dat");
    out3.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.2c.dat");
    out4.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione01/Risultati/es01.2d.dat");

    int M{10000};
    std::vector<int> N{1,2,10,100};
    std::vector<double>  SUn(M), SEn(M), SLn(M);
    double sum1{0.}, sum2{0.}, sum3{0.};
    
    for(int i=0; i<4; i++){ //Per ogni N= 1,2,10,100
        SUn.clear();
        SEn.clear();
        SLn.clear();

        for(int k{0}; k<M; k++){ //10000 volte

            sum1 = 0.;
            sum2 = 0.;
            sum3 = 0.;

            for(int s=0; s<N[i]; s++){  //Somma su N
                sum1 += rnd.Rannyu();
                sum2 += rnd.Expo(1);
                sum3 += rnd.Lorentz(0,1);

            }

            //cout << sum1 << " "<< sum2 << " " << sum3 <<endl;
            SUn[k] = sum1 / N[i];
            SEn[k] = sum2 / N[i];
            SLn[k] = sum3 / N[i];
            //cout << SUn[k] << " " << SEn[k] << " " << SLn[k] << endl;


            if( i == 0){
                out1 << SUn[k] << " " << SEn[k] << " " << SLn[k] << endl;
            }else if( i == 1){
                out2 << SUn[k] << " " << SEn[k] << " " << SLn[k] << endl;
            }else if( i == 2){
                out3 << SUn[k] << " " << SEn[k] << " " << SLn[k] << endl;
            }else{
                out4 << SUn[k] << " " << SEn[k] << " " << SLn[k] << endl;
            }
        }

    }
    out1.close();
    out2.close();
    out3.close();
    out4.close();

    return 0;
}