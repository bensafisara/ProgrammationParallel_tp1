
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread> 
#include <mutex>
#include <condition_variable>
using namespace std;
std::condition_variable cv1 ;
std::condition_variable cv2 ;
std::mutex m;
int count=0;
int number = 81;

/*
- Bensafi Sarra
-Pour compiler : g++ -pthread exercice4_2.cpp -o exercice4_2.x
-Pour Executer : ./exercice4_2.x
*/
 
void thread_impair(){    while(count < number) {
     std::unique_lock <mutex> ul1(m);
    cv1.wait(ul1, []{return(count % 2 != 0 )? true : false ;});
    std::cout << "thread impair: "<< count <<endl;
    count++;
    cv2.notify_one();

		}	
		
  	
  std::cout <<"\n ";
  std::cout <<"\n ";
} 


void thread_pair() 
{    while(count < number) {
     std::unique_lock <mutex> ul2(m);
     cv2.wait(ul2, []{return(count % 2 != 1 )? true : false ;});
    std::cout << "thread pair: "<< count <<endl;
    count++;
    cv1.notify_one();

    } 
  std::cout <<"\n ";
  std::cout <<"\n ";
} 


int main() 
{ 
	std::thread th2(thread_impair);
	std::thread th1(thread_pair); 

	th1.join(); 
	th2.join();

  return 0 ;
}
