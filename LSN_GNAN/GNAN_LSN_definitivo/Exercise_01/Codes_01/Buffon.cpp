#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

#include "Buffon.h"
#include "../Generatore/random.h"


double Estrai_Theta(Random ran){

    while(true){
    double x,y;
    x = ran.Rannyu(-1,1);
    y = ran.Rannyu(0,1);


        if(pow(x,2) + pow(y,2) < 1 and y >= 0){
            return acos( x / sqrt( pow(x,2) + pow(y,2) )); 
        }
    }
}


using namespace std;

EsperimentoBuffon::EsperimentoBuffon(double d, double L, int N_thr){

   m_d = d, m_L = L, m_thr = N_thr, m_hit = 0;

   m_rnd.Inizializza();
   m_rnd.SaveSeed();
}


double EsperimentoBuffon::Esegui(){

    m_hit = 0;

    for(int i{0}; i<m_thr; i++){

        double x = m_rnd.Rannyu(0, m_d);
        //double theta = m_rnd.Rannyu(0, M_PI);
        double theta = Estrai_Theta( m_rnd );

   
        if( x + sin(theta)*m_L*0.5 >= m_d or x - sin(theta)*m_L*0.5 <= 0){
            
             m_hit++;
        }
        
    }
    
    return 2*m_L*m_thr / (m_hit * m_d);

}