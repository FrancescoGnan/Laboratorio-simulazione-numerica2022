#ifndef __ISING__
#define __ISING__

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters, observables
const int m_props=1000;
int n_props,iH;
double nbins;
double walker[m_props];

// averages
double blk_av[m_props],blk_norm,accepted,attempted;
double glob_av[m_props],glob_av2[m_props];
double stima_H;
double err_H;

//configuration
double x;

// simulation
int nstep, nblk, test, Eq_steps, T_start, dT, pari, histo, parameters;
double mu, sigma, delta1, delta2, beta, beta_start;

//functions
void Input(void);
void Equilibration(int);
void Reset(int);
void Accumulate(void);
void Averages(int);
void Simulation(bool);
void Simulated_Annealing(double);
void Move();
void Print_histo(void);
void Print_parameters(double);
void Print_averages(bool, int);
void Measure(void);
//void Save_Energy(double);
double Potential(double);
double PsiT(double, double, double);
double Error(double,double,int);



#endif