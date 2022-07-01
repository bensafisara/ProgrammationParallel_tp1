#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
using namespace std;


/*
- Bensafi Sarra
-version Séquentielle
-Pour compiler : g++ exercice2_Seq.cpp  -o seq.x
-Pour Executer : ./seq.x 10
*/


int c1,r1,c2,r2;
int** A = new int*[r1];
int** B = new int*[r2];
int** RES = new int*[r1];



int main(int argc, char** argv)
{


//recupérer les données et effectuer les test

if (argc<=2){ 
    cout <<"[Un seul Argument N ,Dimension des matrices N * N ]  \n"<<endl;  
    r1=atoi(argv[1]);
    c1=r1;
    r2=r1;
    c2=r1;
   
  }else
  {
    printf("faux Erreur ! \n");
    cout <<"[Un seul Argument N ,Dimension des matrices N * N ]  \n"<<endl;
    exit(-1);
  }



 //Allocate

// je vais creer dynamiquement un vecteur de pointeur en premier lieu

int** A = new int*[r1];
 
    // allocation dynamique
    for (int i = 0; i < r1; i++) {
        A[i] = new int[c1];
    }
 
    // Affecter les valeurs 
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c1; j++) {
            A[i][j] = rand() % 100-1;
        }
    }

// je vais creer dynamiquement un vecteur de pointeur en premier lieu

int** B = new int*[r2];
 
    // / allocation dynamique
    for (int i = 0; i < r2; i++) {
        B[i] = new int[c2];
    }
 
    // affecter les valeurs 
    for (int i = 0; i < r2; i++)
    {
        for (int j = 0; j < c2; j++) {
            B[i][j] = rand() % 100;
        }
    }



// je vais creer dynamiquement un vecteur pour le résultat 

int** RES = new int*[r1];
 
    // dynamically allocate
    for (int i = 0; i < r1; i++) {
        RES[i] = new int[c2];
    }
 
   

// print A et B 
std::cout << "MATRICE A\n";
	    for (int i = 0; i < r1; i++)
	    {
	        for (int j = 0; j < c1; j++) {
	            std::cout << A[i][j] << " ";
	        }
	        std::cout << std::endl;
	    }

std::cout << "\n";
   
std::cout << "MATRICE B\n";
	    for (int i = 0; i < r2; i++)
	    {
	        for (int j = 0; j < c2; j++) {
	            std::cout << B[i][j] << " ";
	        }
	        std::cout << std::endl;
	    }

std::cout << "\n";

std::cout << "Matrice Séquentielle \n";
		//Multiplication Sequentielle et Affichage
		for (int row = 0; row < r1; row++) {
		        for (int col = 0; col < c2; col++) {
		            
		            for (int inner = 0; inner < c1; inner++) {
		                RES[row][col] += A[row][inner] * B[inner][col];
		            }
		            std::cout << RES[row][col] << "  ";
		        }
		        std::cout << "\n";
		    }


















    return 0;
}