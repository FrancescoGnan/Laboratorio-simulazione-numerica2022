#include <iostream>
#include <cmath>
#include <fstream>

#include "TSP.h"

using namespace std;
using namespace arma;

//------------------------------------------------------
//------------------------------------------------------
int main(){

    Input();
    std::vector<Posizione> pos;
    pos = NewPositions(ncity);
    std::vector<int> v;
    for(int i{0}; i<ncity; i++) v.push_back(i);
//------------------------------------------------------   
    ofstream outL2, outBestHalf;
    ofstream outputx, outputy;
    if(circle == 1)
    {
      outL2.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Circle/L2.dat", ios::app);
      outBestHalf.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Circle/BestH.dat", ios::app);
      outputx.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Circle/outputx.dat", ios::app);
      outputy.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Circle/outputy.dat", ios::app);
    }else
    {
      outL2.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Square/L2.dat", ios::app);
      outBestHalf.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Square/BestH.dat", ios::app);
      outputx.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Square/outputx.dat", ios::app);
      outputy.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Square/outputy.dat", ios::app);
    }
//------------------------------------------------------
    GA Genetic(rnd,npop, ncity, pos);
    Genetic.SetExp(nexp);
    Genetic.SetPopulation(v);
    Genetic.SetProb(mprob,cprob);
    Genetic.Order();
//------------------------------------------------------
    std::vector<Posizione> best_trip = Genetic.GetBest();
    std::vector< std::vector< Posizione > > Bests(ngen,std::vector<Posizione>(ncity));

    outL2 << 0 << " " << Genetic.L2(best_trip) << endl;
    outBestHalf << 0 << " " << Genetic.GetBestHalf() << endl;
//------------------------------------------------------
    for(int i{0}; i<ngen; i++)
    {    
      cout << "Generation " << i << endl;
      cout << "-----------------------" << endl;
      Genetic.NewGeneration();
      Genetic.Order();

      best_trip.clear();
      Bests[i] = Genetic.GetBest();
      best_trip = Genetic.GetBest();
  
      for(int j{0}; j<ncity; j++)
      {
        outputx << setw(20) << Bests[i][j].getX();
        outputy << setw(20) << Bests[i][j].getY();
      }

      outL2 << i << " " << Genetic.L2(best_trip) << endl;
      outBestHalf << i << " " << Genetic.GetBestHalf() << endl;
    }
//------------------------------------------------------
    outputx << endl;
    outputy << endl;

    outL2.close();
    outBestHalf.close();
    outputx.close();
    outputy.close();

    Print(Bests, Genetic);

    return 0;
}
//------------------------------------------------------
//------------------------------------------------------


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

  ReadInput >> ncity;
  ReadInput >> npop;
  ReadInput >> ngen;
  ReadInput >> nexp;
  ReadInput >> mprob;
  ReadInput >> cprob;
  ReadInput >> circle;

  ReadInput.close();
}
//------------------------------------------------------

std::vector<Posizione> NewPositions(int ncity)
{   

  ofstream out;
  out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/positions.dat", ios::app);

  std::vector<Posizione> v;
  if( circle == 1 )
  {
    for(int i{0}; i<ncity; i++)
    {   
        double rho = 1;
        double theta = rnd.Rannyu(0, 2*M_PI);
        Posizione pos(rho,theta);
        v.push_back(pos);
    }
  }else
  {
    for(int i{0}; i<ncity; i++)
    {   
        double x = rnd.Rannyu(0,1);
        double y = rnd.Rannyu(0,1);
        Posizione pos(x,y,0);
        v.push_back(pos);
        out << x << " " << y << endl;
    }
  }
  out.close();

  return v;
}
//------------------------------------------------------


void Print(std::vector< std::vector< Posizione > > mat, GA Gen)
{
  ofstream out;
  if(circle == 1)
  {
    out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Circle/Circle.dat",ios::app);
  }else
  {
    out.open("/mnt/c/Users/franc/Desktop/ANNO 3/SIMULAZIONE/Esercitazioni/Esercitazione09/Risultati/Square/Square.dat",ios::app);
  }
      for(int j{0}; j<ncity; j++)
      {
        out << j << " " << mat[ngen-1][j].getX() << " " << mat[ngen-1][j].getY() << endl;
      }
      out << ncity << " " << mat[ngen-1][0].getX() << " " << mat[ngen-1][0].getY() << endl;
  out.close();
}


