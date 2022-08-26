#pragma once

#include <cmath>
#include <vector>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <type_traits>
#include<bits/stdc++.h>


#include "random.h"
#include "Position.h"



class GA: public Posizione{

    public:

    GA(Random, int,int,std::vector<Posizione>);
    ~GA();

    void SetExp(int);
    void SetProb(double,double);
    void SetPopulation(std::vector<int>);
    //-----------------
    void Check(int, int);
    int Selection(void);
    void Order(void);
    double L2(std::vector<Posizione>);
    int Pbc(unsigned int);
    //-----------------
    void Mutation1(int);   //Pair permutation
    void Mutation2(int);   //Shift contiguous
    void Mutation3(int);   //groups permutation
    void Mutation4(int);   //group inversion
    void Mutations(int);
    void Crossover(int, int, int);
    bool Search(std::vector<int>, int, int);
    void NewGeneration(void);
    //-----------------
    void CopyBests(int);
    void SaveMin(void);
    std::vector<Posizione> GetMin(void);
    int FindIndex(std::vector<int>, int);
    std::vector<Posizione> GetBest(void);
    double GetBestHalf(void);
    void PrintMatrix(void);
    void Welcome(std::vector<Posizione>, int);

    private:

    Random rnd;
    unsigned int N_pop, N_Chrom;
    int m_exp;
    std::vector< std::vector<int> > mat_pop, new_pop;
    std::vector<Posizione> v_p{};
    std::vector<int> v_min{};
    double Pm, Pc;

};

