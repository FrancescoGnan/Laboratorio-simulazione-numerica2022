#include <cmath>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>

#include "../Generatore/random.h"
#include "RandomWalk.h"
#include "position.h"


using namespace std;


//======================================
RandomWalk::RandomWalk(){}


RandomWalk::~RandomWalk() {}
//======================================

void RandomWalk::SetConstant(double m){
    m_a = m;
}

Posizione RandomWalk::DiscreteStep(Posizione p, double s1, double s2){

    double x = p.getX();
    double y = p.getY();
    double z = p.getZ();

/////////////////////// Scelgo se incrementare o decrementare
    if (s1 < 0.5) {
        s1 = -1;
    }
    else {
        s1 = 1;
    }
/////////////////////// Scelgo la coordinata da modificare


    if (s2 < 0.33) {                      //Passi in una direzione nel caso discreto
        x +=  m_a * s1;
        p.SetX(x);
    }
    else if (s2 > 0.33 && s2 < 0.66) {
        y +=  m_a * s1 ;   
        p.SetY(y);                
    }
    else {
        z +=  m_a * s1 ;  
        p.SetZ(z);                 
    }   

    return p;

}

Posizione RandomWalk::ContinuousStep(Posizione p, double theta, double phi){

    double x = p.getX();
    double y = p.getY();
    double z = p.getZ();

    x += m_a * sin(theta) * cos(phi);
    y += m_a * sin(theta) * sin(phi);
    z += m_a * cos(theta);

    p.SetX(x);
    p.SetY(y);
    p.SetZ(z);


    return p;

}


void RandomWalk::PrintDiscreteRW(int steps, Random rnd, const char* filename){

    std::ofstream out;
    out.open(filename);

    Posizione P(0,0,0);

    for(int i{0}; i<steps; i++){  // Per ogni step del RW
                
         double s1 = rnd.Rannyu();
         double s2 = rnd.Rannyu();
         P = DiscreteStep( P , s1, s2 );
         out << i << " " << P.getX() << " "<< P.getY() << " "<< P.getZ() << endl;

     } 

     out.close();
}

void RandomWalk::PrintContinuousRW(int steps, Random rnd, const char* filename){

    std::ofstream out;
    out.open(filename);

    Posizione P(0,0,0);

    for(int i{0}; i<steps; i++){  // Per ogni step del RW
                
         double s1 = rnd.RanTheta();
         double s2 = rnd.RanPhi();
         P = ContinuousStep( P , s1, s2 );
         out << i << " " << P.getX() << " "<< P.getY() << " "<< P.getZ() << endl;

     } 

     out.close();
}



