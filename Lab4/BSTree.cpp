#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string& key) {
  if (empty()) //if tree is empty
  {
    root = new Node(key);
    return;
  }
  else
  { 
    Node* currNode = root;
    while (currNode != nullptr)
    {
      if (currNode->key == key) //already in tree
      {
        currNode->count += 1;
        return;
      }
      else if (key < currNode->key) //insert/move down left
      {
        if (currNode->left == nullptr)
        {
          currNode->left = new Node(key);
          return;
        }
        currNode = currNode->left;
      }
      else if (key > currNode->key)//insert/move down right
      {
        if (currNode->right == nullptr) 
        {
          currNode->right = new Node(key);
          return;
        }
          currNode = currNode->right;
      }
    }
  }
}

bool BSTree::search(const string& key) const {
  if (root != nullptr) //key cannot exist in an empty tree
  {
    Node* currentNode = root; //holds node being checked 
    while (currentNode != nullptr) //allows us to loop through BST
    {
      if (key == currentNode->key) { return true;} // breaks when found }
      else if (key < currentNode->key) { currentNode = currentNode->left; }
      else if (key > currentNode->key) { currentNode = currentNode->right;}
    }
  }
  return false;
}

string BSTree::largest() const {
  if (empty()) { return ""; } //empty case
  else
  {
    Node* currentNode = root;
    while (currentNode->right != nullptr) //keeps going to the right, until it can't
    {
      currentNode = currentNode->right;
    }
    return currentNode->key;
  }
}
 
string BSTree::smallest() const {
  if (empty()) { return ""; } //empty case
  else
  {
    Node* currentNode = root;
    while (currentNode->left != nullptr) //keeps going to the left, until it can't
    {
      currentNode = currentNode->left;
    }
    return currentNode->key;
  }
}

int BSTree::height(const string& key) const { //first search for key, then use height_of to find the height to there
  if (search(key)) // not found in tree case, accounts for empty because search has case inside it
  {
    Node* currentNode = root; //holds node being checked 
    while (currentNode != nullptr) //allows us to loop through BST
    {
      if (key == currentNode->key) //found
      {
        return height_of(currentNode); //subtracts height from target to bottom from total height
      }
      else if (key < currentNode->key) { currentNode = currentNode->left; }
      else { currentNode = currentNode->right;}
    }
  }
  return -1;
}

void BSTree::remove(const string& key)
{
  //remove(key); 
}

// for ordered prints, write the thing that finds smallest first
void BSTree::preOrder() const {
  preOrder(root); //calls parametrized function w/ root node
}

void BSTree::postOrder() const {
  postOrder(root); //calls parametrized function w/ root node
}

void BSTree::inOrder() const {
  inOrder(root); //calls parametrized function w/ root node
}

void BSTree::remove(Node* parent, Node* tree, const string& key) {
  // Hint: A good approach is to find the parent and the curr node that holds that key
  // Edge case: The key is not found (do nothing)
  // Edge case.  The key count is greater than 1.  Just decrement the count
  // Edge case: leaf (no children).  Just remove from parent
  //  ==> case 1: parent is nullptr (we are removing the last node from root)
  //  ==> case 2: curr is the left child, remove it from parent
  //  ==> case 3: curr is the right child, remove it from parent
  // Typical case.  Find the target
  // It is either the largest key in the left tree (if one exists)
  // or the smallest key in the right tree (since not a leaf one will exist)
  // Copy the target information into the node we found, set the target count to
  // one, and recursively remove it from left or right subtree (current node is the parent)
  parent = nullptr; //using zybooks algorithm
  Node* iteratorNode = tree;
  while (iteratorNode != nullptr)
  {
    if (iteratorNode->key == key)
    {
      if (iteratorNode->count > 1)
      {
        iteratorNode->count -= 1;
        return;
      }
      if (iteratorNode->right == nullptr && iteratorNode->left == nullptr) //this is a leaf node
      {
        if (parent == nullptr) {root == nullptr;} //root node case
        else if (parent->left == iteratorNode) { parent->left = nullptr;} //updating parent node edges to be null bc child is leaf and being removed
        else if (parent->right == iteratorNode) { parent->right = nullptr;} //same but right child is being removed
        return;
      }
      else if (iteratorNode->right == nullptr) //case that there is no right child
      {
        if (parent == nullptr) {root = iteratorNode->left;} 
        else if (parent->left == iteratorNode) {iteratorNode->left;}
        else {parent->right = iteratorNode->left;}
        return;
      }
      else if (iteratorNode->left == nullptr) //same but no left child
      {
        if (parent == nullptr) {root = iteratorNode->right;} 
        else if (parent->left == iteratorNode) {iteratorNode->right;}
        else {parent->right = iteratorNode->right;}
        return;
      }
      else //remove a node with two children 
      {
        Node* successor = iteratorNode->right;
        while (successor->left != nullptr)
        {
          successor = successor->left;
        }
        string sucData = successor->key;
        remove(key);
        
      } 
    }
  }
}  

int BSTree::height_of(Node* tree) const {
  if (tree == nullptr) {return -1;} // if empty return -1
  else //not empty, keep going down the height of the tree recursively, adding 1 for each existing node 
       //(on either side)
  {
    int rheight = height_of(tree->right);
    int lheight = height_of(tree->left);
    return 1 + max(lheight, rheight);
  }
}

void BSTree::preOrder(Node* tree) const {
  //if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  //else
  if (tree == nullptr) {return;}
  else {
    cout << tree->key << "(" << tree->count << ")" << ", "; //print key
    preOrder(tree->left); //do left
    preOrder(tree->right); //do right
  }
}

void BSTree::postOrder(Node* tree) const {
  //if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  //else
  if (tree == nullptr) {return;}
  else {
    postOrder(tree->left); //do left
    postOrder(tree->right); //do right
    cout << tree->key << "(" << tree->count << ")" << ", "; //print key
  }
}

void BSTree::inOrder(Node* tree) const {
  //if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  //else
  if (tree == nullptr){return;}
  else {
    inOrder(tree->left); //do left
    cout << tree->key << "(" << tree->count << ")" << ", "; //print key
    inOrder(tree->right); //do right
  }
}

// This is a pre-order traversal that shows the full state of the tree
// (but it is a code turd)
void BSTree::debug(Node* tree, int indent) const {
  if (tree == nullptr) return;
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << tree << ' ' << *tree << endl;
  debug(tree->left,indent+1);
  for(int i=0;i<4*indent;++i) cout << ' ';
  cout << "-" << endl;
  debug(tree->right,indent+1);
}
