#pragma once

#include <fstream>
#include <string>
#include "../Generatore/random.h"


class EsperimentoBuffon: public Random{

    public:
    EsperimentoBuffon(double, double, int);
    ~EsperimentoBuffon() {;}


    double Esegui();
    

    private:

    Random m_rnd;
    double m_d, m_L;
    int m_hit;
    int m_thr;
};