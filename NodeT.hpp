/*
 * NodeT.hpp
 *
 *  Created on: Oct 19, 2017
 *      Author: Debra
 */

#ifndef NodeT_HPP_
#define NodeT_HPP_

#include <string>
using namespace std;

class NodeT {
	friend class AVLTree;

public:
	string word;
	int height;
	NodeT *left;
	NodeT *right;
	NodeT *parent;


	NodeT(string x);
	~NodeT();
	void printTNode();
};



#endif /* NodeT_HPP_ */
