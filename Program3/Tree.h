#pragma once

#include "Node.h"

using std::string;

class Tree {
private:
  Node* root;
public:
  Tree();
  ~Tree(); 
  Tree(const Tree&) = delete;
  Tree& operator=(const Tree&) = delete;
  
  void insert( const string & ); 
  void preOrder() const; 
  void inOrder() const; 
  void postOrder() const; 
  void remove( const string & );
  Node* search( const string & Node); 
private:
  bool noChildren(Node* curr) const; 
  void insert(Node* curr, const string& word);
  void addData(Node* addHere, const string& word); 
  void preOrder(const Node* curr) const; 
  void inOrder(const Node* curr) const; 
  void postOrder(const Node* curr) const; 
  void fix(Node* emptyNode);
  bool hasTwoChildSibling(Node* sibling) const;
  bool empty() const {return root == nullptr;} 
  Node* search(Node* curr, const string& word);
  void destructorHelper(Node* node); 
  Node* getParent(const string& key);
  void deleteFromLeafNode(Node* node, const string& key);
  //Not written, did not get time
  Node* getLeftSibling(const string& key);
  Node* getRightSibling(const string& key);
  void rotateRightFromLeaf(const string& key);
  void rotateLeftFromLeaf(const string& key);
};
