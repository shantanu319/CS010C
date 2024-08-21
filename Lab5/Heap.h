#pragma once
#include "PrintJob.h"

const int MAX_HEAP_SIZE = 10;

class Heap {
private:
  PrintJob* arr[MAX_HEAP_SIZE];      // Notice this is an array of PrintJob pointers
  int numItems;  // current number of items in heap

public:
  /* Initializes an empty heap.*/
  Heap();

  Heap(const Heap&) =delete; //copy constructor
  Heap& operator=(const Heap&) =delete; //assignment operator

  /* Inserts a PrintJob to the heap without
  violating max-heap properties.*/
  void enqueue(PrintJob* job);

  /* Removes the node with highest priority from the heap. 
  Follow the algorithm on priority-queue slides. */
  void dequeue();

  /* Returns the node with highest priority.*/
  PrintJob* highest() const;

  /* Prints the PrintJob with highest priority in the following format:
     Priority: priority, Job Number: jobNum, Number of Pages: numPages
     (Add a new line at the end.) */
  void print() const;

private:
  /* This function is called by dequeue function
     to move the new root down the heap to the 
     appropriate location. */
  void trickleDown(int);
  
 
  void trickleUp(int); //called by the enqueue function and used to move the last item up
  void swap(int one, int two);
};
