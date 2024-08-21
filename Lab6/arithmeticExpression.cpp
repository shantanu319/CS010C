#include <iostream>
#include <sstream>
#include <stack>

#include "arithmeticExpression.h"

using namespace std;

arithmeticExpression::arithmeticExpression(const string& expression)
  : infixExpression(expression),
    root(nullptr)
{
}

arithmeticExpression::~arithmeticExpression() //deletes root, triggers TreeNode destructor to recursively destroy left and right
{
    delete root;
}

void arithmeticExpression::buildTree() { //function builds the tree by continually building the chars of the infix string into nodes, and then combining them into trees 
    string pfixExp = infix_to_postfix();
    stack<TreeNode*> stackOfTrees;
    for (unsigned i = 0; i < pfixExp.size(); i++) //loop to fill up the stack and in the process build up the arithmetic expression tree
    {
        if (pfixExp[i] == '+' || pfixExp[i] == '-' || pfixExp[i] == '*' || pfixExp[i] == '/') //if we find an operator, pop them off and combine with the last two items to form a tree 
        {                                                                                     
            TreeNode* operand = new TreeNode(pfixExp[i]);
            operand->right = stackOfTrees.top();
            stackOfTrees.pop();
            operand->left = stackOfTrees.top();
            stackOfTrees.pop();
            stackOfTrees.push(operand);
        }
        else //else its just an operand so push it onto the stack
        {
            stackOfTrees.push(new TreeNode(pfixExp[i]));
        }
    } 
    root = stackOfTrees.top(); //points the root to the tree inside of the stack, it would be the only one in the stack (as such at the top) 
}

void arithmeticExpression::infix() { //calls private parametrized infix method
    infix(root);
}

void arithmeticExpression::prefix() { //calls private parametrized prefix method
    prefix(root);
}

void arithmeticExpression::postfix() { //calls private parametrized postfix method
    postfix(root);
}

void arithmeticExpression::infix(TreeNode *Node) //parametrized infix traversal helper, does inorder traversal
{
    if (Node == nullptr) {return;} //base case, stops printing on hitting a nullptr
    if (Node->left != nullptr){cout <<"(";} //parentheses around each whole expression (left operand right)
    infix(Node->left);
    cout << Node->key;
    infix(Node->right);
    if (Node->right != nullptr){cout <<")";}

}

void arithmeticExpression::prefix(TreeNode *Node) //parametrized prefix traversal helper, does preorder traversal
{
    if (Node == nullptr) {return;} //base case, stops printing on hitting a nullptr
    cout << Node->key;
    prefix(Node->left);
    prefix(Node->right);
}

void arithmeticExpression::postfix(TreeNode *Node) //parametrized postfix traversal helper, does postorder traversal
{
    if (Node == nullptr) {return;} //base case, stops printing on hitting a nullptr
    postfix(Node->left);
    postfix(Node->right);
    cout << Node->key;
}

int arithmeticExpression::priority(char op){ //returns priority of different operators, implemented by starter pack
    int priority = 0;
    if (op == '('){
        priority =  3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() { //converts infix string to postfix and returns, also implemented by starter pack
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if ( c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while(s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
