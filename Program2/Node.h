#pragma once

#include <string>
#include <iostream>

using namespace std;

struct Node {
  string key;
  int count; //counts how many of that string are stored, ie count == 4, this is the 4th of that string
  Node *left;
  Node *right;

  Node();
  Node(const string& s);

  ~Node();
  Node(const Node& other) = delete;
  Node& operator=(const Node &rhs) = delete;
};

std::ostream& operator<< ( std::ostream &os, const Node &a );

