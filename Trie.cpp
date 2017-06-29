#include <string>
#include "Trie.h"
#include <fstream>
#include <iostream>

Trie::Trie():
    myRoot(new TrieNode(' ', false))
{}

Trie::Trie(const Trie& rhs):
    myRoot(new TrieNode(' ', false))
{
    if(rhs.wordCount() != 0) {
        myRoot= new TrieNode(*rhs.myRoot);
    }
}

const Trie& Trie::operator= (const Trie& rhs)
{
    if(this != &rhs) {
        Trie tmp(rhs);
        std::swap(myRoot, tmp.myRoot);
    }
    return *this;
}

Trie::~Trie()
{
    delete myRoot;
    myRoot = nullptr;
}

void Trie::insert (const std::string& word){
    myRoot->insert(word);
}

void Trie::loadFromFile(const std::string& filename){
    std::ifstream file(filename.c_str());

    if (!file) {
        throw std::invalid_argument("Unable to open file. Press enter to exit program.");
    }

    std::string tmp;
    while (file >> tmp) {
            insert(tmp);
    }
}

bool Trie::isWord(const std::string& word) const{
    return myRoot->isWord(word);
}

bool Trie::isPrefix(const std::string& pre) const{
    return myRoot->isPrefix(pre);
}

void Trie::print() const{
    myRoot->print("");
}

size_t Trie::wordCount() const{
    return myRoot->wordCount();
}