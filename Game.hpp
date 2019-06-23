/*
 * Game.hpp
 *
 *  Created on: Mar 19, 2015
 *      Author: Debra
 *
 *  Modified by: Hang Chen
 *  11/19/17
 */

#ifndef GAME_HPP_
#define GAME_HPP_

#include "AVLTree.hpp"
#include "LL.hpp"
#include <iostream>
#include <string>

class Game {
	bool AVL;
	AVLTree *dict;
	int numletters;
	char *currletters;
	//int numright;
	//int totalwords;
	int score;
	LL wordlist;
	string dictfile;
public:
	Game();
	Game(string infile, bool AVLflag);
	void startGame();
	void getWords(char currletters[], int timer);
	void readTreeFromFile ();
	char *getLetters(int x);
	void getWords();
	bool checkWLetters(string s);
	void checkWordsForScore();
    // Two added functions for Extra Credit 2
    int find(char arr[], int len, char seek);
    int getWordsScore(string word) ;
};

#endif /* GAME_HPP_ */
