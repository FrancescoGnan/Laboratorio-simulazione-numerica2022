#pragma once

#include <cmath>

class Funzione{

    public:

    virtual double Eval(double x) const = 0;
    virtual ~Funzione() {;};
};

//====================================
class Coseno : public Funzione{

   public:

   Coseno(){
       m_c = 0;
       m_a = 0;
   }

   Coseno(double c, double a){
       m_c = c;
       m_a = a;
   }

   ~Coseno() {;};

   virtual double Eval(double x) const{

       return m_c*cos( m_a*x );
   }
   
   private: 

   double m_c;
   double m_a;

};


class Coseno2 : public Funzione{

   public:

   Coseno2(){
       m_c = 0;
       m_a = 0;
   }

   Coseno2(double c, double a){
       m_c = c;
       m_a = a;
   }

   ~Coseno2() {;};

   virtual double Eval(double x) const{

       return m_c*cos( m_a*x ) / (2 - 2*x);  //divido l'integranda per p(x)
   }
   
   private: 

   double m_c;
   double m_a;

};