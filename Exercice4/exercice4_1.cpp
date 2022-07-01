
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread> 
int number = 100;


/*
- Bensafi Sarra
-Pour compiler : g++ -pthread exercice4_1.cpp -o exercice4_1.x
-Pour Executer : ./exercice4_1.x

*/

// thread 2
void thread_Deux() 

{   
     int count=0;
    
   	 while(count <number ){
  		if ( count % 2 != 0 )
  		{
  			std::cout << count <<" ";
		}	
		count++;
  	}
  std::cout <<"\n ";
  std::cout <<"\n ";
} 

// thread 1
void thread_Un() 
{ 
	
  for(int i = 0; i <= number; i++)
  	{
  		if ( i % 2 == 0 )
  		{
  			std::cout << i <<" ";
		}	
  	}

std::cout <<"\n ";
std::cout <<"\n ";
} 


int main() 
{ 
	
	std::thread  th1(thread_Un); 
  

	std::thread th2(thread_Deux); 


	th1.join(); 
	th2.join();

  return 0 ;
}
