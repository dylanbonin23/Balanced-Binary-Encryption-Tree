/*
   * file: avl-tree-student-proj4.h
   * author: Dylan Bonin
   * course: CSI 3334
   * assignment: project 4
   * due date: October 23, 2022
   * version: 1.3
   *
   * This file is the the implementation of the
   * member functions from the AVLNode, AVLTree, and
   * EncryptionTree
   * classes.
*/

#ifndef AVL_TREE_STUDENT_PROJ4
#define AVL_TREE_STUDENT_PROJ4

#include "avl-tree-prof-proj4.h"
#include <queue>

/*
   * destructor
   *
   * This function is the destructor for the BSTNode
   * object.
   *
   * Parameters:
   *   none
   *
   * Return value: none
*/

template <class Base>
AVLNode<Base>::~AVLNode () {
    delete left;
    delete right;
}

/*
   * singleRotateLeft
   *
   * This function performs a single left rotation
   * at the node object.
   *
   * Parameters:
   *   none
   *
   * Return value: rightChild - the new root node
   * after the rotation
*/

template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateLeft() {
    //set pointers to all the nodes needed for the rotation
    AVLNode<Base>* rightChild = this->right;
    AVLNode<Base>* rightRightC = nullptr;
    AVLNode<Base>* T2 = nullptr;

    //find the right child of right child and
    //that right child's left child
    if (rightChild != nullptr) {
        rightRightC = rightChild->right;
        T2 = rightChild->left;
    }

    //send new right child of our node
    this->right = T2;
    //set this as left child of the current right child
    rightChild->left = this;

    //update our heights
    this->updateHeight();
    rightChild->updateHeight();

    //return the new parent
    return rightChild;
}

/*
   * singleRotateLeft
   *
   * This function performs a single right rotation
   * at the node object.
   *
   * Parameters:
   *   none
   *
   * Return value: leftChild - the new root node of the
   * subtree after the rotation
*/

template <class Base>
AVLNode<Base>* AVLNode<Base>::singleRotateRight() {
    //set pointers to all the nodes needed for the rotation
    AVLNode<Base>* leftChild = this->left;
    AVLNode<Base>* leftLeftC = nullptr;
    AVLNode<Base>* T3 = nullptr;


    //find the left child of left child and
    //that left child's right child
    if (leftChild != nullptr) {
        leftLeftC = leftChild->left;
        T3 = leftChild->right;
    }


    //set new left child of our node
    this->left = T3;
    //set this as the right child of current left child
    leftChild->right = this;
    //update the heights
    this->updateHeight();
    leftChild->updateHeight();

    return leftChild;
}

/*
   * doubleRotateLeftRight
   *
   * This function performs a double left right
   * rotation at the given node
   *
   * Parameters:
   *   none
   *
   * Return value: newPar - the new root node
   * of the subtree after the rotation
*/

template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateLeftRight() {
    //find right child of left child of root will be the new root
    AVLNode<Base>* newPar = this->left->right;

    //rotation left child left and then rotate this right
    this->left = this->left->singleRotateLeft();
    this->singleRotateRight();

    return newPar;
}

/*
   * doubleRotateRightLeft
   *
   * This function performs a double right left
   * rotation at the given node
   *
   * Parameters:
   *   none
   *
   * Return value: newPar - the new root node
   * of the subtree after the rotation
*/

template <class Base>
AVLNode<Base>* AVLNode<Base>::doubleRotateRightLeft() {
    //the left child of the right child of root will be new root
    AVLNode<Base>* newPar = this->right->left;

    //rotate right at right child, then rotate left at root
    this->right = this->right->singleRotateRight();
    this->singleRotateLeft();

    return newPar;
}

/*
   * printLevelOrder
   *
   * This function outputs the AVL tree in level order
   * (prints the nodes of each level in order)
   *
   * Parameters:
   *   os - the output stream being used
   *
   * Return value: newPar - none
*/

template <class Base>
void AVLTree<Base>::printLevelOrder(ostream& os) const {
    //create a queue for printing our nodes
    queue<AVLNode<Base>*> myQueue;
    //lineCount to determine how many nodes we want printed on
    //one line
    int lineCount = 0;
    //first count to account for the first item outputted
    int firstCount = 0;

    //push root if not null
    if (this->root != nullptr) {
        myQueue.push(this->root);
    }
    else {
        os << "NULL" << endl;
        return;
    }

   //create a node to traverse the tree
   AVLNode<Base>* currNode = this->root;

    //while our queue isn't empty
    while (myQueue.size() > 0) {
        //get the front and pop it
        currNode = myQueue.front();
        myQueue.pop();


        if (currNode == nullptr) {
            //we want 20 nodes at most printed one one line and starting at index 0
            //so while under 19 print the node
            if (lineCount < 19) {
                if (firstCount == 0) {
                    lineCount++;
                    os << "NULL";
                    firstCount++;
                }

                else if (lineCount == 0) {
                    lineCount++;
                    os << "NULL";
                }

                else {
                    lineCount++;
                    os << " NULL";
                }

            }
            //at the 20th node, print NULL then have a new line
            else if (lineCount == 19) {
                os << " NULL" << endl;
                lineCount = 0;
            }
        }

        //if our current node isn't null, push it's children
        // onto the queue
        else {
            myQueue.push(currNode->left);
            myQueue.push(currNode->right);
            //we want 20 nodes at most printed one one line
            //and starting at index 0
            //so while under 19 print the node
            if (lineCount < 19) {
                if (firstCount == 0) {
                    lineCount++;
                    os << currNode->getData();
                    firstCount++;
                }
                //if the first one printed
                else if (lineCount == 0) {
                    lineCount++;
                    os << currNode->getData();
                }
                //if not the first one printed
                else {
                    lineCount++;
                    os << " " << currNode->getData();
                }

            }
            //after twenty items, create a new line
            else if (lineCount == 19) {
                os << " " << currNode->getData() << endl;
                lineCount = 0;
            }
        }

    }

    os << endl;

}

/*
   * printPreorder
   *
   * This function prints the binory search tree
   * in preorder traversal.
   *
   * Parameters:
   *   os - the output stream being used
   *   indent - the indentation being used for the tree
   *
   * Return value: none
*/

template <class Base>
void AVLNode<Base>::printPreorder (ostream &os, string indent) const {
    string space = "  ";

    //print first
    os << indent <<  this->data << endl;

    //print left
    if (this->left != nullptr) {
        this->left->printPreorder(os, indent + space);
    }
    else {
        os << "  " << indent << "NULL" << endl;
    }

    //print right
    if (this->right != nullptr) {
        this->right->printPreorder(os, indent + space);
    }
    else {
        os << "  " << indent << "NULL" << endl;
    }
}

/*
   * minNode
   *
   * This function finds the node with the
   * minimum value in the BST
   *
   * Parameters:
   *   none
   *
   * Return value: currNode - a pointer to the min Node
*/

template <class Base>
const AVLNode<Base>* AVLNode<Base>::minNode() const {
    AVLNode<Base>* currNode = this->left;

    if (this->left == nullptr) {
        return this;
    }
    else {
        while (currNode->left != nullptr) {
            currNode = currNode->left;
        }
    }

    return currNode;
}

/*
   * maxNode
   *
   * This function finds the node with the
   * maximum value in the BST
   *
   * Parameters:
   *   none
   *
   * Return value: currNode - a pointer to the max Node
*/

template <class Base>
const AVLNode<Base>* AVLNode<Base>::maxNode() const {
    AVLNode<Base>* currNode = this->right;

    if (this->right == nullptr) {
        return this;
    }
    else {
        while (currNode->right != nullptr) {
            currNode = currNode->right;
        }
    }

    return currNode;
}

/*
   * remove
   *
   * This function removes a node from the
   * binary search tree
   *
   * Parameters:
   *   item - the data value of the node being removed
   *
   * Return value: none
*/

template <class Base>
void AVLTree<Base>::remove(const Base &item) {
    AVLNode<Base>* parent = nullptr;
    AVLNode<Base>* currentNode = this->root;
    AVLNode<Base>** nodeTree = new AVLNode<Base>*[32]; //array of lenght 32
    //will cover a BST tree of over
    //50 billion nodes, which is much more than we will need.
    //this will keep track of the path of nodes used


    //numNodes to track how many nodes are on the path
    int numNodes = 0;


    //while we are still searching the BST
    while (currentNode != nullptr) {
        //if we have found the node
        if (!(currentNode->getData() < item) && !(item < currentNode->getData())) {
            //node being removed is leaf
            if (currentNode->left == nullptr && currentNode->right == nullptr) {
                //if it is the root node
                if (parent == nullptr) {
                    this->root = nullptr;
                }
                //if it is left child of parent node
                else if (parent->left == currentNode) {
                    parent->left = nullptr;
                }
                //if it is right child of parent node
                else {
                    parent->right = nullptr;
                }
                delete currentNode;
                currentNode = nullptr;
            }
            //node being removed has one child (left child)
            else if (currentNode->left && currentNode->right == nullptr) {
                //if it is root
                if (parent == nullptr) {
                    this->root = currentNode->left;
                }
                //if it is left child of parent
                else if (parent->left == currentNode) {
                    parent->left = currentNode->left;
                }
                //if it is right child of parent
                else {
                    parent->right = currentNode->left;
                }
                currentNode->left = nullptr;
                delete currentNode;
                currentNode = nullptr;
            }
            //node being removed has one child (right child)
            else if (currentNode->left == nullptr && currentNode->right) {
                //if it root node
                if (parent == nullptr) {
                    this->root = currentNode->right;
                }
                //if left child of parent
                else if (parent->left == currentNode) {
                    parent->left = currentNode->right;
                }
                //if right child of parent
                else {
                    parent->right = currentNode->right;
                }
                currentNode->right = nullptr;
                delete currentNode;
                currentNode = nullptr;
            }
            //node being removed has two children
            else {
                AVLNode<Base>* succesor = currentNode->right; //succesor node we will find
                AVLNode<Base>* succesorPar = currentNode; //parent to succesor node
                //look for leftmost node of right subtree
                while (succesor->left != nullptr) {
                    succesorPar = succesor;
                    succesor = succesor->left;
                }
                if (parent == nullptr) {
                    this->root = succesor;
                }
                //if node being removed is left child of its parent
                else if (parent->left == currentNode) {
                    parent->left = succesor;
                }
                //if node being removed is right child of its parent
                else if (parent->right == currentNode) {
                    parent->right = succesor;
                }
                //set succesor node's left to node being removed left
                succesor->left = currentNode->left;

                //if succesor is a leftmost node and has no children
                if (succesorPar->left == succesor && succesor->right == nullptr) {
                    succesorPar->left = nullptr;
                }
                //if succesor is a leftmost node and does have children
                else if (succesorPar->left == succesor && succesor->right != nullptr) {
                    succesorPar->left = succesor->right;
                }
                //if node we are removing right is not succesor and has no children
                if (currentNode->right != succesor && succesor->right == nullptr) {
                    succesor->right = currentNode->right;
                }
                //if succesor is right node and has children
                else if (currentNode->right == succesor && succesor->right != nullptr) {
                    succesor->right = succesor->right;
                }
                //if succesor is not right node and children
                else if (currentNode->right != succesor && succesor->right != nullptr) {
                    //succesor->right = succesor->right;
                    succesorPar->left = succesor->right;
                    succesor->right = currentNode->right;
                }
                //if succesor is right node and has no children
                else {
                    succesor->right = nullptr;
                }

                nodeTree[numNodes] = succesor;
                numNodes++;

                //find the path to the where we found our succesor node
                if (succesor->right != nullptr) {
                    //new node to traverse the tree
                    AVLNode<Base>* succNodePath = succesor->right;
                    nodeTree[numNodes] = succesor->right;
                    numNodes++;

                    //while the left child of our succesor node's right child
                    //is not null, add the left child to our path
                    while (succNodePath->left != nullptr) {
                        succNodePath = succNodePath->left;
                        nodeTree[numNodes] = succNodePath;
                        numNodes++;
                    }
                }

                //delete curr node
                currentNode->left = nullptr;
                currentNode->right = nullptr;
                delete currentNode;
                currentNode = nullptr;
            }
        //if not found, keep searching the tree
        //and add to our path
        }
        else if (currentNode->data < item) {
            nodeTree[numNodes] = currentNode;
            numNodes++;

            parent = currentNode;
            currentNode = currentNode->right;
        }
        else {
            nodeTree[numNodes] = currentNode;
            numNodes++;

            parent = currentNode;
            currentNode = currentNode->left;
        }
    }

    //rebalance the tree after deleting it
    rebalancePathToRoot(nodeTree, numNodes);
    delete [] nodeTree;

    if (currentNode == nullptr) {
        return;
    }
}

/*
   * rebalancePathToRoot
   *
   * This function takes an array of nodes and that
   * represents a path in the AVLTree and rebalances
   * each node, working it's way back to the root
   *
   * Parameters:
   *   path - the array of nodes
   *   numOnPath - the number of items in the array
   *
   * Return value: none
*/

template <class Base>
void AVLTree<Base>::rebalancePathToRoot(AVLNode<Base> **path, int numOnPath) {
    //starting at the end of the array and working back to root
    for (int i = numOnPath - 1; i >= 0; i--) {
        //update the height of the node
        path[i]->updateHeight();

        //calculate the balance factor of the node
        int balance = 0;
        int leftHeight = -1;
        int rightHeight = -1;

        //left subtree height
        if (path[i]->left != nullptr) {
            leftHeight = path[i]->getHeight(path[i]->left);
        }
        //right subtree height
        if (path[i]->right != nullptr) {
            rightHeight = path[i]->getHeight(path[i]->right);
        }

        //calculate balance factor
        balance = leftHeight - rightHeight;

        //too big to the right
        if (balance == -2) {
            //find balance of right child
            int RleftHeight = -1;
            int RrightHeight = -1;
            int RBalance = 0;

            //right child left subtree height
            if (path[i]->right->left != nullptr) {
                RleftHeight = path[i]->getHeight(path[i]->right->left);
            }
            //right child right subtree height
            if (path[i]->right->right != nullptr) {
                RrightHeight = path[i]->getHeight(path[i]->right->right);
            }

            //right child balance factor
            RBalance = RleftHeight - RrightHeight;
            //rotate right left
            if (RBalance == 1) {
                //updating the parents

                //if root
                if (i == 0) {
                    this->root = this->root->doubleRotateRightLeft();
                }
                //if left child of previous node
                else if (path[i - 1]->left == path[i]) {
                    path[i-1]->left = path[i-1]->left->doubleRotateRightLeft();
                }
                //if right child of previous node
                else if (path[i - 1]->right == path[i]) {
                    path[i-1]->right = path[i-1]->right->doubleRotateRightLeft();
                }
            }
            //just rotate left
            else {
                //update parents
                //if root
                if (i == 0) {
                    this->root = this->root->singleRotateLeft();
                }
                //if left child of previous node
                else if (path[i - 1]->left == path[i]) {
                    path[i-1]->left = path[i-1]->left->singleRotateLeft();
                }
                //if right child of previous node
                else if (path[i - 1]->right == path[i]) {
                    path[i-1]->right = path[i-1]->right->singleRotateLeft();
                }
            }
        }
        //too big to the left
        else if (balance == 2) {
            //calculate left child balance factor
            int LleftHeight = -1;
            int LrightHeight = -1;
            int LBalance = 0;

            //find left child left subtree height
            if (path[i]->left->left != nullptr) {
                LleftHeight = path[i]->getHeight(path[i]->left->left);
            }
            //left child right subtree height
            if (path[i]->left->right != nullptr) {
                LrightHeight = path[i]->getHeight(path[i]->left->right);
            }

            //left child balance factor
            LBalance = LleftHeight - LrightHeight;
            //rotate left right
            if (LBalance == -1) {
                //updating the parents
                //if root
                if (i == 0) {
                    this->root = this->root->doubleRotateLeftRight();
                }
                //if left child of previous node
                else if (path[i - 1]->left == path[i]) {
                    path[i-1]->left = path[i-1]->left->doubleRotateLeftRight();
                }
                //if right child of previous node
                else if (path[i - 1]->right == path[i]) {
                    path[i-1]->right = path[i-1]->right->doubleRotateLeftRight();
                }
            }
            //just rotate right
            else {
                //update parents
                //if root
                if (i == 0) {
                    this->root = this->root->singleRotateRight();
                }
                //if left child of previous node
                else if (path[i - 1]->left == path[i]) {
                    path[i-1]->left = path[i-1]->left->singleRotateRight();
                }
                //if right child of previous node
                else if (path[i - 1]->right == path[i]) {
                    path[i-1]->right = path[i-1]->right->singleRotateRight();
                }
            }

        }
    }
}

/*
   * insert
   *
   * This function inserts a node into the
   * binary search tree
   *
   * Parameters:
   *   item - the data value of the item being added
   *
   * Return value: none
*/

template <class Base>
void AVLTree<Base>::insert(const Base &item) {
    AVLNode<Base>* newNode = new AVLNode<Base>(item);
    //AVLNode<Base>** nodeTree = new AVLNode<Base>*[root->getHeight(root) + 1];
    AVLNode<Base>** nodeTree = new AVLNode<Base>*[32];
    //array of lenght 32 will
    //cover a BST tree of over 50 billion nodes, which is more than we will need
    //array to track path taken through tree to rebalance it

    //num nodes on the path
    int numNodes = 0;

    //if tree is empty
    if (root == nullptr) {
        root = newNode;
    }
    //otherwise
    else {
        //set a node to the root
        AVLNode<Base> *currentNode = root;
        while (currentNode) {
            //if data is equal to current node, don't insert again
            if (!(newNode->getData() < currentNode->data)
                && !(currentNode->data < newNode->getData())) {
                delete newNode;
                newNode = nullptr;
                break;
            }
            //if data is less than our currentNode data
            else if (newNode->data < currentNode->data) {
                //add node to the path
                nodeTree[numNodes] = currentNode;
                numNodes++;
                //if left child is null
                if (currentNode->left == nullptr) {
                    currentNode->left = newNode;
                    //newNode->updateHeight();
                    currentNode = nullptr;
                }
                //otherwise keep looking for left child
                else {
                    currentNode = currentNode->left;
                }
            }
            //if item data is greater than curretNode data
            else {
                //add node to the path
                nodeTree[numNodes] = currentNode;
                numNodes++;
                //if right child is null
                if (currentNode->right == nullptr) {
                    currentNode->right = newNode;
                    //newNode->updateHeight();
                    currentNode = nullptr;
                }
                //keep looking right child
                else {
                    currentNode = currentNode->right;
                }
            }
        }
    }

    rebalancePathToRoot(nodeTree, numNodes);

    delete [] nodeTree;
}

/*
   * decrypt
   *
   * This function decrypts an encoded path
   * for our BST.
   *
   * Parameters:
   *   path - the encrypted path
   *
   * Return value: myPointer - a pointer to the decrypted node
*/

template <class Base>
const Base* EncryptionTree<Base>::decrypt(const string &path) const {
    const Base* myPointer = nullptr;
    const AVLNode<Base>* currentNode = this->root;
    string notFound = "?";

    if (currentNode == nullptr) {
        return nullptr;
    }

    //if it is r it's the root node
    if (path == "r") {
        myPointer = &currentNode->getData();
        return myPointer;
    }

    //for every other node, search the tree
    for (int i = 1; i < path.length(); i++) {
        //go right for 1
        if (path[i] == '1') {
            currentNode = currentNode->getRight();
        }
        //go left for 0
        else {
            currentNode = currentNode->getLeft();
        }
        //if null, break
        if (currentNode == nullptr) {
            break;
        }
    }

    //return null if nothing found
    if (currentNode == nullptr) {
        return nullptr;
    }

    myPointer = &currentNode->getData();



    return myPointer;
}

/*
   * encrypt
   *
   * This function enrypts a path to an item
   * in our binary subtree
   *
   * Parameters:
   *   item - the data value of the item being encrypted
   *
   * Return value: myString - the encrypted path to the node
*/

template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const {
    string myString = "r";
    const AVLNode<Base>* currentNode = this->root;

    //if it is null, return "?"
    if (currentNode == nullptr) {
        myString = "?";
        return myString;
    }

    //return r if it is the root
    //if (currentNode->getData() == item) {
    if (!(currentNode->getData() < item) && !(item < currentNode->getData())) {
        return myString;
    }


    //otherwise search the tree
    else {
        //while it is not null and not found
        while ((currentNode != nullptr) &&
               !(!(currentNode->getData() < item) && !(item < currentNode->getData())) ) {
            //if value is less than, go left
            if (item < currentNode->getData()) {
                myString = myString + '0';
                currentNode = currentNode->getLeft();
            }
            //else go right
            else {
                myString = myString + '1';
                currentNode = currentNode->getRight();
            }
        }
    }

    //if it is null, return "?"
    if (currentNode == nullptr) {
        myString = "?";
        return myString;
    }


    //otherwise return the path
    if (currentNode != nullptr &&
        (!(currentNode->getData() < item) && !(item < currentNode->getData()))) {
        return myString;
    }




    //delete newNode;
    return myString;
}



#endif
