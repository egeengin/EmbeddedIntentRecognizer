#ifndef MODIFIEDTRIE_TRIEWITHINTENTS_H
#define MODIFIEDTRIE_TRIEWITHINTENTS_H

#include <string>

// Define the trie size = Number of letters in English alphabet
#define ALPHABET_SIZE 26

// A class to store a Trie node with intentID at end
class TrieWithIntents {
public:
    bool isLeaf, end;
    int intentID;

    TrieWithIntents *letter[ALPHABET_SIZE];

    TrieWithIntents();

    void insert(std::string, int);

    bool erase(TrieWithIntents *&currentNode, std::string word);

    int search(std::string);

    bool haveChildren(TrieWithIntents const *);
};


#endif //MODIFIEDTRIE_TRIEWITHINTENTS_H
