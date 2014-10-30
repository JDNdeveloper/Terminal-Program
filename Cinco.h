/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef CINCO_H
#define CINCO_H
#include "Dictionary.h"
#include "Terminal.h"

class Cinco{
 public:
  Cinco(Terminal *TO){ cheated=false; numguesses=0; dict = new Dictionary("cinco-words.txt");}
  void start(std::string bob[]){ ConsoleUI(); } // public interface to play game of cinco
 private:
  std::string toLowerCase(std::string);
  int countMatchingLetters(std::string, std::string); // find common letters in any order
  int countInPlaceLetters(std::string, std::string);  // find common letters in place
  void ConsoleUI();  // play the game with text/keybd/screen UI
  Dictionary *dict; // legal words for the game
  int numguesses; // track number of guesses used
  bool cheated; // flag set to true if cheat code is used
  std::string secret; // word to guess
};

#endif
