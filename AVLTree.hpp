/* 11/10/17
 * This file is the header file of AVLTree
*/

#ifndef AVLTREE_HPP_
#define AVLTREE_HPP_

#include "NodeT.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
using namespace std;

class AVLTree{
	bool AVLflag;
	friend class Game;
public:
	NodeT *root;
	AVLTree(bool flag);
	bool findWord(string s, NodeT *r);
	void addNode(string s); //had difficulties writing in recursive so changed it to iteration
	void printIO(NodeT *root);
	void printPre(NodeT *root);
	void printPost(NodeT *root);
    NodeT * updateHeightAfterInsertion(NodeT *n); //helper function to update the height of the nodes along the path of the insertion where it happens. It will be used in addNode() and bofore adjustHeights() is used in addNode()
    
	// methods for AVLTrees and can debug for plain BST
	void adjustHeights(NodeT *n);
	int getMax(NodeT *n);
    
	// methods for AVLTrees only
	NodeT * rotateRight(NodeT *n);
	NodeT * rotateLeft(NodeT *n);
	int getDiff(NodeT *n);
    void updateHeightAfterRotation(NodeT *n); //helper function to update the height of the nodes along the path of the returned node from rotation.
};



#endif /* AVLTREE_HPP_ */
