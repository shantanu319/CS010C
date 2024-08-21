#include <iostream>
#include "Heap.h"

using std::runtime_error;
using namespace std;

Heap::Heap()
    : numItems(0)
{
}

void Heap::enqueue(PrintJob *job) //inserts items into back of heap array, percolates them up until they are at the right level
{
  if (numItems + 1 > MAX_HEAP_SIZE) {throw runtime_error("Can't add to a full heap");} //throw exception if enqueueing onto full heap
  else 
  {
    if (numItems == 0) // if heap is empty just new job is root
    {
      arr[0] = job;
    }
    else
    {
      arr[numItems] = job; //insert into back of array
      trickleUp(numItems); //trickle up
    }
    numItems++; //increment num items
  }
}

void Heap::trickleUp(int toPercU) //Helper function to percolate items up 
{
  while (toPercU > 0) //toPercU is the location of the job as it is trickled up, so when < 0 it has reached the top 
  {
    int parent = (toPercU - 1) / 2; //keeps track of parent index
    if (arr[toPercU]->getPriority() <= arr[parent]->getPriority()) //checks if in the correct place in heap array
    {
      return;
    }
    else
    {
      swap(toPercU, parent); //swaps items to move them through the array and follow Heap logic
      toPercU = parent;
    }
  }
}

void Heap::dequeue() //removes top item from heap, moves last item to front, percolates it down so that heap logic is maintained
{
  if (numItems != 0) {throw runtime_error("Attempting to dequeue on empty stack");} //can't remove from empty heap
  else
  {
    if (numItems != 1) //only replaces back with front if array length is > 1, because otherwise swap is pointless
    {
      arr[0] = arr[numItems - 1];
    }
    numItems--; 
    trickleDown(0); 
  }
}

void Heap::trickleDown(int toPercD) //Helper function to percolate items down
{
  int childIndex = (2 * toPercD) + 1;
  PrintJob* joblisting = arr[toPercD];
  while (childIndex < numItems) //childIndex is the location of the job as it is trickled up, so when < 0 it has reached the end of the array  
  {
    PrintJob* max = joblisting;
    int maxIndex = -1;
    for (int i = 0; i < 2 && childIndex < numItems; i++) //loop for checking with both children of the parent
    {
      if (arr[i + childIndex] > max)
      {
        max = arr[i + childIndex];
        maxIndex = i + childIndex;
      }
    }

    if (max == joblisting) //return if it has been percolated down to the right place
    {
      return;
    }
    else //swap and update child index because the job isn't in the right place
    {
      swap(toPercD, maxIndex);
      toPercD = maxIndex;
      childIndex = 2 * toPercD + 1;
    }
  }
}

PrintJob *Heap::highest() const //returns top of heap 
{
  if (numItems == 0) {return nullptr;} //returns null if empty
  return arr[0];
}

void Heap::print() const //prints highest item
{
  if (numItems == 0) //prints nothing if empty heap
  {
    cout << "" << endl;
  }
  else
  {
    cout << "Priority: " << highest()->getPriority() << ", Job Number: " << highest()->getJobNumber();
    cout << ", Number of Pages: " << highest()->getPages() << endl;
  }
}

 
void Heap::swap(int one , int two) //helper function for swapping elements inside the heap array
{
  PrintJob* variableStore = arr[one];
  arr[one] = arr[two];
  arr[two] = variableStore;
}


