/*
   * file: driver-proj4.cpp
   * author: Dylan Bonin
   * course: CSI 3334
   * assignment: project 4
   * due date: October 23, 2022
   * version: 1.3
   *
   * This file is the driver. It creates an AVL or
   * balanced binary search tree that allows
   * users to insert values,
   * decrypt and encrypt messages, and print the tree
   * using preorder traversal. The tree will remain
   * balanced after insertions and deletions
*/

#include <iostream>
#include "avl-tree-student-proj4.h"
#include <sstream>

using namespace std;

/*
   * main
   *
   * This function serves as a driver for the balanced
   * binary tree. It allows users to insert nodes, remove
   * nodes, print the tree in pre-order and level-order
   * traversal and encrypt and decrypt messages. The tree
   * remains balanced throughout this process
   *
   * Parameters:
   *   none
   *
   * Return value: 0 - the exit code for the program
*/

int main() {

    //create variables for myTree and for reading in lines
    EncryptionTree<string> myTree;
    string instructionLine;
    string instructWord;


    //while reading instructions
    while(getline(cin, instructionLine)) {
        //if input is q, stop the program
        if (instructionLine == "q") {
            break;
        }
        //if input is i, insert the value
        else if (instructionLine[0] == 'i') {

            //find the white space
            int i;
            for (i = 0; instructionLine[i] != ' '; i++) {
            }
            i++;

            //insert the ord
            instructWord = instructionLine.substr(i);
            myTree.insert(instructWord);
        }
        //if input is p, print the tree preorder traversal
        else if (instructionLine[0] == 'p') {
            myTree.printPreorder();
        }
        //if input is l, print the tree levelorder traversal
        else if (instructionLine[0] == 'l') {
            myTree.printLevelOrder();
        }
        //input is r, remove the word
        else if (instructionLine[0] == 'r') {
            int i;
            for (i = 0; instructionLine[i] != ' '; i++) {
            }
            i++;

            instructWord = instructionLine.substr(i);
            myTree.remove(instructWord);
        }
        //if input is e, encrypt the word
        else if (instructionLine[0] == 'e') {
            int i;
            for (i = 0; instructionLine[i] != '\''; i++) {
            }
            i++;

            instructWord = instructionLine.substr(i);
            instructWord.pop_back();

            stringstream ss(instructWord);
            string encryptWord;
            int count = 0;

            //read in words for string stream
            while (ss >> encryptWord) {
                if (count == 0) {
                    cout << myTree.encrypt(encryptWord);
                    count++;
                }
                else {
                    cout << " " << myTree.encrypt(encryptWord);
                }
            }
            cout << endl;
        }
        //if input is d, decrypt the word
        else if (instructionLine[0] == 'd') {
            int i;
            for (i = 0; instructionLine[i] != '\''; i++) {
            }
            i++;

            instructWord = instructionLine.substr(i);
            instructWord.pop_back();

            stringstream ss(instructWord);
            string decryptWord;
            int count = 0;

            //read input from string stream
            while (ss >> decryptWord) {
                if (count == 0) {
                    //if nullptr was returned, output "?"
                    if (myTree.decrypt(decryptWord) == nullptr) {
                        cout << "?";
                        count++;
                    }
                    else {
                        cout << *myTree.decrypt(decryptWord);
                        count++;
                    }
                }
                else {
                    if (myTree.decrypt(decryptWord) == nullptr) {
                        cout << " " << "?";
                    }
                    else {
                        cout << " " << *myTree.decrypt(decryptWord);
                    }
                }
            }
            cout << endl;
        }
    }



    return 0;
}
