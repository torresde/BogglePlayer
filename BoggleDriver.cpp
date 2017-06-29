#include "Boggle.h"

int main () {

    Boggle board;
    board.printBoard();

    board.inputWords();
    board.printPlayer();

    board.checkBoard();
    board.printComp();

    board.printScores();

    return 0;
}