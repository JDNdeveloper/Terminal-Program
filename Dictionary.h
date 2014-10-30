/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iostream>

class Dictionary{
 public:
  Dictionary(char *filename="") {}; // arg: filename of input words text file
  //~Dictionary() { if (words != 0) delete [] words; words = 0;}
  bool validWord(std::string word); // check if word is in Dictionary
  std::string getLegalSecretWord(); // return a random word (w/out repeated letters)
 private:
  bool testSecretWord(int n); // nth word in list has only unique letters?
  static std::string words[2415]; // array of strings (or use a Vector)
  static const int numwords = 2415; // number of words in the dictionary
};

#endif
