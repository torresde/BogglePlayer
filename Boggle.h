#include "Trie.h"

#ifndef BOGGLE_H
#define BOGGLE_H


struct die {
    char val;
    bool used;
};

class Boggle {

private:
    die board[4][4];
    Trie ospd, found, player;
    void clean();
    size_t compScore, playerScore;

public:
    // creates a boggle object and reads in boggle-in.txt and sets ospd trie
    Boggle();
    // takes in words from the player to check on the board
    void inputWords();
    // checks the board for the computer for words
    void checkBoard();
    // checks if a position is in bounds
    bool inBound(int x, int y);
    // checks words that are submitted by the player
    bool checkWord(int x, int y, std::string tmp);
    // checks positions on the board for words
    void checkPos(int x, int y, std::string tmp);
    // prints a version of the board to the console
    void printBoard();
    // prints words found by the player
    void printPlayer();
    // prints words found by the computer
    void printComp();
    // prints the scores
    void printScores();
};

#endif
