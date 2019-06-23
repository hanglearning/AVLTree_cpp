/*
 * NodeT.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: Debra
 */

#include "NodeT.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

NodeT::NodeT(string x) {
	word = x;
	left = NULL;
	right = NULL;
	parent = NULL;
	height = 0;
}

NodeT::~NodeT() {
	if ((left != NULL) || (right != NULL)) {
		cout << "deleting may leave dangling Tree Nodes" << endl;
	}
}

void NodeT::printTNode() {
	cout << "|"<<height<<":"<<word << "| " << endl;
}


