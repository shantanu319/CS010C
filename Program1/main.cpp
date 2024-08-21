#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;

};

Node* newNode(const string& payload) {
    Node* node = new Node();
    node->payload = payload;
    node->next = nullptr;
    return node;
}

Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) {
        name = names.at(i);
	// Special edge case when the list is initially empty
        if (head == nullptr) {
            head = newNode(name);
            prev = head;
            //prev->next = head; 
        } else {
            prev->next = newNode(name); 
            prev = prev->next;//iterator ste[]
        }   
    }

    if (prev != nullptr)  //checks prev because empty list doesn't need, prev handled for element w/ 1 list
    {
      prev->next = head; //don't want to be updating start accidentally, the var for the front of the list should remain the same post function
    }
    
    return head;
}

// prints list from a starting node
void print(const Node* start) { //why const? don't want to be updating start accidentally, the var for the front of the list should remain the same post function
  const Node* curr = start;
  while (curr != nullptr) {//checks against empty list, prevents undefined behavior from line 73 & 74
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

// josephus w circular list, k = num skips
Node* runGame(Node* start, int k) {
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing (next points to itself)
        for (int i = 0; i < k; ++i) { // find kth node
          prev = curr; // would stop with curr = kth node
          curr = curr->next;
        }

        // delete kth node, using prev to hold 
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
        
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;

    if (!cin) throw runtime_error("error reading n and k from input"); //input error handling
    
    while (cin >> name && name != ".") { names.push_back(name);} // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    
    if (lastPerson != nullptr) {
        cout << lastPerson->payload << " wins!" << endl;
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}