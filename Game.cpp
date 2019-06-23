/*
 * Game.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: Debra
 *
 *  Modified by: Hang Chen
 *  11/19/17
 */

#include <iostream>
#include "AVLTree.hpp"
#include "Game.hpp"
#include "LL.hpp"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
// fot timer
#include <time.h>
using namespace std;

Game::Game(){
	Game("dict.txt", false);
}

Game::Game(string filen, bool AVLflag){
	AVL = AVLflag;
	dictfile = filen;
	readTreeFromFile();
    cout <<endl;
	cout << "Printing in order: " << endl;
	dict->printIO(dict->root);
	cout << endl<<"Printing Preorder: " << endl;
	dict->printPre(dict->root);
	cout << endl<<"Printing Postorder: " << endl;
	dict->printPost(dict->root);
	numletters = 0;
	//numright = 0;
	//totalwords = 0;
    wordlist = *new LL();
}

void Game::startGame() {
    // Added timer for extra credit 1
    /* References: https://stackoverflow.com/questions/21181162/how-do-i-stop-a-while-loop-after-a-certain-time-in-c
       https://stackoverflow.com/questions/45941512/exit-a-c-loop-after-defined-amount-of-time */
    cout << "Please set a timer to limit your input time slot."<<endl;
    bool valid = false;
    string timerS;
    int timer = 0;
    // Positive integer user input validation. Not perfect since it can still accept positiveInt+chars but it's the best I can get.
    while (!valid){
        cout << "Enter in seconds (POSITIVE INT only, extra charaters following the number will be trimmed)...: ";
        cin >> timerS;
        try {
            timer = stoi(timerS);
            if (timer > 0){
                valid = true;
            }
        } catch(...) {
            cout << "Invalid input."<<endl;
        }
    }
	cout <<endl<<"How many letters do you want?" << endl;
	cin >> numletters;
	currletters = getLetters(numletters);
	cout << endl;
    // New rule added for extra credit 2
    cout << "Here is the rule:" <<endl;
    cout << "Based on the info form https://www.bestwordlist.com, the amount of words containing letter:" <<endl;
    cout << "A: 147346" <<endl;
    cout << "B: 41392" <<endl;
    cout << "C: 84663" <<endl;
    cout << "D: 72351" <<endl;
    cout << "E: 186136" <<endl;
    cout << "F: 25794" <<endl;
    cout << "G: 60862" <<endl;
    cout << "H: 55649" <<endl;
    cout << "I: 160467" <<endl;
    cout << "J: 3951" <<endl;
    cout << "K: 20866" <<endl;
    cout << "L: 105628" <<endl;
    cout << "M: 63211" <<endl;
    cout << "N: 130259" <<endl;
    cout << "O: 124414" <<endl;
    cout << "P: 64719" <<endl;
    cout << "Q: 4069" <<endl;
    cout << "R: 140215" <<endl;
    cout << "S: 164777" <<endl;
    cout << "T: 127836" <<endl;
    cout << "U: 72751" <<endl;
    cout << "V: 21738" <<endl;
    cout << "W: 17621" <<endl;
    cout << "X: 6832" <<endl;
    cout << "Y: 38027" <<endl;
    cout << "Z: 10977" <<endl<<endl;
    cout << "If we sort by SMALLEST amount to LARGEST, the corresponding letters would be:" <<endl;
    cout << "J, Q, X, Z, W, K, V, F, Y, B, H, G, M, P, D, U, C, L, O, T, N, R, A, I, S, E" <<endl;
    cout <<endl<< "Thus, letter J will worth 26 points, Q will worth 25 pts ... S will worth 2 pts and E will worth 1 point." <<endl<<endl;
    cout << "If the word you are generating is okay letterwise and in the tree, for example, fly, you will get 19+9+18 = 46pts; however, if your chosen word is either not letterwise nor in the tree or both, say, fdsi, you will lose: 19+12+2+3 = 36pts." <<endl;
    cout << "Press input 'y' then hit enter to continue:(y) " <<endl;
    string y = "n";
    cin >> y;
    while (y != "y") {
        cout << "Please review the rule and hit 'y' then enter to continue:(y) " <<endl;
        cin >> y;
    }
    cout <<endl;
    //Continue to get words from the user
	getWords(currletters, timer);
	wordlist.printList();
	checkWordsForScore();
	wordlist.printList();
	wordlist.getScore();
	cout << "Final Score is: " << wordlist.score << endl;
}

// getWords() with timer functioning
void Game::getWords(char currletters[], int timer) {
    //Rule explaination
    cout <<"You have "<<timer<<" seconds to enter your words."<<endl;
    cout <<"You can enter '-1' at any time to end the process before the time ends"<<endl;
    cout <<"NOTE: Please count it in your mind."<<endl<<"This is not a multithreading program so the process won't end automatically."<<endl<<"Any answer that is entered beyond the allowed time slot will not be recorded."<<endl;
    cout << "Are we clear?(enter 'y' to start "<<timer<<" seconds timer)(y)" <<endl;
    string y = "n";
    cin >> y;
    while (y != "y") {
        cout << "Please review the timer rule and enter 'y' to start "<<timer<<" seconds timer...(y)" <<endl;
        cin >> y;
    }
    cout <<endl<<timer<<" seconds timer starts now."<<endl;
    cout << "Start generating words: " << endl;
    cout << "Your letters are: " << endl;
    for (int i = 0; i < numletters; i++) {
        cout << currletters[i] << " ";
    }
    cout <<endl;
    //Start timer
    time_t start = time(0);
    time_t end = start + timer;
    string s;
    cin >> s;
    time_t enteredFirstWord = time(0);
    //Records words with timer functioning
    if (s == "-1"){
        
    } else if (enteredFirstWord <= end){
        wordlist.push(s);
        time_t startNext = time(0);
        while (s != "-1" && startNext <= end) {
            cin >> s;
            time_t endNext = time(0);
            if (s != "-1" && endNext <= end){
                wordlist.push(s);
            } else {
                if (s == "-1"){
                    break;
                } else if (endNext - start == timer){
                    cout <<"You entered your last word right at the "<<timer<<" seconds limit."<<endl;
                    cout <<"You last answer is not recorded."<<endl<<endl;
                    break;
                } else {
                    cout <<"You entered your last word in "<<endNext - start<<" seconds from the beginning, which exceeds "<<timer<<" seconds."<<endl;
                    cout <<"You last answer is not recorded."<<endl<<endl;
                    break;
                }
            }
            startNext = time(0);
        }
    } else {
        cout <<"You entered your first word in "<<enteredFirstWord - start<<" seconds, which exceeds "<<timer<<" seconds."<<endl;
        cout <<"You answer is not recorded."<<endl;
    }
}

char * Game::getLetters(int x) {
	char vowel[5] = {'a','e','i','o','u'};
	char conso[21] = {'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z'};
	char *curr = new char[x];
 	int v = rand() %(x-1) + 1;

	for (int i = 0; i < v; i++) {
		int y = rand() %5;
		curr[i] = vowel[y];
	}
	for (int i = v; i < x; i++) {
		int y = rand() %21;
		curr[i] = conso[y];
	}
	return curr;
}
bool Game::checkWLetters(string s) {
	char tempchar[numletters];
	for (int i = 0; i < numletters; i++) {
		tempchar[i] = currletters[i];
	}
	for (int i = 0; i < s.size(); i++) {
		int j = 0;
		while ((j < numletters) && (tolower(s[i]) != tempchar[j] )) {
			j++;
		}
		if (j == numletters) {
			return false;
		}
		tempchar[j] = '1';
	}
	return true;
}

//helper function to find the index of an element in an array
//https://stackoverflow.com/questions/3909784/how-do-i-find-a-particular-value-in-an-array-and-return-its-index
int Game:: find(char arr[], int len, char seek)
{
    for (int i = 0; i < len; ++i)
    {
        if (arr[i] == seek) return i;
    }
    return -1;
}

int Game:: getWordsScore(string word) {
    char letterList[26] = {'E' ,'S' ,'I' ,'A' ,'R' ,'N' ,'T' ,'O' ,'L' ,'C' ,'U' ,'D' ,'P' ,'M' ,'G' ,'H' ,'B' ,'Y' ,'F' ,'V' ,'K' ,'W' ,'Z' ,'X' ,'Q' ,'J'};
    int wordScore = 0;
    for (int i = 0; i < word.length(); i++){
        char curr = toupper(word[i]);
        int index = find(letterList, 26, curr);
        wordScore += (index + 1);
    }
    return wordScore;
}

void Game:: checkWordsForScore() {
	NodeL *tmp = wordlist.first;
    int wordScore = 0;
	while (tmp != NULL) {
		if (checkWLetters(tmp->word) ) {
			cout << tmp->word << " is okay  letterwise" << endl;

			if (dict->findWord(tmp->word,dict->root)) {
				cout << tmp->word << " is in tree " << endl;
                wordScore = getWordsScore(tmp->word);
				tmp->wscore = wordScore;
			}
			else {
				cout << tmp->word << " NOT in tree " << endl;
                wordScore = getWordsScore(tmp->word);
				tmp->wscore = 0 - wordScore;
			}
		}
		else {
			cout << tmp->word << " is invalid letterwise" << endl;
            wordScore = getWordsScore(tmp->word);
			tmp->wscore = 0 - wordScore;
		}
		tmp = tmp->next;
	}
}

void Game::readTreeFromFile () {
	dict = new AVLTree(AVL);
	ifstream file(dictfile.c_str());
	string word;
    int i = 1;
	while (!file.eof()) {
		file >> word;
		//if (!file.eof()) {
        cout <<endl;
        cout <<i<<endl;
			cout << "Adding: " << word << endl;
            dict->addNode(word); //Me: had difficulties in writing it recursive so changed to iteration
			//dict->insert(word);
		//}
        //DEBUG: dict->printIO(dict->root);
        i++;
	}
	return;
}

	//=


