#include "TrieWithIntents.h"
#include <iostream>

// #define DEBUG

using namespace std;

// TrieWithIntents: Class of a modifiedTrie which has intentID in the end node.
TrieWithIntents::TrieWithIntents() {
    this->isLeaf = false;
    this->end = true;
    this->intentID = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        this->letter[i] = nullptr;
    }
}

// Iterative function to insert a key into a Trie
void TrieWithIntents::insert(string word, int intentID) {
    TrieWithIntents *currentNode = this; // root
    for (int i = 0; i < word.length(); i++) {
        // create a new node if no path
        if (currentNode->letter[word[i] - 'a'] == nullptr) {
            currentNode->letter[word[i] - 'a'] = new TrieWithIntents();
        }
        currentNode->end = false;

        currentNode = currentNode->letter[word[i] - 'a']; // next node
    }
    currentNode->isLeaf = true;

    if (currentNode->end) {
        currentNode->intentID = intentID;
#ifdef DEBUG
        std::cout << "Trie.insert: " << word << ":" << intentID << endl; // TODO: Debug (will be deleted on delivery)
#endif
    }
}

int TrieWithIntents::search(string key) {
    // return false if Trie is empty
    if (this == nullptr) {
        return false;
    }

    TrieWithIntents *currentNode = this;
    for (int i = 0; i < key.length(); i++) {
        currentNode = currentNode->letter[key[i] - 'a']; //next node

        if (currentNode == nullptr) { // string not in trie
            return false;
        }
    }
    if (currentNode->isLeaf) // end of the string in trie
        return currentNode->intentID;
    else
        return 0;
}

bool TrieWithIntents::haveChildren(TrieWithIntents const *currentNode) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (currentNode->letter[i]) {
            return true;    // child found
        }
    }
    return false;
}
