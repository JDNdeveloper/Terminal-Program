/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include "Scrambler.h"

using namespace std;

/*
 *readLines collects lines of input until EOF is
 *reached.
 */
void Scrambler::readLines() {
  cout << "Type lines to scramble, hit enter twice to exit\n" << endl;
  string input;
  while (getline(cin, input) && input.length()!=0) {
    seperateString(input);
    cout << "\n\n";
  }
}

/*
 *seperateString takes a string as a parameter and passes it
 *into the print function as long as the counter variable
 *doesn't excede the amount of characters in the string.
 */
void Scrambler::seperateString(string theWord) {
  int j = 0;
  while (j < theWord.size()) {
    j = seperateWord(theWord, j);
  }
}

/*
 *seperateWord takes a string and counter variable as parameters
 *and disects the string into individual words and
 *passes that on to the word scrambler function if
 *it is over three characters in length.
 *It returns the counter variable.
 */
int Scrambler::seperateWord(string newInput, int num1) {
  string newWord = "";
  int i = num1;
  while (newInput[i] != ' ' && i <  newInput.size()) {
    newWord += newInput[i];
    i++;
  }
  if (newWord.size() > 3) {
    wordScramble(newWord);
  } else {
    cout << newWord << " ";
  }
  return  ++i;
}

/*
 *wordScramble takes a string as a parameter and
 *scrambles the insides while retaining the
 *first and last letters and any trailing
 *punctuation. It determines a strings puncatuation
 *by calling the checkPunctuation function.
 */
void Scrambler::wordScramble(string word) {
  int length = word.size();
  if (!checkPunctuation(word)) {
    for (int v = (length - 2); v > 0; v--) {
      int num = randomNum(length - 2);
      char char1 = word[v];
      word[v] = word[num];
      word[num] = char1;
    }
  } else {
    for (int v = (length - 3); v > 0; v--) {
      int num = randomNum(length - 3);
      char char1 = word[v];
      word[v] = word[num];
      word[num] = char1;
    }
  }
  cout << word << " ";
}

/*
 *checkPunctuation takes a string as a parameter
 *and checks the last character to see if it matches
 *any of the punctuation I am checking for. If it
 *does match than it returns true and if it doesn't
 *it returns false.
 */
 bool Scrambler::checkPunctuation(string aWord) {
  int lastChar = (aWord.size() - 1);
  if (aWord[lastChar] == '.' || aWord[lastChar] == '?'
      || aWord[lastChar] == '!' || aWord[lastChar] == ','
      || aWord[lastChar] == ';' || aWord[lastChar] == ':') {
    return true;
  } else {
    return false;
  }
}

/*
 *randomNum takes the length of a string as a
 *parameter and returns a random number ranging from
 *one to the 'theLength' variable value.
 */
int Scrambler::randomNum(int theLength) {
  return rand() % theLength + 1;
}
