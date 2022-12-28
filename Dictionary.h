#pragma once
#include <string>
using namespace std;

class Dictionary //definition of class Dictionary
{
  public:
    string word; //word
    string pos; //part of speech
    string meaning; //meaning of the word

    Dictionary() //default constructor
    {
      word.push_back('\0');
      pos.push_back('\0');
      meaning.push_back('\0');
    }

    Dictionary(string word, string pos , string meaning) //parametrized constructor
    {
      this->word = word;
      this->pos = pos;
      this->meaning = meaning;
    }

    // << was overloaded for printing and file writing purposes
    friend ostream &operator<<( ostream &output, const Dictionary& dict)
    {
      output << dict.word << " :: " << dict.pos<< " :: " << dict.meaning;
      return output;
    };
};