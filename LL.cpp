/* 11/10/17
 * This file is the definition file of LL 
*/


#include "LL.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstring>
using namespace std;

// Constructor
LL::LL(){
    first = NULL;
    last = NULL;
    size = 0;
    score = 0;
}

// Destructor
// Referene: https://stackoverflow.com/questions/2265967/writing-a-linkedlist-destructor
LL::~LL(){
    NodeL* tmp = first;
    while(tmp != NULL) {
        NodeL* next = tmp->next;
        delete tmp;
        tmp = next;
    }
    size = 0;
    score = 0;
}

void LL::printList(){
    NodeL* tmp = first;
    while(tmp != NULL) {
        NodeL* next = tmp->next;
        cout <<tmp->word<<":"<<tmp->wscore;
        cout <<", ";
        tmp = next;
    }
    cout <<endl;
}

void LL::addFirst(string x){
    first = new NodeL(x); //By default, prev and next are both NULL, and it fits in the circumstance of the first node
    last = first;
    size++;
}

void LL::push(string x){
    if (first == NULL) {
        addFirst(x);
    } else {
        NodeL *newTail = new NodeL(x);
        last->next = newTail;
        last = newTail;
        size++;
    }
}

int LL::getScore(){
    score = 0;
    NodeL* tmp = first;
    while(tmp != NULL) {
        score += tmp->wscore;
        tmp = tmp->next;
    }
    return score;
}
