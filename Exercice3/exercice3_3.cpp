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
#include <mutex>
using namespace std;
int somme = 0;//Partagé
int N,NumTh;
int* A;
std::mutex m ;
////////////////

/*
- Bensafi Sarra
-version Par Bloc
-Pour compiler : g++ -pthread exercice3_3.cpp -o exo3_3.x
-Pour Executer : time ./exo3_3.x 4 2

*/



void generateRandomVector(int *vec, int lowerValue, int upperValue) {
    srand(time(0));
  
    int i;
    for (i = 0; i <N; ++i) {
       
            A[i] = (rand() % (upperValue - lowerValue + 1)) + lowerValue;
        }

}






void Add(int id){//Chaq thread va exécuter cette fonction
 
int taille= N/NumTh;
int fin ;                       // calcule fin block
int debut = id * taille ;           // calcule de debut de block

if((id+1)==NumTh){

       fin=N-1;

  }else{

      fin=((id*taille)+(taille))-1;}


 m.lock();  
for(int i = debut;i<=fin;i++) //cela est valable que pour les lignes car je divise les lignes en blocs
{
    
    somme = somme +A[i];
    
        }

m.unlock();

}




void func(int NumTh){

  /*****************Declaration & initialisation ********************/
  std::thread workers[NumTh];
  int i;
  
 

  /**********************Traitment******************************/
  for(i=0;i<NumTh;i++)
    {
      
      
                    workers[i]= std::thread(Add,i);
                    workers[i].join();

    }
    
   


  }


int main(int argc, char** argv){

if (argc<3 || argc>3 )
  {
    printf("faute \n");
    cout <<"respecter l'ordre [dimension vecteur  N ] [num threads]   \n"<<endl;
    exit(-1);
    
   
  }else
  {
N=atoi(argv[1]);
NumTh=atoi(argv[2]);
}


/********allocation *********/
    int i = 0;
    A=(int *)malloc( (N-1)*sizeof(int *));     
    
generateRandomVector(A,1,99);

/******print vector*******/
std::cout << "vector A\n";
        for (int i = 0; i < N; i++)
        {
                std::cout << A[i] << " "; 
        }
std::cout << "\n";

/******Traitement*******/
//Appeler la fonction pour chaque thread prenant comme paramètre l'ID
 func(NumTh);
 std::cout << "somme : "<<somme;
std::cout << "\n";  


    }

