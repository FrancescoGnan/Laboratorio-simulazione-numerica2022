#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>

#include "../Generatore/random.h"
#include "Blocks.h"

double error(std::vector<double> &AV,std::vector<double> &AV2, int n){
		
		if( n == 0 ){
			return 0;
		}
		else{
			return sqrt( ( AV2[n] - pow(AV[n], 2) ) / n );
		}
}

using namespace std;

//======================================
Blocchi::Blocchi(int M, int N){
    m_M = M;
    m_N = N;
}

Blocchi::~Blocchi() {}
//======================================


void Blocchi::blocks(std::vector<double> v, const char* filename){

   int steps = m_M / m_N;
   std::vector<double> sum_prog(m_N), su2_prog(m_N), err_prog(m_N), ave(m_N), av2(m_N), x(m_N);
   /* for(int i=0; i<m_N; i++){
	    x[i] = i*steps;        // # lanci in ogni blocco
    }
   */
    //==============  1° ciclo

    for(int i=0; i<m_N; i++){  //ciclo sul numero di blocchi

            double sum = 0;

        for(int j=0; j<steps; j++){  //ciclo sul numero di step per blocco

            int k = j + ( i * steps ) ;

            sum += v[k];
        }
        ave[i] = sum / steps;
	    av2[i] = pow( (ave[i]) , 2 );
    }

    //================== 2° ciclo

    for(int i=0; i<m_N; i++){  // di blocco in blocco do una stima progressiva del valor medio

        for(int j=0; j<i+1; j++){
		   
		   sum_prog[i] += ave[j];
		   su2_prog[i] += av2[j];
		}

        sum_prog[i] /= (i+1);  //media cumulativa <A>
		su2_prog[i] /= (i+1);  //<A^2>

        //cout << sum_prog[i] << endl;
		
		err_prog[i] = error( sum_prog, su2_prog, i );

        //cout << err_prog[i] << endl;
    }

    std::ofstream out;
    out.open(filename);

    for(int i=0; i<m_N; i++){

      out << i << " " << sum_prog[i] << " " << err_prog[i] << endl;

   }

   out.close();

}


