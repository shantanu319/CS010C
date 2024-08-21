   #pragma once

#include <iostream>
#include <cstdlib>

using namespace std;
struct TreeNode{
    char key;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char key):key(key),left(nullptr),right(nullptr){}
    ~TreeNode() //recursively cleanup children
    {
      delete left;
      delete right;
    }
};

class arithmeticExpression{
  private:
    string infixExpression;
    TreeNode* root;

  public:

    arithmeticExpression(const string &);

    ~arithmeticExpression(); //destructor

    arithmeticExpression(const arithmeticExpression&) =delete; //copy constructor
    arithmeticExpression& operator=(const arithmeticExpression&) =delete; //assignment operator

    void buildTree();

    void infix();

    void prefix();

    void postfix();

 private:

    int priority(char);

    string infix_to_postfix(); 

    void infix(TreeNode *Node); 

    void prefix(TreeNode *Node);

    void postfix(TreeNode *Node);

};
