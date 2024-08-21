    #pragma once
#include <string>
#include <cstdlib>
#include "Node.h"

using namespace std;

class AVLTree
{
    private:
        Node* root;    

    public:
        AVLTree() : root(nullptr) {} 
        ~AVLTree(); 
        AVLTree(const AVLTree&) =delete;
        AVLTree& operator=(const AVLTree&) =delete;

        void insert(const string& key);
        int balanceFactor(Node* node); 
        void printBalanceFactors(); 
        //did not implement the visualizers

    private:
        Node* findUnbalancedNode(Node* node);
        void rotate(Node* node);
        void rotateLeft(Node* node);
        void rotateRight(Node* node);
        void printBalanceFactors(Node* node); 
        void teardown(Node* node); 
        void updateHeight(Node* node);
        void setChild(Node* parent, string rOrL, Node* child);
        void replaceChild(Node* parent, Node* child, Node* newChild);
};
