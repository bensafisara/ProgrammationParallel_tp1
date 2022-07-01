#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <thread>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;
int N;
int somme_vector;

/*
- Bensafi Sarra
-version Sequentielle
-Pour compiler : g++ -pthread exercice3_1.cpp -o exo3_1.x
-Pour Executer : time ./exo3_1.x 444
*/
void generateRandomVector (int vector[], int lowerValue, int upperValue) {
    
    int i;
    for (i = 0; i <N; ++i) {
       
            vector[i] = (rand() % (upperValue - lowerValue + 1)) + lowerValue;
        }
    }

int Add(int vector[]){
int somme =0;
for (int i = 0; i < N; ++i) {
       
            somme = somme +vector[i];
        }

return somme;
}



int main(int argc, char** argv)
{

if (argc<2 || argc>2 )
  {
    std::cout <<" Erreur"<<std::endl;
    std::cout <<"il faut spécifier [La dimension du vecteur N ]   \n"<<std::endl;
   

  }else
  {
    N=atoi(argv[1]);
    
  }

int A[N];
generateRandomVector(A,1,99);
// print vector
std::cout << "vector A\n";
        for (int i = 0; i < N; i++)
        {
            
                std::cout << A[i] << " ";  
                 
        }


std::cout << "\n";
somme_vector = Add(A);
std::cout << "somme : "<<somme_vector;
std::cout << "\n";

    }