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
using namespace std;

/*
- Bensafi Sarra
-version parallèle calcul de chaque élément Pij par un thread
-Pour compiler : g++ -pthread exercice2_Para.cpp -o parallele.x
-Pour Executer : time ./parallele.x 10000 

--------------------------- 
N            time
---------------------------
10           0m0.012s
---------------------------
100          0m0.552s
---------------------------
180          0m1.745s


*/


/***Déclarations***/
int N;
int** A ;
int** B ;
int** RES ;


/***Fonction pour remplir les matrices***/
void generateRandomMatrice (int **matrix, int dim, int lowerValue, int upperValue) {
    srand(time(0));
    int i, j;
    for (i = 0; i < dim; ++i) {
        for (j = 0; j < dim; ++j) {
            matrix[i][j] = (rand() % (upperValue - lowerValue + 1)) + lowerValue;
        }
    }

}

/***Lafonction qui effectue le produit***/

void Calcul_Par_Valeur(int i, int j){

//i et j sont les index de la valeur à calculer
     for (int a=0;a<N;a++){
            
         RES[i][j]+=A[i][a]*B[a][j];
        
        }
    
    } 

/***Fonction qui fait appelle aux threads pour faire le produit parallèle***/
void funcPara(){

std::vector<std::thread> vecteur_Threads;

         for (int i=0;i<N;i++){

                for (int j=0;j<N;j++){
                    //Ici chaque thread prend une valeur afin de la calculer
                    vecteur_Threads.push_back(std::thread(Calcul_Par_Valeur,i,j));
                    
                    
                
                }
            }



for (std::thread &t: vecteur_Threads) {
                  if (t.joinable()) {
                    t.join();}
                  }


std::cout << "Resultat \n" << endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                std::cout << RES[i][j] << " ";
            }
            std::cout <<endl;
            }       


  }


 
int main(int argc, char** argv){


/***Récuperer les arguments***/
if (argc<2 || argc>2 )
  {
    std::cout <<" Erreur"<<std::endl;
    std::cout <<"il faut spécifier [La dimension de la matrix carre  N ]   \n"<<std::endl;
   

  }else
  {
    N=atoi(argv[1]);
    
  }
/***allocation des matrix***/
    int i,j = 0;

    A=(int **)malloc( N*sizeof(int *));     
    for(i=0;i<N;i++){
    A[i]=(int *)malloc( N*sizeof(int ));

    }

    B=(int **)malloc(N*sizeof(int *));
    for(i=0;i<N;i++){
    B[i]=(int *)malloc( N*sizeof(int ));

    }

   RES=(int **)malloc( N*sizeof(int *));
    for(i=0;i<N;i++){
    RES[i]=(int *)malloc( N*sizeof(int ));
    }


/***Remplir les matrices***/

generateRandomMatrice(A,N,1,10);
generateRandomMatrice(B,N,1,10);

 

//print A et B
std::cout << "MATRICE A\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) {
                std::cout << A[i][j] << " ";
            }
            std::cout << std::endl;
        }

std::cout << "\n";
  
std::cout << "MATRICE B\n";
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++) {
                std::cout << B[i][j] << " ";
            }
            std::cout << std::endl;
        }


funcPara();


return 0;
}