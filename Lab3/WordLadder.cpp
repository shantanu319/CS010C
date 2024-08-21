#include "WordLadder.h"
#include <iostream>
#include <fstream>

// This gives us access to std::stack and std::queue.  
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

bool WordLadder::differenceCheck(string& lhs, const string& rhs) const //function that returns true if the parameter words have exactly 1 difference
{
  int numChanges = 0;
  for (unsigned int i = 0; i < 5; i++) //because input is of length 5, loops five times
  {
    if(lhs[i] != rhs[i]) //per-letter check
    {
      numChanges++;
    } 
  }
  return (numChanges == 1); //ret true if = to 1
}


WordLadder::WordLadder(const string& filename) {
  ifstream infs;
  infs.open(filename);
  
  if(infs.fail()) //file error handling
  {
    throw runtime_error("Error opening dictionary file");
  }

  string inputVar;
  while (infs >> inputVar) // loop to push items of length 5 to list<string> dict
  {
    if (inputVar.size() != 5) //input error check
    {
      throw runtime_error("Error with input: length is not equal 5 chars");
    }
    else
    {
      dict.push_back(inputVar);
    } 
  }
  infs.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  
  ofstream outfs;
  outfs.open(outputFile);
  if (outfs.fail()) // check for valid output file
  {
    throw runtime_error("Failed to open output file");
  }

  //check for valid start and end inputs
  if (!(std::find(dict.begin(),dict.end(),start) != dict.end()) || !(std::find(dict.begin(),dict.end(),end) != dict.end()))
  {
    throw runtime_error("Either start or end are not in dict");
  }

  //set up queue of stacks and beginning of ladder
  stack<string> firstWordStack;
  queue<stack<string>> QofStacks;
  firstWordStack.push(start);
  QofStacks.push(firstWordStack);

  if (start == end) //base check
  {
    outfs << start << endl;
  }
  else
  {
    while (!QofStacks.empty()) //access main queue until empty
    {
      stack<string> frontStack = QofStacks.front();
      string frontWord = frontStack.top(); //word on top of front stack 

      auto it = dict.begin();
      while(it != dict.end()) //iterate through dictionary, using while loop as it let me bypass the iterator error
      {
        const string& x = *it;
        if (differenceCheck(frontWord, x)) //check for single letter difference
        {
          stack<string> copyStack = frontStack;
          copyStack.push(x);
          if (x == end) // check if end condition
          {
            vector<string> reversedLadder; //printing in opposite order to account for stack direction
            
            while (!copyStack.empty()) //copies to vector
            {
              reversedLadder.push_back(copyStack.top());
              copyStack.pop();
            }
            //output word ladder here
            for(int i = reversedLadder.size() - 1; i >= 0; i--) //prints in reverse from vector to output file
            {
              outfs << reversedLadder.at(i) << endl;
            }
            return;
          }
          else
          {
            QofStacks.push(copyStack);
            it = dict.erase(it);
          }
        }
        else
        {
          it++;
        }
        
      }
      QofStacks.pop();
    }

    if (QofStacks.empty()) //empty check, it returns if a word ladder is found before this point
    {
      outfs << "No Word Ladder Found." << endl;
    }
  }
  outfs.close();
}