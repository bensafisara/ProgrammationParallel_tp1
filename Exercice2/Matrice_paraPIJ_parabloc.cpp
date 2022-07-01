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
using namespace std::chrono;
using namespace std;

/*
- Bensafi Sarra
-calcul de du produit par les 2 versions parallèle
-Pour compiler : g++ -pthread Matrice_paraPIJ_parabloc.cpp -o matrice.x
-Pour Executer : ./matrice.x N NbTHreads
*/


int N,NumTh;
int** A ;
int** B ;
int** RES_p ;
int** RES_B ;
int** RES_seq;

void generateRandomMatrix (int **matrix, int dim, int lowerValue, int upperValue) {
    srand(time(0));
    int i, j;
    for (i = 0; i < dim; ++i) {
        for (j = 0; j < dim; ++j) {
            matrix[i][j] = (rand() % (upperValue - lowerValue + 1)) + lowerValue;
        }
    }

}
            /*********************      Partie  par Parallèle Pij     **********************/

void Calcul_Par_Valeur(int i, int j){

     for (int a=0;a<N;a++){
            
         RES_p[i][j]+=A[i][a]*B[a][j];
        
        }} 

void funcPara(){

   std::vector<std::thread> workers;

         for (int i=0;i<N;i++){

                for (int j=0;j<N;j++){

                    workers.push_back(std::thread(Calcul_Par_Valeur,i,j));
                    
                 } }



for (std::thread &t: workers) {
                  if (t.joinable()) {
                    t.join();}
                  }



std::cout << "Resultat multiplication Parallèle Pij\n" << endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                std::cout << RES_p[i][j] << " ";
            }
            std::cout <<endl;
            }       


  }




           /*********************           Partie  par Bloc                **********************/
void Calcul_Par_bloc(int id){

//calculer par un thread 
int taille= N/NumTh;
int fin ;                       // calcule de reste de block
int debut = id * taille ;           // calcule de debut de block

if((id+1)==NumTh){

       fin=N-1;

  }else{

      fin=((id*taille)+(taille))-1;
  }      
// calcule de la fin de block
//Exemple la taill est 2 car 10(N)/4(thread) donne 2.5 et id du thread est 2
// => (2*2)+2=6-1=5 2*2 le début on ajoute la taille et on enlève 1 car matrice commance de 0


for(int i = debut;i<=fin;i++) //cela est valable que pour les lignes car je divise les lignes en blocs
  {
    for(int j=0;j<N;j++)
    {   RES_B[i][j]=0;   
        for(int x=0; x<N; x++)
        {

            RES_B[i][j]  += A[i][x] * B[x][j];
        } 
     }
  
    
    } 
}

 void funcbloc(int NumTh){

  //Declaration & initialisation

  std::thread workers[NumTh];
  int i;
  
 

  //Traitment
  for(i=0;i<NumTh;i++)
    {
      
      
                    workers[i]= std::thread(Calcul_Par_bloc,i);
                    workers[i].join();

    }
    
   
//resulatat

std::cout << "Resultat Resultat multiplication Parallèle par Bloc \n" << endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                std::cout << RES_B[i][j] << " ";
            }
            std::cout <<endl;
            } 
  }






              /**********************     Main      ***********************/

 

int main(int argc, char** argv)
{
if (argc<3 || argc>3 )
  {
   
    printf("faute \n");
    cout <<"respecter l'ordre [dimension matrix carre  N ] [num threads]   \n"<<endl;
    exit(-1);
    
  }else
  {

    
    N=atoi(argv[1]);
    NumTh=atoi(argv[2]); 
    
  }
      /*****allocation des matrix*****/
    int i,j = 0;

    A=(int **)malloc( N*sizeof(int *));     
    for(i=0;i<N;i++){
    A[i]=(int *)malloc( N*sizeof(int ));

    }

    B=(int **)malloc(N*sizeof(int *));
    for(i=0;i<N;i++){
    B[i]=(int *)malloc( N*sizeof(int ));

    }

   RES_p=(int **)malloc( N*sizeof(int *));
    for(i=0;i<N;i++){
    RES_p[i]=(int *)malloc( N*sizeof(int ));
    }
     RES_B=(int **)malloc( N*sizeof(int *));
    for(i=0;i<N;i++){
    RES_B[i]=(int *)malloc( N*sizeof(int ));
    }
     
//recupérer les données et effectuer les test





 //Allocate

// je vais creer dynamiquement un vecteur de pointeur en premier lieu

generateRandomMatrix(A,N,1,99);
generateRandomMatrix(B,N,1,99);

// print A et B 
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







/**************************** SECTION PARALLELE Bloc *************************/
std::cout << "\n";
std::cout << "\n";
auto start = high_resolution_clock::now();
funcbloc(NumTh);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop-start);
std::cout<<"Sec bloc : " <<duration.count()<<std::endl;

/**************************** SECTION PARALLELE Pij *************************/
std::cout << "\n";
std::cout << "\n";
auto start1 = high_resolution_clock::now();
funcPara();
auto stop1 = high_resolution_clock::now();
auto duration1 = duration_cast<microseconds>(stop1-start1);
std::cout<<"Sec pij : " <<duration1.count()<<std::endl;    



    return 0;
}