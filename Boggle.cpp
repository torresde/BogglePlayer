#include <iostream>
#include <fstream>
#include "Boggle.h"


Boggle::Boggle():
    compScore(0),
    playerScore(0)
{

    std::cout << "Reading Board from boggle-in.txt: " << std::endl;

    std::ifstream fin;
    fin.open("boggle-in.txt");
    if (fin.fail()) {
        throw std::invalid_argument("Unable to open boggle-in.txt for reading.");
    }

    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            fin >> board[i][j].val;
            board[i][j].used = false;
        }
    }

    ospd.loadFromFile("ospd.txt");
}

void Boggle::clean(){
    for(int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
            board[i][j].used = false;
        }
    }
}

void Boggle::inputWords() {
    std::cout << "Enter words. Input \"q\" when finished:" << std::endl;
    std::string tmp;
    std::cin >> tmp;

    bool found;
    while (tmp != "q") {
        found = false;
        if (tmp.length() >3) {
            if(ospd.isWord(tmp)) {

                for(int i=0; i<4; i++) {
                    for (int j=0; j<4; j++) {


                        if(board[j][i].val == tmp[0]){
                            found = checkWord(j, i, tmp.substr(1, tmp.length()-1));
                            clean();
                        }
                    }
                }
            }
        }
        if (found) {
            if(!player.isWord(tmp)) {
                playerScore += tmp.length()-3;
                player.insert(tmp);
            }
        }
        std::cin >>tmp;
    }
}

bool Boggle::checkWord(int x, int y,std::string tmp) {

    if(board[x][y].used) {
        return false;
    }

    board[x][y].used = true;
    if(tmp.length() == 0){
        return true;
    }

    bool move[8];
    for (size_t k=0; k<8; k++) {
        move[k]=false;
    }

    std::string newtmp = tmp.substr(1, tmp.length()-1);
    if(inBound(x-1, y)) {
        if(board[x-1][y].val == tmp[0]){
            move[0] = checkWord(x-1, y, newtmp);
        }
    }
    if(inBound(x-1, y-1)) {
        if(board[x-1][y-1].val == tmp[0]){
            move[1] = checkWord(x-1, y-1, newtmp);
        }
    }
    if(inBound(x-1, y+1)) {
        if(board[x-1][y+1].val == tmp[0]){
            move[2] = checkWord(x-1, y+1, newtmp);
        }
    }
    if(inBound(x, y-1)) {
        if(board[x][y-1].val == tmp[0]){
            move[3] = checkWord(x, y-1, newtmp);
        }
    }
    if(inBound(x, y+1)) {
        if(board[x][y+1].val == tmp[0]){
            move[4] = checkWord(x, y+1, newtmp);
        }
    }
    if(inBound(x+1, y-1)) {
        if(board[x+1][y-1].val == tmp[0]){
            move[5] = checkWord(x+1, y-1, newtmp);
        }
    }
    if(inBound(x+1, y)) {
        if(board[x+1][y].val == tmp[0]){
            move[6] = checkWord(x+1, y, newtmp);
        }
    }
    if(inBound(x+1, y+1)) {
        if(board[x+1][y+1].val == tmp[0]){
            move[7] = checkWord(x+1, y+1, newtmp);
        }
    }
    board[x][y].used = false;
    return (move[0] || move[1] || move[2] || move[3]
            || move[4] || move[5] || move[6] || move[7]);
}

bool Boggle::inBound(int x, int y) {
    return (x < 4 && x >= 0 && y >= 0 && y < 4);
}

void Boggle::checkBoard() {
    std::string tmp("");
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
                checkPos(x,y, tmp);
        }
    }
}

void Boggle::checkPos(int x, int y, std::string tmp){

    if (x<0 || x>3 || y<0 || y>3) {
        return;
    }
    if (board[x][y].used) {
        return;
    }

    tmp += board[x][y].val;
    board[x][y].used = true;

    if(ospd.isPrefix(tmp)){
        if(tmp.length() > 3) {
            if (ospd.isWord(tmp)) {
                if(!player.isWord(tmp)) {
                    if(!found.isWord(tmp)) {
                        compScore += tmp.length()-3;
                        found.insert(tmp);
                    }
                }
            }
        }

        checkPos(x+1, y-1, tmp);
        checkPos(x+1, y, tmp);
        checkPos(x+1, y+1, tmp);
        checkPos(x, y-1, tmp);
        checkPos(x, y+1, tmp);
        checkPos(x-1, y-1, tmp);
        checkPos(x-1, y, tmp);
        checkPos(x-1, y+1, tmp);
    }
    board[x][y].used = false;
}

void Boggle::printBoard() {
    for (size_t y=0; y<4; y++) {
        for (size_t x=0; x<4; x++) {
            std::cout << board[y][x].val;
        }
        std::cout << "\n";
    }
}

void Boggle::printPlayer() {
    std::cout << "\nThe player found the following words:"
            "\n============" << std::endl;
    player.print();
    std::cout << "============\nThe player found " <<
              player.wordCount() << " words." << std::endl;
}

void Boggle::printComp() {
    std::cout << "\nThe computer found the following words:"
            "\n============" << std::endl;
    found.print();
    std::cout << "============\nThe computer found " <<
              found.wordCount() << " words.\n" << std::endl;
}

void Boggle::printScores(){
    std::cout << "Final Scores\n============\n"
            "Player: " << playerScore << "\nComputer: "
              << compScore << "\n============";
}