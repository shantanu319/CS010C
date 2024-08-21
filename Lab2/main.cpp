#include <iostream>
#include "IntList.h"

using namespace std;

int main() {
  IntList list;
  
  cout << "empty: " << list << endl;

  
  list.push_front(3);
  
  cout << "push front 3: " << list << endl;

  list.push_back(1);
  cout << "push back 1: " << list << endl;

  list.push_back(5);
  cout << "push back 5: " << list << endl;

  list.push_front(2);
  cout << "push front 2: " << list << endl;

  //print reverse
  list.printReverse();
  cout << endl;

  list.pop_back();
  cout << "pop back: " << list << endl;

  list.pop_front();
  cout << "pop front: " << list << endl;
  
  list.pop_back();
  cout << "pop backt: " << list << endl;

  list.pop_back();
  cout << "pop b ack: " << list << endl;
  
  list.pop_back();
  cout << "pop backt: " << list << endl;
       
  return 0;
}
