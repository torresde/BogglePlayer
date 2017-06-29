# BogglePlayer
Play boggle against a computer! The boggle board will display and you can enter as many words as you can find that are defined in the lexicon of legal words and are at least four letters long. The computer then finds all the words that were not found by the user. Words of four characters are worth one point, five characters are worth two points, etc.

This application finds all words, of four or more characters, from the Official Scrabble Players Dictionary that are legally playable on a scrabble board. It uses a Trie class to keep a lexicon of acceptable words and to keep track of words that the user has found. This is a recursive backtracking solver.

The ospd.txt file contains the official scrabble player’s dictionary and boggle-in.txt is the board that will be used containing four rows of four characters. The boggle-in.txt file can be changed to any combination of characters.
