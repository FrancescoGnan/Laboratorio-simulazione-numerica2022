#include <iostream>
#include <cmath>
#include <fstream>
#include "mpi.h"
#include "TSP.h"
#include <string>

using namespace std;

//------------------------------------------------------
//------------------------------------------------------
int main(int argc, char* argv[]){

    int size, rank;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Input(rank);
    
    std::vector<Posizione> pos_0(ncity);

    if(USA == 1)
    {
	   	 
    	     ifstream capitals;
	     capitals.open("American_capitals.dat");
	     for(int i{}; i<ncity; i++)
	     {
		    double x, y;
		    capitals >> x >> y;
		    pos_0[i].SetX(x);
		    pos_0[i].SetY(y);
             }		  
    }else
    {
             pos_0 = NewPositions(ncity);
    }

    std::vector<int> v;
    for(int i{0}; i<ncity; i++) v.push_back(i);
//------------------------------------------------------   
    ofstream outL2, outBestHalf;
    
    if(USA == 1)
    {
       outL2.open("Risultati/USA/Migration_L2_rk"+to_string(rank)+".dat", ios::app);
       outBestHalf.open("Risultati/USA/Migration_BestH_rk"+to_string(rank)+".dat", ios::app);
    }else
    {

         if(circle == 1)
         {
              outL2.open("Risultati/Circle/L2_rk"+to_string(rank)+".dat", ios::app);
              outBestHalf.open("Risultati/Circle/BestH_rk"+to_string(rank)+".dat", ios::app);
         }else
         {
              outL2.open("Risultati/Square/L2_rk"+to_string(rank)+".dat", ios::app);
              outBestHalf.open("Risultati/Square/BestH_rk"+to_string(rank)+".dat", ios::app);
         }
     }
//------------------------------------------------------
    GA Genetic(rnd,npop, ncity, pos_0);
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
      
      Genetic.NewGeneration();
      Genetic.Order();

      if(exchange == 1 and i%20 == 0)   // Starting migration
      {
          // Migration(size,ncity,Genetic);
  	  std::vector<double> x(ncity), y(ncity);
	  for(int node{}; node<size; node++)
	  {
		std::vector<Posizione> path(ncity);
		path = Genetic.GetBest();
		for(int j{}; j<ncity; j++)
		{
			x[j] = path[j].getX();
			y[j] = path[j].getY();
		}

		MPI_Bcast(&x.front(), x.size(), MPI_DOUBLE, node, MPI_COMM_WORLD);
		MPI_Bcast(&y.front(), y.size(), MPI_DOUBLE, node, MPI_COMM_WORLD);
                
		for(int j{}; j<ncity; j++)
		{
			path[j].SetX( x[j] );
			path[j].SetY( y[j] );
		}
		
		for(int i{}; i<ncity; i++)
		{
		      Genetic.Welcome( path, node );
                }

	    }
        }	//End of migration   
      
      Genetic.Order();
      best_trip.clear();
      Bests[i] = Genetic.GetBest();
      best_trip = Genetic.GetBest();

      outL2 << i << " " << Genetic.L2(best_trip) << endl;
      outBestHalf << i << " " << Genetic.GetBestHalf() << endl;
    }
//------------------------------------------------------
    outL2.close();
    outBestHalf.close();
 
    Print(Bests,rank, Genetic);
    
    MPI_Finalize();
    
    return 0;
}
//------------------------------------------------------
//------------------------------------------------------



void Input(int rk)
{
	
  ifstream ReadInput;

//Read seed for random numbers
   int p1, p2;
   ifstream Primes("Primes");
   for(int i{0}; i < rk + 1; i++)
   {
	   Primes >> p1 >> p2 ;
   }
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
  ReadInput >> exchange;
  ReadInput >> USA;

  ReadInput.close();
}
//------------------------------------------------------

std::vector<Posizione> NewPositions(int ncity)
{   

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
    }
  }

    return v;
}
//------------------------------------------------------
/*
void Migration(int sz, int Ncity, GA Gen)
{
	std::vector<double> x(Ncity), y(Ncity);
	for(int node{}; node<sz; node++)
	{
		std::vector<Posizione> path(Ncity);
		path = Gen.GetBest();
		for(int j{}; j<Ncity; j++)
		{
			x[j] = path[j].getX();
			y[j] = path[j].getY();
		}

		MPI_Bcast(&x.front(), x.size(), MPI_DOUBLE, node, MPI_COMM_WORLD);
		MPI_Bcast(&y.front(), y.size(), MPI_DOUBLE, node, MPI_COMM_WORLD);
                
		for(int j{}; j<Ncity; j++)
		{
			path[j].SetX( x[j] );
			path[j].SetY( y[j] );
		}
		
		for(int i{}; i<Ncity; i++)
		{
		      Gen.Welcome( path, node );
                }

	}
}*/	
//------------------------------------------------------
void Print(std::vector< std::vector< Posizione > > mat,int rk, GA Gen)
{
  ofstream out;
  if(USA == 1)
  {
     out.open("Risultati/USA/Migration_USA_rk"+std::to_string(rk)+".dat",ios::app);
  }else
  {
     if(circle == 1)
     {
        out.open("Risultati/Circle/Circle_rk"+std::to_string(rk)+".dat",ios::app);
     }else
     {
	    
        out.open("Risultati/Square/Square_rk"+std::to_string(rk)+".dat",ios::app);
     }  
  } 
  for(int j{0}; j<ncity; j++)
  {
        out << j << " " << mat[ngen-1][j].getX() << " " << mat[ngen-1][j].getY() << endl;
  }
      out << ncity << " " << mat[ngen-1][0].getX() << " " << mat[ngen-1][0].getY() << endl;
  out.close();
}


