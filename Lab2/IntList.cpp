#include "IntList.h"

#include <iostream>
#include <exception>

using namespace std;

/*
// This is just for the throws during the
// development phase... it is a turd once
// you remove all the HERE's
#define STRINGIZE(x) #x
#define STR(x) STRINGIZE(x)
#define HERE ("Broken at\n" __FILE__ ":" STR(__LINE__) ": broken")
*/


//destructor
IntList::~IntList()
{
  if (!empty()) // no need to delete dummy nodes since dummy head and tail are local
  {
    while (dummyHead.next != &dummyTail) //pop_front from first non-dummy node to last non-dummy node
    {
      pop_front();
    }  
  }
}


ostream & operator<<(ostream &out, const IntList &rhs) {
  if(!rhs.empty()) //no need for error on empty b/c output nothing
  {
    IntNode* curr = rhs.dummyHead.next; //first actual node
    while(curr->next != &rhs.dummyTail) //iterates from first to second-to-last node
    {
      out << curr->data << " ";
      curr = curr->next;
    }
    out << curr->data; //prints last node's data
  }
  return out;
}

void IntList::push_front(int value) {
  IntNode* newNode = new IntNode(value);
  if (empty()) //list empty
  {
    dummyHead.next = newNode;
    dummyTail.prev = newNode;
    newNode->next = &dummyTail;
    newNode->prev = &dummyHead;
  }
  else
  {
    dummyHead.next->prev = newNode;
    newNode->next = dummyHead.next;
    newNode->prev = &dummyHead;
    dummyHead.next = newNode;
  }
}

void IntList::pop_front() {
  if (empty()) // only does anything if list is not empty
  {
    throw runtime_error("List empty");
  }
  else{
    IntNode* toPop = dummyHead.next;
    dummyHead.next = toPop->next;
    toPop->next->prev = &dummyHead;
    delete toPop;
  }
}

void IntList::push_back(int value) {
  if (empty()) //needs a different case for empty
  {
    push_front(value);
  }
  else
  {
    IntNode* newNode = new IntNode(value);
    dummyTail.prev->next = newNode;
    newNode->prev = dummyTail.prev;
    newNode->next = &dummyTail;
    dummyTail.prev = newNode;
  }
}

void IntList::pop_back() {
  if (empty()) // only does anything if list is not empty
  {
    throw runtime_error("List empty");
  }
  else
  {
    IntNode* toPop = dummyTail.prev;
    dummyTail.prev = toPop->prev;
    toPop->prev->next = &dummyTail;
    delete toPop;
  }
}

bool IntList::empty() const {
  return (dummyHead.next == &dummyTail); // if head.next == tail ret true, then list is empty
}

void IntList::printReverse() const {
  if (!empty()) // prints nothing if list not empty
  {
    for (IntNode* curr = dummyTail.prev; curr->prev != &dummyHead; curr = curr->prev) //iterates backward from the last to the second node
    {
      cout << curr->data << " ";
    }
    cout << dummyHead.next->data; //prints first node's data
  }
}

