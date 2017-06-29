#include <string>

#ifndef TRIENODE_H
#define TRIENODE_H

class TrieNode
{
private:

    char item;
    bool end;
    TrieNode* letter[26];

    typedef TrieNode *nodePtr;

    void printWords (nodePtr tmp, const std::string& str) const;
    size_t countHelp(nodePtr tmp) const;

public:

    TrieNode (char c, bool b);
    TrieNode (const TrieNode& rhs);
    ~TrieNode();
    const TrieNode& operator= (const TrieNode& rhs);
    void insert (const std::string& str);
    bool isWord (const std::string& str) const;
    bool isPrefix (const std::string& pre) const;
    void print (const std::string& str) const;
    size_t wordCount() const;

};

#endif