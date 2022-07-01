#include <iostream>
#include <thread>

using namespace std;

 void f() {
 
  cout<<"Hello World Programmation ¨Para !!"<<endl;

 }

int main(int ac, char** av) {
	thread t1(f);
	thread t2(f);
	t1.join();
	t2.join();
	 return 0;
 }
