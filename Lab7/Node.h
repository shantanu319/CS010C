    #pragma once

#include <string>

using namespace std;

struct Node
{
    string key;
    int height = -1;
    Node* parent;
    Node* left;
    Node* right;
   
    Node();
    Node(const string& key) : key(key), height(0), parent(nullptr), left(nullptr), right(nullptr) {} //inline parametrized constructor

    //using default destructor
    Node(const Node& other) = delete;
    Node& operator=(const Node &rhs) = delete;
};
