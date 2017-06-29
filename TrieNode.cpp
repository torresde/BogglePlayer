#include <string>
#include <iostream>
#include "TrieNode.h"

TrieNode::TrieNode (char c, bool b):
    item(c),
    end(b)
{
    for(size_t i = 0; i < 26; i++) {
        letter[i] = nullptr;
    }
}

TrieNode::TrieNode (const TrieNode& rhs):
    item(rhs.item),
    end(rhs.end)
{
    for (size_t i = 0; i < 26; i++) {
        if (rhs.letter[i] != nullptr) {
            letter[i] = new TrieNode(*rhs.letter[i]);
        } else {
            letter[i] = nullptr;
        }
    }
}

TrieNode::~TrieNode() {
    for (size_t i = 0; i < 26; i++) {
        delete letter[i];
        letter[i] = nullptr;
    }
}

const TrieNode& TrieNode::operator= (const TrieNode& rhs){
    if (this != &rhs) {
        TrieNode tmp(rhs);
        std::swap(item, tmp.item);
        std::swap(end, tmp.end);
        std::swap(letter, tmp.letter);
    }
    return *this;
}

void TrieNode::insert (const std::string& str){
    if(str.empty()) {
        return;
    }

    int index = str[0] - 'a';
    if (letter[index] == nullptr) {
        letter[index] = new TrieNode(str[0], str.length() == 1);
    }

    if (str.length() ==1) {
        letter[index]->end = true;
    } else if (str.length() > 1) {
        nodePtr tmp = letter[index];

        for (size_t i = 1; i < str.length(); i++) {
            index = str[i]-'a';

            if (tmp->letter[index] == nullptr) {
                tmp->letter[index] = new TrieNode(str[i], i == str.length()-1);
            }

            tmp = tmp->letter[index];
        }
        tmp->end = true;
    }
}

bool TrieNode::isWord (const std::string& str) const{
    if (str.empty()){
        return false;
    }
    if (letter[str[0]-'a'] != nullptr) {
        if (str.length() == 1) {
            return letter[str[0]-'a']->end;
        }
        nodePtr tmp = letter[str[0]-'a'];
        for (size_t i = 1; i < str.length(); i++) {
            if (tmp->letter[str[i]-'a'] == nullptr) {
                return false;
            }
            tmp = tmp->letter[str[i]-'a'];
        }

        if (tmp->end) {
            return true;
        }
    }
    return false;
}

bool TrieNode::isPrefix (const std::string& pre) const{
    if (pre.empty()){
        return true;
    }
    if (letter[pre[0]-'a'] != nullptr) {
        if (pre.length() == 1) {
            return true;
        }
        nodePtr tmp = letter[pre[0]-'a'];
        for (size_t i = 1; i < pre.length(); i++) {
            if (tmp->letter[pre[i]-'a'] == nullptr) {
                return false;
            }
            tmp = tmp->letter[pre[i]-'a'];
        }

        return true;
    }
    return false;
}

void TrieNode::print (const std::string& str) const
{
    nodePtr tmp;
    if (!str.empty()) {
        int index = str[0] - 'a';
        if (letter[index] != nullptr) {
            tmp = this->letter[index];
        } else {
            return;
        }
        std::string newstr = str.substr(1, str.size() - 1);
        while (!newstr.empty()) {
            index = newstr[0] - 'a';
            if (tmp->letter[index] != nullptr) {
                tmp = tmp->letter[index];
            } else {
                return;
            }
            newstr = newstr.substr(1, str.size() - 1);
        }

        if (tmp->end) {
            std::cout << str << std::endl;
        }

        for (size_t i = 0; i < 26; i++) {
            if (tmp->letter[i] != nullptr) {
                printWords (tmp->letter[i], str);
            }
        }

    } else {
        for (size_t i = 0; i < 26; i++) {
            if (letter[i] != nullptr) {
                printWords (letter[i], str);
            }
        }
    }

}

void TrieNode::printWords (nodePtr tmp, const std::string& str) const
{
    std::string newstr = str + tmp->item;
    if (tmp->end) {
        std::cout << newstr << std::endl;
    }

    for (size_t i = 0; i < 26; i++) {
        if (tmp->letter[i] != nullptr) {
            printWords(tmp->letter[i], newstr);
        }
    }
}

size_t TrieNode::wordCount() const{
    size_t count(0);
    for(size_t i = 0; i < 26; i++){
        if(this->letter[i] != nullptr) {
            count = count + countHelp(letter[i]);
        }
    }
    return count;
}

size_t TrieNode::countHelp(nodePtr tmp) const{
    size_t count(0);
    if(tmp->end) {
        count++;
    }
    for(size_t i = 0; i < 26; i++){
        if(tmp->letter[i] != nullptr) {
            count = count + countHelp(tmp->letter[i]);
        }
    }
    return count;
}