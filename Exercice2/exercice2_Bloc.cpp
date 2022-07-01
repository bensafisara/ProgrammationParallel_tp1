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
-version par bloc
-Pour compiler : g++ -pthread exercice2_Bloc.cpp -o bloc.x
-Pour Executer : time ./bloc.x 10 4
*/

/***Déclarations***/
int N,NumTh;
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





/***La fonction qui effectue le produit***/
void Calcul_Par_bloc(int id){
//pour chaque bloc créer un nombre de thread 
//NumTh nombre de thread par bloc //taille nombre de bloc 
int taille= N/NumTh;
int fin ;                       // calcule de reste de block
int debut = id * taille ;           // calcule de debut de block

if((id+1)==NumTh){

       fin=N-1;

  }else{

      fin=((id*taille)+(taille))-1;
  }      // calcule de la fin de block
//Exemple la taille est 2 car 10(N)/4(thread) donne 2.5 et id du thread est 2
// => (2*2)+2=6-1=5 2*2 le début on ajoute la taille et on enlève 1 car matrice commence de 0


for(int i = debut;i<=fin;i++) //cela est valable que pour les lignes car je divise les lignes en blocs
  {
    for(int j=0;j<N;j++)
    {   RES[i][j]=0;   
        for(int x=0; x<N; x++)
        {
         RES[i][j]  += A[i][x] * B[x][j];
        } 
     } 
    } 
}
/***Fonction qui fait appelle aux threads pour faire le produit parallèle par bloc***/
 void funcbloc(int NumTh){

  /*****Declaration & initialisation*****/
  std::thread workers[NumTh];
  int i;
  
  

  /*****************Traitment*************/
  for(i=0;i<NumTh;i++)
    {
      
                    workers[i]= std::thread(Calcul_Par_bloc,i);
                    workers[i].join();

    }
    
   
 /*********Afficher Résultat C************/

std::cout << "Resultat \n" << endl;
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                std::cout << RES[i][j] << " ";
            }
            std::cout <<endl;
            } 


  }



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
/********allocation des matrix*********/
   //Allocate

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



//Remplir les Matrices
generateRandomMatrice(A,N,1,99);
generateRandomMatrice(B,N,1,99);


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


std::cout << "\n";
std::cout << "\n";
auto start = high_resolution_clock::now();
funcbloc(NumTh);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop-start);
std::cout<<"Sec : " <<duration.count()<<std::endl;

    return 0;
}