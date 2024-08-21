#include "BSTree.h"

#include <iostream>
#include <stdexcept>

using namespace std;

void BSTree::insert(const string &key) // iteratively inserts a node into the tree
{
  if (empty()) // if tree is empty
  {
    root = new Node(key);
    return;
  }
  else
  {
    Node *currNode = root;
    while (currNode != nullptr) // iterate through tree
    {
      if (currNode->key == key) // already in tree
      {
        currNode->count += 1;
        return;
      }
      else if (key < currNode->key) // insert/move down left
      {
        if (currNode->left == nullptr) // checks if a hole exists to insert new node
        {
          currNode->left = new Node(key);
          return;
        }
        currNode = currNode->left;
      }
      else if (key > currNode->key) // insert/move down right
      {
        if (currNode->right == nullptr) // checks if a hole exists to insert new node
        {
          currNode->right = new Node(key);
          return;
        }
        currNode = currNode->right;
      }
    }
  }
}

bool BSTree::search(const string &key) const // iteratively searches for a key
{
  if (root != nullptr) // key cannot exist in an empty tree
  {
    Node *currentNode = root;      // holds node being checked
    while (currentNode != nullptr) // allows us to loop through BST
    {
      if (key == currentNode->key) // returns true if node is found
      {
        return true;
      }
      else if (key < currentNode->key) // move to the right side of the tree
      {
        currentNode = currentNode->left;
      }
      else if (key > currentNode->key) // move to the left side of the tree
      {
        currentNode = currentNode->right;
      }
    }
  }
  return false;
}

string BSTree::largest() const
{
  if (empty()) // empty case
  {
    return "";
  }
  else
  {
    Node *currentNode = root;
    while (currentNode->right != nullptr) // keeps going to the right, until it can't
    {
      currentNode = currentNode->right;
    }
    return currentNode->key; // returns rightmost because its largest in bst
  }
}

string BSTree::smallest() const
{
  if (empty()) // empty case
  {
    return "";
  } // empty case
  else
  {
    Node *currentNode = root;
    while (currentNode->left != nullptr) // keeps going to the left, until it can't
    {
      currentNode = currentNode->left;
    }
    return currentNode->key; // returns leftmost because its smallest in bst
  }
}

int BSTree::height(const string &key) const // first search for key, then use height_of to find the height to there
{
  if (search(key)) // not found in tree case, accounts for empty because search has case inside it
  {
    Node *currentNode = root;      // holds node being checked
    while (currentNode != nullptr) // allows us to loop through BST
    {
      if (key == currentNode->key) // found
      {
        return height_of(currentNode); // return height from node to bottom
      }
      else if (key < currentNode->key)
      {
        currentNode = currentNode->left;
      }
      else
      {
        currentNode = currentNode->right;
      }
    }
  }
  return -1;
}

int BSTree::height_of(Node *tree) const // counts from the node to the bottom of the tree
{
  if (tree == nullptr) // if empty return -1
  {
    return -1;
  }
  else // not empty, keep going down the height of the tree recursively, adding 1 for each existing node (on either side)
  {
    int rheight = height_of(tree->right);
    int lheight = height_of(tree->left);
    return 1 + max(lheight, rheight);
  }
}

void BSTree::remove(const string &key) // calls the remove helper with nullptr and root as parameters
{
  remove(nullptr, root, key);
}

void BSTree::remove(Node *parent, Node *tree, const string &key)
{
  if (!search(key)) // search contains empty case
  {
    return;
  }
  else
  {
    if (tree->key == key) // if current node is the one to be deleted
    {
      if (tree->count > 1) // in case that count is > 1
      {
        tree->count -= 1;
      }
      else if (tree->right == nullptr && tree->left == nullptr) //  leaf node case
      {
        if (parent == nullptr) // root is leaf node
        {
          delete root;
          root = nullptr;
        }
        else if (parent->left == tree) // parent's left is leaf node
        {
          delete parent->left;
          parent->left = nullptr;
        }
        else // parent's right is a leaf node
        {
          delete parent->right;
          parent->right = nullptr;
        }
      }
      else if (tree->right == nullptr) // deleting a node with only a left child
      {
        if (parent == nullptr) // root node being deleted
        {
          root = tree->left;
        }
        else if (parent->left == tree) // deleting node on left of parent
        {
          parent->left = tree->left;
        }
        else // deleting node on right of parent
        {
          parent->right = tree->left;
        }
      }
      else if (tree->left == nullptr) // deleting a node with only a right child
      {
        if (parent == nullptr)
        {
          root = tree->right;
        }
        else if (parent->left == tree) // deleting node on left of parent
        {
          parent->left = tree->right;
        }
        else // deleting node on right of parent
        {
          parent->right = tree->right;
        }
      }
      else // case for two children (general case)
      {
        Node *successor = tree->right;
        Node *successorParent = tree;

        while (successor->left != nullptr) // Find in-order successor (smallest in subtree)
        {
          successorParent = successor;
          successor = successor->left;
        }

        tree->key = successor->key; // replace information from successor to tree
        tree->count = successor->count;

        remove(successorParent, successor, successor->key); // Recursively delete the successor
      }
    }
    else // recursively goes down the right and left subtrees checking for the node to remove and performing above
    {
      if (key < tree->key) // goes to left subtree
      {
        remove(tree, tree->left, key);
      }
      else // goes to right subtree
      {
        remove(tree, tree->right, key);
      }
    }
  }
}

// for ordered prints, write the thing that finds smallest first
void BSTree::preOrder() const
{
  preOrder(root); // calls parametrized function w/ root node
}

void BSTree::postOrder() const
{
  postOrder(root); // calls parametrized function w/ root node
}

void BSTree::inOrder() const
{
  inOrder(root); // calls parametrized function w/ root node
}

void BSTree::preOrder(Node *tree) const
{
  // if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  // else
  if (tree == nullptr)
  {
    return;
  }
  else
  {
    cout << tree->key << "(" << tree->count << ")"
         << ", ";          // print key
    preOrder(tree->left);  // do left
    preOrder(tree->right); // do right
  }
}

void BSTree::postOrder(Node *tree) const
{
  // if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  // else
  if (tree == nullptr)
  {
    return;
  }
  else
  {
    postOrder(tree->left);  // do left
    postOrder(tree->right); // do right
    cout << tree->key << "(" << tree->count << ")"
         << ", "; // print key
  }
}

void BSTree::inOrder(Node *tree) const
{
  // if (tree != nullptr) {throw runtime_error("Trying to traverse empty tree");} //throw exception on empty
  // else
  if (tree == nullptr)
  {
    return;
  }
  else
  {
    inOrder(tree->left); // do left
    cout << tree->key << "(" << tree->count << ")"
         << ", ";         // print key
    inOrder(tree->right); // do right
  }
}
