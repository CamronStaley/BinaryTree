//a bintree object holds a root node containing a NodeData, Node left
//and node right used for constructing and minupulating a binary trees
#pragma once
#include "nodedata.h"
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
//Implementation and Assumptions:
//  -- NodeData is a complete ADT 
//  -- Tree is created empty by default
//  -- Any functions involving arrays does not do error checking 

//---------------------------------------------------------------------------

class BinTree { 
    
    //overloaded << operator which prints the tree in order with a space
    //between each data and one endl at the end (calls inorder helper)
    friend ostream& operator<<(ostream&, const BinTree&);

public:
    BinTree(); // constructor
    BinTree(const BinTree&); // copy constructor (calls copyHelper)
    ~BinTree(); // destructor, calls makeEmpty()
    bool isEmpty() const; // true if tree is empty, otherwise false

    // make the tree empty so isEmpty returns true (calls makeEmptyHelper)
    void makeEmpty(); 

    //make the *this = passed in tree with deep copy (calls copyHelper)
    BinTree& operator=(const BinTree&);

    //if both trees are identical return true (calls compareHelper)
    bool operator==(const BinTree&) const;

    //if both trees aren't identical return true (calls compareHelper)
    bool operator!=(const BinTree&) const;
    bool insert(NodeData*); //inserts the NodeData in the correct location

    //iterates through tree to find target and set the pointer reference
    //equal to it. Returns false if not found
    bool retrieve(const NodeData&, NodeData*&) const;
    void displaySideways() const; // displays the tree sideways
    void bstreeToArray(NodeData* []); //empties tree into an array in order

    //finds the target and returns the furthest distance from a leaf node
    //returns 0 if not found and 1 if it is leaf node
    int getHeight(const NodeData&) const; 
    void arrayToBSTree(NodeData* []); //creates balanced tree for ordered array

private:
    struct Node {
        NodeData* data; // pointer to data object
        Node* left; // left subtree pointer
        Node* right; // right subtree pointer
    };
    Node* root; // root of the tree
    int index = 0; //used for bstreeToArray

    // utility functions
    void inorderHelper(const Node*, ostream&) const; // recursive helper for operator<<
    void sideways(Node*, int) const; //helper for print sideways
    void makeEmptyHelper(Node*); //helper for makeEmpty
    Node* copyHelper(Node*, const Node*); //helper for = and copyConstructor
    bool compareHelper(const Node*, const Node*) const; //helper for == and !=
    void bstreeToArrayHelper(Node*, NodeData* []); //helper for bstreeToArray
    int getHeightHelper(const Node*) const; //helper for getHeight
    int findTarget(const Node*, const NodeData&) const; //helper for getHeight
    Node* arrayToBSHelper(Node*, NodeData* [], int, int); //helper for arrayToBSTree
};