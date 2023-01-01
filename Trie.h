#include <iostream>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;

class TrieNode
{
public:
    Dictionary *dict;        // Dictionary object made from Dictionary.h
    TrieNode *children[73]; // 73 children for 73 ASCII characters
    bool isEndOfWord;        // true if the node represents end of a word

    TrieNode() // Constructor
    {
        dict = NULL;
        isEndOfWord = false;
        for (int i = 0; i < 73; i++)
            children[i] = NULL;
    }
};

class Trie
{
public:
    TrieNode *root; // root node of the trie

    Trie() // Constructor
    {
        root = new TrieNode();
    }

    int returnCharIdx(char c) //Return the index of char
    {
        // ".", "-"
        if (c == 46 || c == 45)
        {
            c = c - 45; // Maps to index 0 and 1
        }
        // num 
        else if (c >= 48 && c <= 57)
        {
            c = c - 45; // Maps to index 2 to 12
        }
        // A-Z
        else if (c >= 65 && c <= 90)
        {
            c = c - 52; // Maps to index 13 to 38
        }
        // a-z
        else if (c >= 97 && c <= 122)
        {
            c = c - 58; // Maps to index 39 to 64
        }
        // " ", "!", """, "#", "$", "%", "&", "'"
        else if (c >= 32 && c <= 39)
        {
            c = c + 33; // Maps to index 65 to 73
        }
        return c;
    }

    void insert(Dictionary dict) // Insert a word into the trie
    {
        
        TrieNode *temp = root;
        // loop through all the characters of the word
        for (int i = 0; i < dict.word.length(); i++)
        {
            char c = dict.word[i];
            int index = returnCharIdx(c);
            if (temp->children[index] == NULL) // if the character is not present in the trie
                temp->children[index] = new TrieNode();
            temp = temp->children[index];
        }
        temp->dict = new Dictionary(dict); // store the dictionary object in the trie
        temp->isEndOfWord = true;          // mark the end of the word
    }

    Dictionary search(string word) // Search a word in the trie
    {
        TrieNode *temp = root;                  // start from the root node
        for (int i = 0; i < word.length(); i++) // loop through all the characters of the word
        {
            char c = word[i];
            int index = returnCharIdx(c);
            if (temp->children[index] == NULL) // if the character is not present in the trie
                return Dictionary("", "", ""); // return an empty dictionary object
            temp = temp->children[index];
        }
        if (temp->isEndOfWord)  // if the word is present in the trie
            return *temp->dict; // return the dictionary object
        else
            return Dictionary("", "", ""); // return an empty dictionary object
    }

    void display(TrieNode *temp, string word) // Display all the words in the trie
    {
        if (temp->isEndOfWord) // Base case -> will print the word
            cout << *temp->dict << endl;
        for (int i = 0; i < 73; i++)
        {
            if (temp->children[i] != NULL)
            {
                word.push_back(i);                // Appends the character to the word
                display(temp->children[i], word); // recursively call unless reaches end of word (base case)
                word.pop_back();                  // removes the last character and call for othe branch
            }
        }
    }

    void deleteWord(string word) // Delete a word from the trie
    {
        TrieNode *temp = root;
        for (int i = 0; i < word.length(); i++) // Traverse upto last character of the word
        {
            char c = word[i];
            int index = returnCharIdx(c);
            if (temp->children[index] == NULL)
                return;
            temp = temp->children[index];
        }
        if (temp->isEndOfWord) // Make it false ultimately doing the deletion operation
            temp->isEndOfWord = false;
    }

    void destroy(TrieNode *temp) // Destroy the trie
    {
        for (int i = 0; i < 73; i++)
        {
            if (temp->children[i] != NULL)
                destroy(temp->children[i]);
        }
        delete temp;
    }
};

void writeToFileUtil(TrieNode *root, fstream &myfile)
{
    if (root == NULL)
        return;

    // If a word is present
    if (root->isEndOfWord)
    {
        myfile << root->dict->word << "," << root->dict->pos << "," << root->dict->meaning << endl;
    }

    for (int i = 0; i < 73; i++)
        writeToFileUtil(root->children[i], myfile);
}

// Filter the words by prefix and return a trie with these words
Trie *filterWords(Trie *trie, string prefix)
{
    TrieNode *temp = trie->root;
    for (int i = 0; i < prefix.length(); i++) // loop through all the characters of the prefix
    {
        char c = prefix[i];
        int index = trie->returnCharIdx(c);
        if (temp->children[index] == NULL) // if the character is not present in the trie
            return new Trie();                 // return an empty trie
        temp = temp->children[index];      // move to the next node
    }
    Trie *filteredTrie = new Trie();
    filteredTrie->root = temp; // set the root of the filtered trie to the last node of the prefix
    return filteredTrie;      // return the filtered trie
}
