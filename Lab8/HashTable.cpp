#include "HashTable.h"
#include "WordEntry.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>

int main() { //moved main into HashTable.cpp for the zybooks submission
	// declare a few needed variables for inputing the data
	string line;    
	int score;
	string message = " ";
	
	// open input file
	ifstream myfile("movieReviews.txt");
	if (myfile.fail()) {
	    cout << "could not open file" << endl;
	    exit(1);
	}
	
	//create hash table
	HashTable table(20071);
	
	while (true) {
	    myfile >> score;     // get score
	    myfile.get();        // get blank space
	    getline(myfile, line);
	    if (not myfile) {
	      if (myfile.eof()) break; // Doesn't return true unless we tried input
	      throw runtime_error("input failed");
	    }
	    int len = line.size();
	    while(len > 0) {     // identify all individual strings
	        string sub;
	        len = line.find(" ");
	        if (len > 0) {
	            sub = line.substr(0, len);
	            line = line.substr(len + 1, line.size());
	        }
	        else {
	            sub = line.substr(0, line.size() - 1);
	        }
	        table.put(sub, score); // insert string with the score
	    }
	}
	
	// after data is entered in hash function
	// prompt user for a new movie review
	while(message.length() > 0) {
	    cout << "enter a review -- Press return to exit: " << endl;
	    getline(cin, message);
	
	    // used for calculating the average
	    double sum = 0;
	    int count = 0;
	    
	    double sentiment = 0.0;
	    
	    size_t len = message.size();
	    // get each individual word from the input
	    while(len != string::npos) {
	        string sub;
	        len = message.find(" ");
	        if (len != string::npos) {
	            sub = message.substr(0, len);
	            message = message.substr(len + 1, message.size());
	        }
	        else {
	            sub = message;
	        }
	        // calculate the score of each word
	        sum += table.getAverage(sub);
	        ++count;
	    }
	
	    if (message.size() > 0) {
	    	sentiment = sum / count;
	        cout << "The review has an average value of " << sentiment << endl;
	        if (sentiment >= 3.0) {
	        	cout << "Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 2.0) {
	        	cout << "Somewhat Positive Sentiment" << endl;
	        }
	        else if (sentiment >= 1.0) {
	        	cout << "Somewhat Negative Sentiment" << endl;
	        }
	        else {
	        	cout << "Negative Sentiment" << endl;
	        }
	        cout << endl;
	    }
	}
	
	return 0;
}

HashTable::HashTable(int s)
{
  size = s;
  hashTable = new list<WordEntry>[size]; //dynamically allocate array of lists
}

HashTable::~HashTable() //deletes dynamically allocated array
{
	delete[] hashTable;
}


//ChatGPT gave me something called DJB2 , I edited it slightly, adding the "% size" at the return so it can fit the size of the hash table 
unsigned HashTable::computeHash(const string &s) const //hash function
{
  unsigned long hash = 5381; // Initial value

  for (char c : s)
  {
    hash = ((hash << 5) + hash) + static_cast<unsigned int>(c); // hash * 33 + c
  }

  return (static_cast<unsigned int>(hash)) % size;
}

void HashTable::put(const string &s, int score) //adds a new item to the hash table or updates the number of appearances if already there
{
  int slotIndex = computeHash(s); 

  if (contains(s)) //if contained in hash table
  {
    for (auto curr = hashTable[slotIndex].begin(); curr != hashTable[slotIndex].end(); curr++) //iterate through slot which would contain string
    {
      if (curr->getWord() == s) //update appearances when found
      {
        curr->addNewAppearance(score);
      }
    }
  }
  else //if not in hashtable, initialize new WordEntry and append it to the LL in the right slot
  {
    WordEntry toInput = WordEntry(s, score); 
    hashTable[slotIndex].push_back(toInput);
  }
}

double HashTable::getAverage(const string &s) const //retrieves average of a specified wordEntry
{
  if (contains(s)) //only work to iterate through LL in the right slot if it exists, otherwise return 2.0 (default value)
  {
    int slotIndex = computeHash(s);
    for (auto curr = hashTable[slotIndex].begin(); curr != hashTable[slotIndex].end(); curr++)
    {
      if (curr->getWord() == s) //return average when found
      {
        return curr->getAverage();
      }
    }
  }
  return 2.0;
}

bool HashTable::contains(const string &s) const
{
  int slotIndex = computeHash(s);
  for (auto curr = hashTable[slotIndex].begin(); curr != hashTable[slotIndex].end(); curr++) //iterate through linkedList at the slot the item would be at
  {
    if (curr->getWord() == s) //return true if found
    {
      return true;
    }
  }
  return false;
}
