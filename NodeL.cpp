/*
 * NodeL.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: Debra
 */

#include "NodeL.hpp"
#include <string>
#include <iostream>

using namespace std;

NodeL::NodeL(string s) {
	word = s;
	next = NULL;
	wscore = 0;
}
NodeL::~NodeL() {
	cout << "Deleting " << word << endl;
}

