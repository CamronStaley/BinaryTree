#include "bintree.h"
#include "nodedata.h"


//---------------------------------------------------------------------------
//Default constructor
//creates empty tree
BinTree::BinTree() {
    root = nullptr;
}

//---------------------------------------------------------------------------
//Copy Constructor
//calls copy helper to deep copy
BinTree::BinTree(const BinTree& toCopy) {
    if (toCopy.root != nullptr) {        
        root = copyHelper(root, toCopy.root);
    }
}

//operator=
//overloaded = operator which calls copyHelper to deep copy 
BinTree& BinTree::operator=(const BinTree& toCopy) {
    if (&toCopy != this) {
        makeEmpty();
        root = copyHelper(root, toCopy.root);
    }

    return *this;
}

//used to recursively deep copy the tree
BinTree::Node* BinTree::copyHelper(Node* curr, const Node* toCopyCurr) {
    if (toCopyCurr != nullptr) {
        Node* ptr = new Node;    
        ptr->data = new NodeData(*toCopyCurr->data);
        ptr->left = ptr->right = nullptr;
        curr = ptr;
        curr->left = copyHelper(curr->left, toCopyCurr->left);
        curr->right = copyHelper(curr->right, toCopyCurr->right);
    }
    return curr;
}

//---------------------------------------------------------------------------
//getHeight
//finds the furthest distance from the target object to a leaf node. 
//Returns 0 if not found and uses getHeightHelper to do recurssion 
int BinTree::getHeight(const NodeData& target) const {
    return findTarget(root, target);
}

//findTarget
//used to find the target returns 0 if not found and calls getHeightHelper
//if it is found
int BinTree::findTarget(const Node* curr, const NodeData& target) const {
    int num = 0;
    if (curr == nullptr) { //not found
        return 0;
    }
    else if (*curr->data == target) { //it is found
        //checking if it is leaf
        if (curr->left == nullptr && curr->right == nullptr) {
            return num + 1;
        }
        else { //not leaf so finds height
            return getHeightHelper(curr);
        }
        
    }
    else { //keep searching
        num += findTarget(curr->left, target);
        num += findTarget(curr->right, target);
    }
    return num;
}

//getHeightHelper
//recursively finds the height to the largest depth
int BinTree::getHeightHelper(const Node* curr) const{
    if (curr == nullptr) { //end condition
        return 0;
    }
    else {
        int lHeight = getHeightHelper(curr->left);
        int rHeight = getHeightHelper(curr->right);

        if (lHeight > rHeight) { //getting largest height
            return(lHeight + 1);
        }
        else {
            return(rHeight + 1);
        }
    }
}

//---------------------------------------------------------------------------
//arrayToBSTree
//Builds a tree from an array and leaves the array empty
//does no error checking and uses arrayToBSHelper for reccursion
void BinTree::arrayToBSTree(NodeData* arr[]) {
    makeEmpty();
    int high = 0;
    while (arr[high] != nullptr) { //getting the size of arr
        high++;
    }
    high--;
    root = arrayToBSHelper(root, arr, 0, high);
}

//arrayToBSHelper
//creates a Binary search tree out of the given array using recurrsion
BinTree::Node* BinTree::arrayToBSHelper(Node* curr, 
    NodeData* arr[], int low, int high) {
    if (low > high) { //end condition
        return nullptr;
    }
    int mid = ((low + high) / 2); //getting current root
    curr = new Node;
    curr->left = curr->right = nullptr;
    curr->data = arr[mid];
    curr->left = arrayToBSHelper(curr->left, arr, low, mid - 1);
    curr->right = arrayToBSHelper(curr->right, arr, mid + 1, high);
    arr[mid] = nullptr; //emptying array
    return curr;
}
//---------------------------------------------------------------------------
//Destructor
//calls makeEmpty to delete tree
BinTree::~BinTree() {
    makeEmpty();
}


//makeEmpty
//deletes all memory and clears tree by calling makeEmptyHelper
void BinTree::makeEmpty() {
    if (root != nullptr) {
        makeEmptyHelper(root);
        root = nullptr;
    }
}

//makeEmptyHelper
//called by makeEmpty to recursively delete tree
void BinTree::makeEmptyHelper(Node* curr) {
    if (curr != nullptr) {
        makeEmptyHelper(curr->left);
        makeEmptyHelper(curr->right);
        delete curr->data;
        curr->data = nullptr;
        delete curr;
        curr = nullptr;
    }
}

//---------------------------------------------------------------------------
//isEmpty
//returns true if tree is empty
bool BinTree::isEmpty() const {
    if (root == nullptr) {
        return true;
    }
    return false;
}


//---------------------------------------------------------------------------
//<<operator
//displays the tree with an inorder traversal using the inorder helper func
//displays each data with a space after it and an endl at the end
ostream& operator<<(ostream& output, const BinTree& tree) {
    tree.inorderHelper(tree.root, output);
    output << endl;
    return output;
}

//inorder helper function moves through tree to display variables
//in order and return them
void BinTree::inorderHelper(const Node* curr, ostream& output) const {
    if (curr != nullptr) {
        inorderHelper(curr->left, output);
        output << *curr->data << " ";
        inorderHelper(curr->right, output);
    }
}
//---------------------------------------------------------------------------
//operator==
//overloaded == operator which returns true if all nodes are the same and
//within the same locations calls compareHelper for recursion 
bool BinTree::operator==(const BinTree& other) const {
    return compareHelper(root, other.root);
}

//operator!=
//calls operator== to check if the trees are not equal
bool BinTree::operator!=(const BinTree& other) const {
    return !(*this == other);
}

//compareHelper
//used by operator== and operator!= to recursively compare two trees
bool BinTree::compareHelper(const Node* curr, 
    const Node* otherCurr) const {

    if (curr == nullptr && otherCurr != nullptr) { //one is null
        return false;
    }
    else if (curr != nullptr && otherCurr == nullptr) { //other is null
        return false;
    }
    else if (curr == nullptr && otherCurr == nullptr) { //both are null
        return true;
    }
    else if (*curr->data != *otherCurr->data) { //not same data
        return false;
    }
    else { //move onto right and left
        return (compareHelper(curr->left, otherCurr->left) &&
            compareHelper(curr->right, otherCurr->right));
    }
    
}
//---------------------------------------------------------------------------
//retrieve
//used to find the data and if it is not found then returns false
bool BinTree::retrieve(const NodeData& target, NodeData*& point) const {
    if (root == nullptr) {
        return false;
    }
    Node* curr = root;
    while (curr != nullptr) {
        if (*curr->data == target) {
            point = curr->data;
            return true;
        }
        else if (target < *curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return false;
}
//---------------------------------------------------------------------------
//bstreeToArray
//Fills the array with the data in the tree (leaving the tree empty)
//no error checking and calls bstreeToArrayHelper for recurrsion
void BinTree::bstreeToArray(NodeData* arr[]) {
    index = 0;
    bstreeToArrayHelper(root, arr);
    root = nullptr;
}

//bstreeToArrayHelper
//Used to recursively fill the array with the data in the tree
void BinTree::bstreeToArrayHelper(Node* curr, NodeData* arr[]) {
    if (curr != nullptr) {
        bstreeToArrayHelper(curr->left, arr);
        arr[index++] = curr->data;
        bstreeToArrayHelper(curr->right, arr);
        curr->data = nullptr;
        delete curr;
        curr = nullptr;
    }
}

//---------------------------------------------------------------------------
//insert
//Inserts in order within tree assuming that operator< exists in NodeData

bool BinTree::insert(NodeData* dataptr) {
    Node* ptr = new Node;     
    ptr->data = dataptr;
    dataptr = nullptr;
    ptr->left = ptr->right = nullptr;
    if (isEmpty()) {
        root = ptr;
    }
    else {
        Node* current = root;
        bool inserted = false;

        // if item is less than current item, insert in left subtree,
        // otherwise insert in right subtree
        while (!inserted) {
            if (*current->data == *ptr->data) {
                delete ptr;
                ptr = nullptr;
                return false;
            }
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) {      // at leaf, insert left
                    current->left = ptr;
                    inserted = true;
                }
                else
                    current = current->left;        // one step left
            }
            else {
                if (current->right == nullptr) {   // at leaf, insert right
                    current->right = ptr;
                    inserted = true;
                }
                else
                    current = current->right;    // one step right
            }
        }
    }
    return true;
}
//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const {
    sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
    if (current != nullptr) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level 
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;    // display information of object
        sideways(current->left, level);
    }
}
//---------------------------------------------------------------------------