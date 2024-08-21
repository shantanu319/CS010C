#include "Tree.h"
#include <iostream>
#include <string>

using namespace std; 

Tree::Tree()
{
  root = NULL;
}

Tree::~Tree()
{
  destructorHelper(root);
}

void Tree::destructorHelper(Node *node) //recursively deallocates all nodes, called in the destructor
{
  if (node == nullptr)
  {
    return;
  }
  destructorHelper(node->left);
  destructorHelper(node->middle);
  destructorHelper(node->right);

  delete node;
}

bool Tree::noChildren(Node *node) const //returns true if a node has no children
{
  return (node->left == nullptr);
}

void Tree::insert(const string &word) //iteratively inserts into btree, only works until 3 layers
{
  if (root == nullptr)
  {
    root = new Node(word);
  }
  else
  {
    insert(root, word);
  }
}

void Tree::insert(Node *curr, const string &word) //helper function to iteratively insert
{
  Node *parent = nullptr;
  while (curr != nullptr) // iteratively moves through btree looking for appropriate leaf (or lack thereof)
  {
    if (noChildren(curr)) // checks for leaf
    {
      if (curr->numData == 1) // leaf with 1 element case
      {
        addData(curr, word);
        return;
      }
      else if (curr->numData == 2 && parent == nullptr) // full root case (can't throw anything back up to the parent)
      {
        if (word < curr->small) // split and insertion when smaller
        {
          root = new Node(curr->small);
          root->left = new Node(word);
          root->middle = new Node(curr->large);
        }
        if (word > curr->large) // split and insertion when larger
        {
          root = new Node(curr->large);
          root->left = new Node(curr->small);
          root->middle = new Node(word);
        }
        if (word < curr->large && word > curr->small) // split and insertion when in the middle of the two values
        {
          root = new Node(word);
          root->left = new Node(curr->small);
          root->middle = new Node(curr->large);
        }
        delete curr; //curr node is being split and is not reused so it needs to be deallocated
        return;
      }
      else if (curr->numData == 2 && parent->numData == 1) // full leaf with non-full parent
      {
        if (word < parent->small) //checks if we are on the left subtree
        {
          if (word < curr->small) // word is less than currs keys
          {
            addData(parent, curr->small);
            parent->right = parent->middle;
            parent->middle = new Node(curr->large);
            parent->left = new Node(word);
          }
          else if (word > curr->small && word < curr->large) // word is between currs keys
          {
            addData(parent, word);
            parent->right = parent->middle;
            parent->middle = new Node(curr->large);
            parent->left = new Node(curr->small);
          }
          else // word is larger than all of currs keys
          {
            addData(parent, curr->large);
            parent->right = parent->middle;
            parent->middle = new Node(word);
            parent->left = new Node(curr->small);
          }
        }
        else if (word > parent->small) //insert logic for being on the middle subtree 
        {
          if (word < curr->small) // word is less than curr's keys but we are branching to the right of the tree now
          {
            addData(parent, curr->small);
            parent->middle = new Node(word);
            parent->right = new Node(curr->large);
          }
          else if (word > curr->small && word < curr->large) // word is in the middle of currs keys on the right subtree oft he parnet
          {
            addData(parent, word);
            parent->middle = new Node(curr->small);
            parent->right = new Node(curr->large);
          }
          else // word is greater than currs keys but we are on the right
          {
            addData(parent, curr->large);
            parent->middle = new Node(curr->small);
            parent->right = new Node(word);
          }
        }
        delete curr;
        return;
      }
    }
    else if (word < curr->small) //iterate down left subtree if spot to insert has not been found
    {
      parent = curr;
      curr = curr->left;
    }
    else if (word > curr->large && curr->numData == 2) //iterate down right subtree
    {
      parent = curr;
      curr = curr->right;
    }
    else //iterate down middle subtree
    {
      parent = curr;
      curr = curr->middle;
    }
  }
}

void Tree::addData(Node *addHere, const string &word) // handles the logic of insert keys into nodes which only have 1 key
{
  if (addHere->numData == 1) // we would never be inserting into an empty node (Node class handles it)
  {
    if (word < addHere->small) //new word is smaller than the existing word
    {
      addHere->large = addHere->small;
      addHere->small = word;
    }
    if (word > addHere->small) //new word is larger than the existing word
    {
      addHere->large = word;
    }
    addHere->numData++; //always increment numData if increasing the number of elements in the node
  }
}

void Tree::preOrder() const
{
  preOrder(root);
  cout << endl;
}

void Tree::preOrder(const Node *curr) const //parametrized helper function for preorder print
{
  if (curr == nullptr) //base case
  {
    return;
  }
  else if (curr->numData == 2) //maintains preorder when node has 2 items
  {
    cout << curr->small << ", ";
    preOrder(curr->left);
    cout << curr->large << ", ";
    preOrder(curr->middle);
    preOrder(curr->right);
  }
  else if (curr->numData == 1) //node has 1 item
  {
    cout << curr->small << ", ";
    preOrder(curr->left);
    preOrder(curr->middle);
  }
}

void Tree::inOrder() const
{
  inOrder(root);
  cout << endl;
}

void Tree::inOrder(const Node *curr) const //parametrized helper function for inorder print
{
  if (curr == nullptr) //base case
  {
    return;
  }
  if (curr->numData == 2) //maintains inorder when node has 2 items
  {
    inOrder(curr->left);
    cout << curr->small << ", ";
    inOrder(curr->middle);
    cout << curr->large << ", ";
    inOrder(curr->right);
  }
  if (curr->numData == 1) //node has 1 item
  {
    inOrder(curr->left);
    cout << curr->small << ", ";
    inOrder(curr->middle);
  }
}

void Tree::postOrder() const
{
  postOrder(root);
  cout << endl;
}

void Tree::postOrder(const Node *curr) const //parametrized helper function for postOrder printing
{
  if (curr == nullptr) //base case
  {
    return;
  }
  if (curr->numData == 2) //maintains postorder when node has 2 items
  {
    postOrder(curr->left);
    postOrder(curr->middle);
    cout << curr->small << ", ";
    postOrder(curr->right);
    cout << curr->large << ", ";
  }
  if (curr->numData == 1) //node has 1 item
  {
    postOrder(curr->left);
    postOrder(curr->middle);
    cout << curr->small << ", ";
  }
}

void Tree::remove(const string &word) //function that removes keys from the 2-3 btree
{
  if (!root) // Nothing to do in an empty tree, just return
  {
    return;
  } 

  Node* item = search(root, word); //search for the node with the key, break if it doesn't exist
  if (item == nullptr) {return;}

  if (item == root) //root is special case, ran out of time so hardcoded cases with only 3 inserts(ie item is root or rootLeft/rootRight)
  { 
    if (noChildren(item) && item->numData == 2) {deleteFromLeafNode(item, word);} //root has no children and 2 keys
    else if (noChildren(item) && item->numData == 1) //root has no children and 1 key, delete the node and set root = nullptr
    {
      delete root;
      root = nullptr;
    }
    else if (item->numData == 1 && !noChildren(item))
    {
      item->left->large = item->middle->small;
      item->left->numData++;
      root = item->left;
      delete item;
    }
    return;
  }

  Node* parent = getParent(word);
  if (parent->numData == 1 && hasTwoChildSibling(parent)) //check if parent has 2 kids so we can rotate from one side to the other (these are two of the 3-insert cases)
  {
    if (item == parent->left) //rotating left
    {
      parent->large = parent->middle->small;
      parent->numData++;
      delete parent->left;
      delete parent->middle;
      parent->left = nullptr;
      parent->middle = nullptr;
    }
    if (item == parent->right) //rotating right
    {
      parent->large = parent->small;
      parent->small = parent->left->small;
      parent->numData++;
      delete parent->left;
      delete parent->middle;
      parent->left = nullptr;
      parent->middle = nullptr;
    }
  }

}

// remove helpers
void Tree::fix(Node *emptyNode) //was not able to finish writing this
{
}

bool Tree::hasTwoChildSibling(Node *sibling) const //checks if a node has 2 keys in it, as this means it has to have 3 children, so 2 siblings for each child
{
  return (sibling->numData == 2);
}

void Tree::deleteFromLeafNode(Node* node, const string& key) //helper function to delete keys from leaf nodes
{
  if (node->numData == 1) //single key case
  {
    if (node->small == key) //if key is in single key node, numData = 0 (creating a hole)
    {
      node->numData--;
    }
  }
  if (node->numData == 2) //full leaf node case
  {
    if (node->small == key) //rearranging data if necessary
    {
      node->small = node->large;
      node->numData--;   
    }
    else if (node->large == key) //large key case
    {
      node->numData--;
    }
  }
}

Node* Tree::getParent(const string &key) //iteratively finds the parent node of a key
{
  Node *parent = nullptr;
  Node *curr = root;
  while (curr != nullptr) //loop to search through binary tree
  {
    if (curr->large == key || curr->small == key) {return parent;} //return parent if found
    else if (curr->numData == 1) //ensures that we get traversal to the middle or left in the case that there's one key
    {
      parent = curr;
      if (key > curr->small) {curr = curr->middle;}
      else {curr = curr->left;}
    }
    else if (curr->numData == 2) //separate cases for having 2 keys
    {
      parent = curr;
      if (key > curr->large) {curr = curr->right;} //go to the right
      else if (key > curr->small && key < curr->small) {curr = curr->middle;} //goes to the middle only if small < key < large
      else{curr = curr->left;}
    }
  }
  return nullptr;
}

// end of remove helpers
Node *Tree::search(const string &word)
{
  return search(root, word);
}

Node *Tree::search(Node *curr, const string &word) //search function with node parameter allowing us to start search from a specific node
{
  if (curr == nullptr) //base case 1
  {
    return nullptr;
  }
  if (curr->small == word || curr->large == word) // base case 2, found node
  {
    return curr;
  }
  if (word < curr->small) //iterate to the left 
  {
    return search(curr->left, word);
  }
  if (curr->numData == 2 && word > curr->large) //iterate right case
  {
    return search(curr->right, word);
  }
  else //else iterate middle 
  {
    return search(curr->middle, word);
  }
}
