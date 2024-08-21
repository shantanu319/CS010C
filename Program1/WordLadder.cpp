#include "WordLadder.h"

#include <iostream>
#include <fstream>

// This gives us access to std::stack and std::queue.  
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

WordLadder::WordLadder(const string& filename) {
  ifstream infs;
  infs.open(filename);
  
  if(infs.fail())
  {
    throw runtime_error("Error opening file");
  }

  while (!infs.fail())
  {
    string inputVar;
    infs >> inputVar;
    if (inputVar.size() != 5)
    {
      throw runtime_error("Error with input: length is not equal 5 chars");
      break;
    }
    else
    {
      dict.push_back(inputVar);
    }
    
  }

}

// CODETURD:  To iterate through the dictionary list, we can use this loop
//    for(auto it = dict.begin(); it != dict.end(); ++it) {
//      const string& x = *it;
//
// CODETURD: We need that because we have to remove words from the dictionary
// after we use them (if we are following the zyBook algorithm), to erase, use
//
// it = dict.erase(x);
//
// CODETURD: To see if a word is in the dictionary, use
// if (std::find(dict.begin(),dict.end(),word) != dict.end()) {
//    cout << word << " is in the dictionary" << endl;
// }
//
// std::find is defined in <algorithm> (you can google more about how it works)
//
void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile) {
  // This is how we traverse the std::list dict
  for(auto it = dict.begin(); it != dict.end(); ++it) {
    // This is how we erase an entry and move to the next item (if any)
    it = dict.erase(it);
  }
}
