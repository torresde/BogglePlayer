cmake_minimum_required(VERSION 3.6)
project(BoggleProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Trie.cpp
    Trie.h
    TrieNode.cpp
    TrieNode.h
    Boggle.cpp
    Boggle.h
    BoggleDriver.cpp)

add_executable(BoggleProject ${SOURCE_FILES})