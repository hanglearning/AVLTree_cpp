/* 11/10/17
 * This file is the header file of LL
*/

#ifndef LL_HPP_
#define LL_HPP_

#include "NodeL.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <cstring>
using namespace std;

class LL {
    friend class Game;
    NodeL *first;
    NodeL *last;
    int size;
    int score;
    
public:
    LL();
    ~LL();
    void printList();
    void addFirst(string x);
    void push(string x);
    int getScore();
};


#endif /* LL_HPP_ */
