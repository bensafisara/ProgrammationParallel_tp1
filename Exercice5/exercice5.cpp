
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <chrono>
#include <stdlib.h>
#include <thread> 
#include <mutex>
#include <condition_variable>
using namespace std;
std::condition_variable cv ;
std::mutex m;
int counter=0;

/*
- Bensafi Sarra
-Pour compiler : g++ -pthread exercice5.cpp -o exercice5.x
-Pour Executer : ./exercice5.x
*/

void thread_barrage() { 
    std::lock_guard<mutex> lg(m);
    while(counter!=5){//Lorsque le compteur arrive à 5, il faut lâcher l’eau et notifier le van
      counter++;
      std::cout << "thread 1 => barrage remplit avec "<< counter <<endl;
      this_thread::sleep_for(1s);

        } 
      cv.notify_one();
  }
  
  

void thread_van() 
{    
    std::unique_lock <mutex> ul(m);//le van ouvre pour quand le compteur est à 5
    cv.wait(ul, []{return( counter==5)? true : false ;});
    std::cout << "thread 2 => ouvrir van" <<endl;
    counter=0;
    std::cout <<"\n ";

  }
    
    
 
int main() 
{ 
  std::thread th1(thread_van);
  std::thread th2(thread_barrage);
  th1.join(); 
  th2.join();

  return 0 ;
}
