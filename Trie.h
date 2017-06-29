#include <string>
#include "TrieNode.h"

#ifndef TRIE_H
#define TRIE_H
class Trie {
private:

    TrieNode* myRoot;

public:

    Trie();
    Trie(const Trie& rhs);
    const Trie& operator= (const Trie& rhs);
    ~Trie();
    void insert(const std::string& word);
    void loadFromFile(const std::string& filename);
    bool isWord(const std::string& word) const;
    bool isPrefix(const std::string& pre) const;
    void print() const;
    size_t wordCount() const;

};
#endif