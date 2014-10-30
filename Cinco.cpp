/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include <cctype>
#include "Cinco.h"
#include "Dictionary.h"

using std::cout;
using std::endl;
using std::string;

/*
 * ConsoleUI deals with printing out to the console
 * and with gathering user input. It also calls other
 * helper functions in the Dictionary class and in this
 * class to help the Cinco game run according to
 * specifications.
 */
void Cinco::ConsoleUI() {
  cout << "\nCinco!" << endl;
  cout << "By Jayden Navarro" << endl;
  cout << "Type \"EXIT\" to end" << endl;
  cout << "I'm thinking of a five letter word..." << endl;

  numguesses = 1;
  bool gameOver = false;
  string guess = "";
  int matching = 0;
  int inplace = 0;

  secret = dict->getLegalSecretWord();

  while (!gameOver) {
    cout << "Your guess? ";
    std::cin >> guess;

    guess = toLowerCase(guess);
    if (guess.compare("exit")==0) {
        cout << "\n- Bye! -\n" << endl;
        return;
    }
    if (guess.compare("xxxxx") == 0) {
      cout << "Secret Word is: " << secret << endl;
      cheated = true;
      numguesses++;
    } else if (dict->validWord(guess)) {
      matching = countMatchingLetters(guess, secret);
      inplace = countInPlaceLetters(guess, secret);
      if (inplace < 5) {
        cout << "Matching: " << matching << endl;
        cout << "In-Place: " << inplace << endl;
        numguesses++;
      } else {
        gameOver = true;
      }
    } else {
      cout << "I don't know that word." << endl;
    }
  }
  cout << "Correct! You got it in " << numguesses;
  if (cheated)
    cout << " guesses, but only by cheating.\n" << endl;
  else if (numguesses == 1)
    cout << " guess.\n" << endl;
  else
    cout << " guesses.\n" << endl;
}

/*
 * toLowerCase takes a string parameter and converts
 * each character into the lower case ascii value of
 * it's letter, and leaves it the same if already lower
 * case by using the tolower() library function. It then
 * returns the new all lower case string.
 */
string Cinco::toLowerCase(string newString) {
  string newWord = newString;
  for (int i = 0; i < newString.length(); i++) {
    newWord[i] = tolower(newString[i]);
  }
  return newWord;
}

/*
 * countMatchingLetters takes two strings as parameters
 * and makes word1.length * word1.length comparisons.
 * I.E. if word1 was 5 characters long it would make
 * 25 comparisons. It does the comparisons by going through
 * each character and comparing it to every character of
 * the other string. But this comparison alone doesn't
 * increase the counter. First it checks to see if this
 * character is contained in the "letters" character array.
 * If it is then the loop continues without increasing the
 * counter but if it is not in "letters" then it is added
 * to the "letters" array at position i and the counter
 * increases. After the loop the function returns counter.
 * The array "letters" is only the length of
 * word1 because there can only be at most word1.length()
 * letters that are in common between word1 and word2.
 * This function is limited because word1 and word2 must be
 * the same length in order for this function to work properly.
 * Through out this function word1.length() should be
 * interchangeable with word2.length(), I just chose the
 * former because it seemed clearer.
 */
int Cinco::countMatchingLetters(string word1, string word2) {
  char *letters = new char[word1.length()];
  int counter = 0;
  bool repeat = false;
  int j = 0;
  for (int i = 0; i < word1.length(); i++) {
    for (j = 0; j < word1.length(); j++) {
      if (word1[i] == word2[j]) {
        repeat = false;
        for (int k = 0; k < word1.length(); k++) {
          if (word1[i] == letters[k]) {
            repeat = true;
          }
        }
        if (!repeat) {
          letters[i] = word1[i];
          counter++;
        }
      }
    }
  }
  return counter;
}

/*
 * countInPlaceLetters takes two strings as parameters
 * and compares each character position to see if they
 * are the same. If they are then the counter increases.
 * It returns counter at the end. This function is limited
 * because it will not work if word1 and word2 don't have
 * the same length.
 */
int Cinco::countInPlaceLetters(string word1, string word2) {
  int counter = 0;
  for (int i = 0; i < word1.length(); i++) {
    if (word1[i] == word2[i])
      counter++;
  }
  return counter;
}
