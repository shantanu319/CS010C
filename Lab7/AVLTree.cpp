#include "AVLTree.h"
#include <iostream>
#include <fstream>

using namespace std;

AVLTree::~AVLTree()
{
    teardown(root);
}

void AVLTree::teardown(Node *node)
{
    if (node == nullptr) {return;}

    teardown(node->left);
    teardown(node->right);

    delete node;
}

void AVLTree::insert(const string &key) //performs a standard BST insert, then moves back up the insert path balancing as needed
{
    if (root == nullptr) //root case
    {
        Node* newNode = new Node(key);
        root = newNode;
        return;
    }
    else //general case
    {
        Node* newNode = new Node(key);
        Node* curr = root;
        while (curr != nullptr) //iterates toward insert location
        {
            if (curr->key == key) //prevents duplicate inserts
            {
                throw runtime_error("Key already exists in tree");
            }
            if (key < curr->key) //moves down left subtree if needed
            {
                if (curr->left == nullptr) //insert in hole
                {
                    curr->left = newNode;
                    newNode->parent = curr;
                    curr = nullptr;
                }
                else //continue iterating
                {
                    curr = curr->left;
                }
            }
            else if (key > curr->key) //move down right subtree
            {
                if (curr->right == nullptr) //insert in hole
                {
                    curr->right = newNode;
                    newNode->parent = curr;
                    curr = nullptr;
                }
                else //continue iterating
                {
                    curr = curr->right;
                }
            }
        }

        newNode = newNode->parent;
        while (newNode != nullptr) //iterating up the insert path, rotating and updating heights as needed
        {
            rotate(newNode);
            newNode = newNode->parent;
        }
    }
}

void AVLTree::rotate(Node *node) //updates the node's height after rotation and performs single or double rotation as needed 
{
    if (node == nullptr) //invalid input check, not really needed since insert handles the case and prevents it from happening
    {
        throw runtime_error("Rotating a non-existent node"); 
    }
    updateHeight(node);
    if (balanceFactor(node) == -2) // leaning right
    {
        if (balanceFactor(node->left) == 1) // double rotation case
        {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
    else if (balanceFactor(node) == 2) // leaning left
    {
        if (balanceFactor(node->left) == -1) // double rotation case
        {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
}

void AVLTree::rotateLeft(Node *node) //left rotation
{
    if (node == nullptr || node->right == nullptr) {return;} //nothing to rotate
    Node* rightLeftChild = node->right->left;
    if (node->parent != nullptr) //non-root case
    {
        replaceChild(node->parent, node, node->right);
    }
    else 
    {
        root = node->right;
        root->parent = nullptr;
    }
    setChild(node->right, "l", node); //sets children appropriately so the rotation happens to the left 
    setChild(node, "r", rightLeftChild);
}

void AVLTree::rotateRight(Node *node) //right rotation
{
    if (node == nullptr || node->left == nullptr) {return;} //nothing to rotate
    Node *leftRightChild = node->left->right;
    if (node->parent != nullptr) //non-root case
    {
        replaceChild(node->parent, node, node->left);
    }
    else
    {
        root = node->left;
        root->parent = nullptr;
    }
    setChild(node->left, "r", node); //sets children appropriately so that the rotation happens to the right 
    setChild(node, "l", leftRightChild);
}

void AVLTree::updateHeight(Node *node) //calculates and sets the height of a node
{
    if (node == nullptr) //no node means nothing to update
    {
        throw runtime_error("Updating height on nonexistant node");
    }
    int leftHeight = -1;
    if (node->left != nullptr) //retrieves left child's heigh
    {
        leftHeight = node->left->height;
    }
    int rightHeight = -1;
    if (node->right != nullptr) //retrieves right child's height
    {
        rightHeight = node->right->height;
    }
    node->height = max(leftHeight, rightHeight) + 1; //sets the nodes height to the greater of its right and left subtrees, adding 1 for itself
}

void AVLTree::setChild(Node *parent, string rOrL, Node *child) //sets the right or left child pointer of a node
{
    if (rOrL != "r" && rOrL != "l") //exits on invalid inputs
    {
        throw runtime_error("direction inputs");
    }

    if (rOrL == "l") //sets left child of parent node
    {
        parent->left = child;
    }
    else //right
    {
        parent->right = child;
    }

    if (child != nullptr) //updates child pointer
    {
        child->parent = parent;
    }

    updateHeight(parent); //updates parent's height especially in the case that a new child was added
}

void AVLTree::replaceChild(Node *parent, Node *child, Node *newChild) //replaces an existing child pointer with another child
{
    if (parent->left == child) //replaces left child
    {
        setChild(parent, "l", newChild);
    }
    else if (parent->right == child) //replaces right child
    {
        setChild(parent, "r", newChild);
    }
}

int AVLTree::balanceFactor(Node *node) //calculates the balance factor at each nodes
{
    if (node == nullptr) {return -1;} //in case we get the balance factor of nothing
    int leftHeight = -1;
    if (node->left != nullptr) // left subtree not there
    {
        leftHeight = node->left->height;
    }
    int rightHeight = -1;
    if (node->right != nullptr) //right subtree not there
    {
        rightHeight = node->right->height;
    }
    return leftHeight - rightHeight;
}

void AVLTree::printBalanceFactors() //calls parametrized and private print function
{
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node) //prints the nodes and their balance factors with inorder traversal
{
    Node *curr = node;
    if (curr == nullptr) //base case, stops recursing once nothing more to print
    {
        return;
    }
    printBalanceFactors(curr->left);
    cout << curr->key << "(" << balanceFactor(curr) << "), ";
    printBalanceFactors(curr->right);
}

Node *AVLTree::findUnbalancedNode(Node *node) //recursively moves up the tree looking for unbalanced nodes
{

    Node *curr = node;
    if (curr == nullptr) // no unbalanced nodes
    {
        return nullptr;
    }
    if (balanceFactor(curr) >= 2 || balanceFactor(curr) <= -2) // unbalanced node found
    {
        return curr;
    }

    return findUnbalancedNode(curr->parent); // recursively goes up path until it finds an unbalanced node*/
}