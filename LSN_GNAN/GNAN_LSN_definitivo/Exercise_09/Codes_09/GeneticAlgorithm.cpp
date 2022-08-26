#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <random>
#include <type_traits>
#include<bits/stdc++.h>


#include "random.h"
#include "GeneticAlgorithm.h"
#include "../Armadillo/armadillo-11.1.1/include/armadillo"

double Distanza2( const Posizione& a, const Posizione& b){
	return       pow( a.getX()-b.getX(), 2 )
				+pow( a.getY()-b.getY(), 2 )
				+pow( a.getZ()-b.getZ(), 2 ) ;
}

using namespace std;
using namespace arma;


//======================================
GA::GA(Random ran, int N, int M, std::vector<Posizione> v)
{
    rnd = ran;
    N_pop = N;
    N_Chrom = M;
    mat_pop.resize(N_pop);
    new_pop.resize(N_pop);

    for(unsigned int i{0}; i<N_Chrom; i++)
    {
        v_p.push_back( v[i] );
    }
    v_min.resize(N_Chrom);

}

GA::~GA() {}
//======================================


void GA::SetExp(int p)
{
    m_exp = p;
}
//--------------------------------------
void GA::SetProb(double pm, double pc)
{
    Pm = pm;
    Pc = pc;
}
//--------------------------------------
void GA::SetPopulation(std::vector<int> p)
{
    
    for(unsigned int i{0}; i<N_pop; i++)
    {
        std::random_shuffle(p.begin()+1,p.end());
        std::vector<Posizione> P1{};
        for(unsigned int j{0}; j<N_Chrom; j++)
        {
            mat_pop[i].push_back(p[j]);
            new_pop[i].push_back(0);
            P1.push_back(v_p[mat_pop[i][j]]);
        }
    }
}
//--------------------------------------
/*
void GA::Check(int index, int start)
{
    //dimensione = 34
    //Visita una sola volta ogni città
    //città 1 uguale per tutte
   
    if( mat_pop[index].size() != N_Chrom)
    {
        cout << "Check error 1" << endl;
    }

    int conta{0};
    for(unsigned int i{0}; i<N_Chrom; i++)
    {
        int a = mat_pop[index][i];
        for(unsigned int j{i+1}; j<N_Chrom; j++)
        {
            if( mat_pop[index][j] == a ) conta++;
        }
    }
    if( conta > 0 )
    {
        cout << "Check error 2" << endl;
    }

    if( mat_pop[index][0] != start )
    {
        cout << "Check error 3" << endl;
    }

}
*/
//--------------------------------------
double GA::L2(std::vector<Posizione> v)
{
    double sum{0.0};
    for(unsigned int i{0}; i<v.size(); i++)
    {
        if( i != v.size() - 1 )
        {
            sum += Distanza2( v[i] , v[i+1] );
            //sum += ( v[i] - v[i+1] ) * ( v[i] - v[i+1] );
        }
        else 
        {
            sum += Distanza2( v[v.size()-1] , v[0] );
            //sum += ( v[v.size()-1] - v[0] ) * ( v[v.size()-1] - v[0] );
        }
    }

    return sum;
}
//--------------------------------------
void GA::Order(void)
{
    //ordino la popolazione dal minore al maggiore secondo L2
    std::vector<double> sum1{};
    for(unsigned int i{0}; i<N_pop; i++)
    {   
        std::vector<Posizione> p{};
        for(unsigned int j{0}; j<N_Chrom; j++)
        {      
            p.push_back( v_p[ mat_pop[i][j] ] );
        }
        sum1.push_back( L2( p ) );
    }

    std::vector<double> sum2{};
    sum2 = sum1;
    std::sort( sum2.begin(), sum2.end()); //ordino sum2 dal minore al maggiore

    std::vector<int> indici{};
    for(unsigned int i{0}; i<N_pop; i++)
    {
        auto it = find( sum1.begin(), sum1.end(), sum2.at(i) );  //cerco in sum1 (non ordinato) la posizione dell'elemento i-esimo di sum2 (ordinato)
        //it è un iteratore e find restituisce sum1.end() se non trova sum2.at(i)
        if( it != sum1.end() )
        {
            indici.push_back( std::distance( sum1.begin(), it ) ); //indici contiene (secondo l'ordine in sum2) le posizioni (in sum1) degli elementi ordinati di sum2
        }
    }
    //ordino le righe di mat_pop secondo l'ordine dettato da indici
    std::vector<std::vector<int>> copy_mat(N_pop, std::vector<int>(N_Chrom));
    copy_mat = mat_pop;
    for(unsigned int i{0}; i<N_pop; i++)
    {
        for(unsigned int j{0}; j<N_Chrom; j++)
        {
            mat_pop[i][j] = copy_mat[ indici[i] ][j];
        }
    }
/*
    //BUBBLE SORT
    for(unsigned int i{0}; i<N_pop-1; i++)
    {
        for(unsigned int j{0}; j<N_pop-i-1; j++)
        {
            if(sum1[j] > sum1[j+1])
            {
                std::swap( sum1[j] , sum1[j+1] );
                std::swap( mat_pop[j] , mat_pop[j+1] );
            }
        }
    }
*/
}
//--------------------------------------

int GA::Selection(void)
{   
    double r = rnd.Rannyu();
    int j = (int)( N_pop * pow(r,m_exp));

    return j;
}
//--------------------------------------
void GA::NewGeneration(void)
{
    for(unsigned int i{0}; i<N_pop; i+=2)
    {
        int k = Selection();
        Crossover(i,k,i);
        Mutations(i);
    }
    mat_pop = new_pop;
}
//--------------------------------------
std::vector<Posizione> GA::GetBest(void)
{
    std::vector<Posizione> P{};
    for(unsigned int i{0}; i<N_Chrom; i++)
    {
        P.push_back( v_p[mat_pop[0][i]] );
    }
    return P;
}
//--------------------------------------
double GA::GetBestHalf(void)
{
    double mean{0};
    std::vector<double> sum{};

    for(unsigned int i{0}; i<N_pop/2; i++)
    {
        std::vector<Posizione> p{};
        for(unsigned int j{0}; j<N_Chrom; j++)
        {
            p.push_back( v_p[ mat_pop[i][j] ] );
        }

        sum.push_back( L2( p ) );
        mean += sum[i];
    }
    mean /= (N_pop/2);
    
    return mean;
}

//--------------------------------------
void GA::CopyBests(int n)
{
    std::vector< std::vector<int> > copy(n, std::vector<int>(N_Chrom));
    for(unsigned int i{0}; i<n ; i++)
    {
        copy[i] = mat_pop[i];
        mat_pop[N_pop-1-i] = copy[i];
    }
}
//--------------------------------------
void GA::SaveMin(void)
{
    v_min = mat_pop[0];
}
//--------------------------------------
std::vector<Posizione> GA::GetMin(void)
{
    std::vector<Posizione> copy{};
    for(unsigned int i{0}; i<N_Chrom; i++)
    {
        copy.push_back( v_p[v_min[i]] );
    }
    return copy;
}

void GA::PrintMatrix(void)
{
    
    for(unsigned int i{0}; i<N_pop; i++)
    {   
        std::vector<Posizione> P{};
        cout << i << ":  [ ";
        for(unsigned int j{0}; j<N_Chrom; j++)
        {
            cout << mat_pop[i][j] << " ";
            P.push_back( v_p[ mat_pop[i][j] ] );
        }
        cout << "]           " <<L2(P) <<  endl;
    }
    cout << endl << "----------------------------------------------" << endl;
}

void GA::Welcome(std::vector<Posizione> new_p, int rank)
{
    std::vector<int> New_row{};
    for(int i{}; i<new_p.size(); i++)
    {
        for(int j{}; j<new_p.size(); j++)
        {
            if( new_p[i] == v_p[j] )
            {
                New_row.push_back( j );
            }
        }
    }
    
    mat_pop[N_pop - rank] = New_row;
}

void GA::Mutation1(int index)
{
    double r = rnd.Rannyu();
    if(  r < Pm )
    {
        while(true)
        {

            unsigned int o1 = static_cast<unsigned int>(rnd.Rannyu()*N_Chrom);
            unsigned int o2 = static_cast<unsigned int>(rnd.Rannyu()*N_Chrom);
            if( o1 != 0 and o2 != 0 )
            {
                std::swap( new_pop[index][o1] , new_pop[index][o2] );
                break;
            }
        }
    }
}


void GA::Mutation2(int index)
{
    double r = rnd.Rannyu();
    if(  r < Pm )
    {
       //unsigned int n = static_cast<unsigned int>(r*N_Chrom);
       int n = (int)rnd.Rannyu(1,34);
       // unsigned int m = static_cast<unsigned int>(rnd.Rannyu()*N_Chrom); //# spostamenti

 /*       std::vector<int> v{};
        for(unsigned int i{0}; i<N_Chrom; i++)
        {
            v.push_back( mat_pop[index][i] );
        }*/

        for(int i{}; i<n; i++)
        {
            std::rotate(new_pop[index].begin()+1, new_pop[index].begin()+2, new_pop[index].begin()+N_Chrom - 2);
            //std::rotate(v.begin()+1, v.begin()+m, v.begin()+N_Chrom - 2);
        }
 /*       for(unsigned int i{0}; i<N_Chrom; i++)
        {
            mat_pop[index][i] = v[i];
        }*/
    }
}


void GA::Mutation3(int index)
{
    double r = rnd.Rannyu();
    
    
    if(  r < Pm )
    {
        unsigned int n1 = (int)(rnd.Rannyu()*N_Chrom); 
        unsigned int n2 = (int)(rnd.Rannyu()*N_Chrom); 
        unsigned int m = (int)(rnd.Rannyu()*N_Chrom); 

        if( n1 > 0 and n2 > 0 and n1 != n2 and m < N_Chrom/2 )
        {
            for(unsigned int i{0}; i < m; i++)
            {
                std::swap( new_pop[index][Pbc(n1 + i)], new_pop[index][Pbc(n2 + i)] );
            }
        }
    }

}

void GA::Mutation4(int index) 
{
    double r = rnd.Rannyu();
    if(  r < Pm )
    {
        unsigned int m = (int)(rnd.Rannyu()*N_Chrom); 
        unsigned int n = (int)(rnd.Rannyu()*N_Chrom); 

        if( n > 0 and m <= N_Chrom )
        {
           std::reverse( new_pop[index].begin() + Pbc(n) -1, new_pop[index].begin() + Pbc(n+m) - 1 );
        }
    }   
}


void GA::Crossover(int index1, int index2, int newindex)
{
    double r = rnd.Rannyu();
    if( r < Pc )
    {
        std::vector<int> copia1{}, copia2{}, coda1{}, coda2{};
        int o = rnd.Rannyu(1,N_Chrom-2);
        for(unsigned int i{0}; i < N_Chrom; i++)
        {
            copia1.push_back( mat_pop[index1][i] );
            copia2.push_back( mat_pop[index2][i] );
        }


            for(unsigned int j{0}; j < N_Chrom; j++)
            {
                bool it = Search(copia1, o, copia2[j]);
                if( it == true )  //and copia2[j] != copia1[o-1]
                {
                    coda1.push_back( copia2[j] );
                }
            }
       


            for(unsigned int j{0}; j < N_Chrom; j++)
            {
                bool is = Search(copia2, o, copia1[j]);
                //auto is = find( copia2.begin(), copia2.begin()+o-1, copia1[j] );
                //if( is == copia2.begin()+o-1 and copia1[j] != copia2[o-1])
                if( is == true ) //and copia1[j] != copia2[o-1] 
                {
                    coda2.push_back( copia1[j] );
                }
            }
        

        for(unsigned int i{0}; i < o; i++) //sovrascrivo i due peggiori elementi della popolazione
        {
            new_pop[newindex][i] = copia1[i];
            new_pop[newindex+1][i] = copia2[i];
        }
        for(unsigned int i{o}; i < N_Chrom; i++)
        {
            new_pop[newindex][i] = coda1[i - o];
            new_pop[newindex+1][i] = coda2[i - o];
        }
    }
    else //Ricopio i genitori
    {
        for(unsigned int i{0}; i < N_Chrom; i++)
        {
            new_pop[newindex][i] = mat_pop[index1][i];
            new_pop[newindex+1][i] = mat_pop[index2][i];
        }
    }

}

bool GA::Search(std::vector<int> vec, int O, int elem)
{
    int conta = 0;
    for(int i{0}; i<O; i++)
    {
        if( vec[i] == elem ) conta++;
    }
    if( conta == 0 ) return true;
    else return false;
}


void GA::Mutations(int index)
{

     Mutation1(index);
     Mutation2(index);
     Mutation3(index);
     Mutation4(index);

}

int GA::FindIndex(std::vector<int> arr, int k){
    std::vector<int>::iterator it;
    it = std::find(arr.begin(), arr.end(), k);
    if(it != arr.end())
        return (it - arr.begin());
    else
        return 0;
}


int GA::Pbc(unsigned int i)
{
    if(i >= N_Chrom) i = i + 1 - N_Chrom;

    if( i != 0 ) return i;
    else cout << "Error Pbc" << endl;
}


