#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
#include "main.h"

using namespace std;

int main(){

    Input();
    Equilibration(Eq_steps);

    //first simulation ---> exercise 08.1
    Simulation(false);

    //Simulated Annealing ---> exercise 08.2
    while(beta < 500){
      Equilibration(Eq_steps);
      Simulated_Annealing(beta);
      //Save_Energy(beta);
      beta++;
    }

    //Aggiungere funzione SaveBestParameters

    cout << endl << "============================" << endl;
    cout << "Best parameters: sigma = " << sigma << ", mu = " << mu << endl;

    return 0;
}

void Input(void)
{
  ifstream ReadInput;

//Read seed for random numbers
   int p1, p2;
   ifstream Primes("Primes");
   Primes >> p1 >> p2 ;
   Primes.close();

   ifstream input("seed.in");
   input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
   rnd.SetRandom(seed,p1,p2);
   input.close();
  
//Read input informations
  ReadInput.open("input.dat");

  ReadInput >> delta1;
  ReadInput >> delta2;
  ReadInput >> sigma;
  ReadInput >> mu;
  ReadInput >> beta_start;
  ReadInput >> test;
  ReadInput >> Eq_steps;
  ReadInput >> pari;
  ReadInput >> histo;
  ReadInput >> parameters;
  ReadInput >> nblk;
  ReadInput >> nstep;

  beta = beta_start;

  cout << "Delta1 = " << delta1 << endl;
  cout << "Delta2 = " << delta2 << endl;
  cout << "Sigma = " << sigma << endl;
  cout << "Mu = " << mu << endl;
  cout << "Starting temperature = " << 1/(double)beta_start << endl;  
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl;
  if(test) cout << endl << "Armonic test" << endl;

  ReadInput.close();

//Prepare arrays for measurements
  iH = 0; //Energy

  n_props = 1; //Number of observables

//initial configuration
  x = 0.0;                //Parto da x_0 = 0
  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iH] << endl;
}

void Simulation(bool print){
    
      for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
      {
        Reset(iblk);   //Reset block averages
        for(int istep=1; istep <= nstep; ++istep)
        {
          Move();
          Measure();
          Accumulate(); //Update block averages
        }
        Averages(iblk);   //Print results for current block
        Print_averages(print, iblk);
      }
}

void Simulated_Annealing(double bet){

    //ofstream out;
    //out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/SA_pari.dat",ios::app);
    double sigma_old, mu_old, H_old, err_old;
    double H_new, err_new;
    double A;

    sigma_old = sigma;
    mu_old = mu;
    H_old = glob_av[iH]/(double)nblk;
    err_old = err_H;

    //Uso una probabilità di transizione uniforme in (-delta2,delta2)
    sigma = sigma + rnd.Rannyu(-delta2,delta2);
    mu   = mu + rnd.Rannyu(-delta2,delta2);
    
    //New
    Simulation(false);
    H_new = glob_av[iH]/(double)nblk;
    err_new = err_H;

    //Metropolis test
      A = std::min( 1.0 , exp( -bet * (H_new-H_old) ) );

      if(A >= rnd.Rannyu())  
      {
      //Update
        //out << bet << " " << H_new << " " << err_new << endl;
        accepted = accepted + 1.0;
        if(parameters == 1) {
          Print_parameters(bet);
        }
      }else{
        sigma = sigma_old;
        mu = mu_old;
        glob_av[iH] = H_old * nblk;
      }
      attempted = attempted + 1.0;

      //out.close();

}

void Equilibration(int steps){
/*
  cout << "----------------------------" << endl;
  cout << "EQUILIBRATION PHASE: " << steps << " steps" << endl;
  cout << "----------------------------" << endl;
*/
  for(int i{0}; i<steps; i++){
    Move();
  }
}



void Move(){

    double A, Psi_old, Psi_new, x_new;

    //Uso una probabilità di transizione uniforme in (-delta1,delta1)
    x_new = x + rnd.Rannyu(-delta1,delta1);
    
    //Old
    Psi_old = fabs( PsiT(x,mu,sigma) ) * fabs( PsiT(x,mu,sigma) );
    
    //New
    Psi_new = fabs( PsiT(x_new,mu,sigma) ) * fabs( PsiT(x_new,mu,sigma) );

    //Metropolis test
      A = std::min( 1.0 , Psi_new/(double)Psi_old );

      if(A >= rnd.Rannyu())  
      {
      //Update
        x = x_new;
        if(histo == 1){
          Print_histo();
        }
        accepted = accepted + 1.0;
      }
      attempted = attempted + 1.0;
}

void Print_histo(void){

   ofstream histo;
   histo.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/histo.dat",ios::app);
   histo << x << endl;
   histo.close();
}

void Print_parameters(double beta){

   ofstream param;
   param.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/parameters.dat",ios::app);
   param << beta << " " << mu <<" " << sigma << endl;
   param.close();
}


void Measure()
{
  
  double H = 0.0;
  double d1 = pow(x-mu,2)/(sigma*sigma);
  double d2 = pow(x+mu,2)/(sigma*sigma);
  double Ekin = -0.5 *( exp( -d1/2 ) * (d1-1) / (sigma*sigma) + exp( -d2/2 ) * (d2-1) / (sigma*sigma) );
  H = Ekin /(double) PsiT(x,mu,sigma) + Potential(x);

  walker[iH] = H;

}

double Potential(double x){

    if(test){
      return 0.5*x*x;
    }else{
      return x*x*x*x - 5*0.5*x*x;
    }
}

double PsiT(double x, double mu, double sigma){
    if(pari){
      return exp(-pow(x-mu,2) /(double) (2*sigma*sigma)) + exp(-pow(x+mu,2) /(double) (2*sigma*sigma));  
    }else{
      return exp(-pow(x-mu,2) /(double) (2*sigma*sigma)) - exp(-pow(x+mu,2) /(double) (2*sigma*sigma));  

    }
}

void Reset(int iblk) //Reset block averages
{
   
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0;
}


void Averages(int iblk) //Print results for current block
{
    
    stima_H = blk_av[iH]/blk_norm; //Energy
    glob_av[iH] += stima_H;
    glob_av2[iH] += stima_H*stima_H;
    err_H=Error(glob_av[iH],glob_av2[iH],iblk);
    
}

void Print_averages(bool stampa,int iblk){

  if(stampa){
      ofstream H;
      const int wd=12;
    
      //cout << "Block number " << iblk << endl;
      //cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
      if(test) H.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/test.dat",ios::app);
      else H.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/H_best.dat",ios::app);

      H << setw(wd) << iblk <<  setw(wd) << stima_H << setw(wd) << glob_av[iH]/(double)iblk << setw(wd) << err_H << endl;

      //cout << "----------------------------" << endl << endl;
      H.close();
  }
}
/*
void Save_Energy(double T){

    ofstream out;
    out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione08/Risultati/H_T.dat",ios::app);

    out << beta << " " << glob_av[iH]/(double)nblk << " " << err_H << endl;
    out.close();
}
*/
double Error(double sum, double sum2, int iblk)
{
    return sqrt(fabs(sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)iblk);
}
