/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include "Solitaire.h"

using std::string;
using std::endl;
using std::cout;
using std::cin;

const int Solitaire::deck[28] =
    {9, 10, 25, 3, 6, 22, 1, 7, 26, 17, 4, 15, 18, 28,
     16, 14, 8, 27, 13, 20, 11, 19, 2, 24, 23, 21, 5, 12};
/*
 * The Solitaire constructor initializes encrypt to
 * tempEncryt's value, it also does a deep copy of
 * theArray into key, and intializes mssg to message
 * and encr to a blank string.
 */
void Solitaire::setter(bool tempEncrypt, int theArray[],
                     string message) {
  encrypt = tempEncrypt;
  for (int i = 0; i < SIZE; i++)
    key[i] = theArray[i];
  mssg = message;
  encr = "";
}

/*
 * setKey sets all of key's
 * values to array1's values
 */
void Solitaire::setKey(int array1[]) {
  for (int i = 0; i < SIZE; i++)
    key[i] = array1[i];
}

/*
 * getKey returns a pointer to an
 * array that contains the values that
 * 'key' contained.
 *
 */
int *Solitaire::getKey() {
  int *newArray = new int[SIZE];
  for (int i = 0; i < SIZE; i++)
    newArray[i] = key[i];
  return newArray;
}


void Solitaire::start(string SA[]) {
  string fullPath = T->getFullUserName() + "/deck.txt";
  std::ifstream inf(fullPath.c_str());
  std::ofstream outf;
  if (!inf.is_open()) {
      outf.open(fullPath.c_str());
      for (int i = 0; i < 28; i++) {
        outf << deck[i];
        if (i < 27)
          outf << " ";
      }
      outf << endl;
      outf.close();
      outf.clear();
  }
  inf.close();
  inf.clear();


  string string1;
  string string2;
  string myInput;
  string eORd;
  int myArray[28];
  for (int i = 0; i < 28; i++)
    myArray[i] = 0;

  if (SA[1].length() == 0) {
    cout << "Please enter a filename: ";
    getline(cin, myInput);
  } else {
    myInput = SA[1];
  }

  myInput = T->getFullUserName() + "/" + myInput;
  inf.open(myInput.c_str());
  if (inf.fail()) {
    std::cerr << endl << "Error opening File: " << myInput << endl;
    return;
  }

  eORd[0] = tolower(SA[0][0]);

  if (eORd[0] != 'e' && eORd[0] != 'd') {
    std::cerr << endl << "e OR d only" << endl;
    cin.get();
    return;
  }

  std::getline(inf, string1);
  string1.append(" ");
  while (string1[0] == ' ')
    string1.erase(0, 1);

  std::istringstream iss(string1);
  int pos = 0;
  while (getline(iss, string2, ' ')) {
    myArray[pos] = atoi(string2.c_str());
    pos++;
  }
  string userInput;
  bool action = true;
  if (eORd[0] == 'e')
    action = true;
  else
    action = false;
  if (action) {
    cout << "Enter message to be encrypted (non-letters ignored)"
         << endl;
  } else {
    cout << "Enter message to be decrypted (non-letters ignored)"
         << endl;
  }
  getline(cin, userInput);


  setter(action, myArray, userInput);
  starter();
  if (action) {
    cout << "Plaintext message is: " << getMessage() << endl;
    cout << "The encrypted message is: " << getEncrypted()
         << endl;
  } else {
    cout << "The encrypted message is: " << getMessage() << endl;
    cout << "Plaintext message is: " << getEncrypted() << endl;
  }

  string writeToFile = "n";
  if (SA[2].length() == 0) {
    std::cout << "Save to file? y/n: ";
    getline(std::cin, writeToFile);
  }
  if (writeToFile[0] == 'y' || writeToFile[0] == 'Y') {
      std::cout << "Enter a filename to save to: ";
      getline(std::cin, myInput);
      fullPath = T->getCompletePath() + "/" + myInput;
  } else if (SA[2].length() != 0) {
     fullPath = T->getCompletePath() + "/" + SA[2];
  }
  if (SA[2].length() != 0 || writeToFile[0] == 'y') {
    outf.open(fullPath.c_str());
    if (outf.fail()) {
        std::cerr << "\nFile writing failed" << std::endl;
        return;
    }
    outf << getEncrypted();
    outf << endl;
    outf.close();
    cout << "\nSAVED" << endl;
  }
}
/*
 * Start calls changeString and then
 * loops and calls the encryption action
 * functions which manipulate the array, then it
 * finds the keystream value and adds that to the
 * alphabetical value of the character that it is
 * at and adds that to encr. It loops until it has gone
 * through the whole string.
 */
void Solitaire::starter() {
  int keyValue = 0;
  int ascValue = 0;
  string stringTemp = " ";
  const bool action = encrypt;

  changeString();
  for (int i = 0; i < mssg.length(); i++) {
    keyValue = JA;
    while (keyValue == JA
           || keyValue == JB) {
      swap(true);
      swap(false);
      tripleCut();
      topCardShuffle();
      if (key[0] == JB)
        keyValue = key[JA];
      else
        keyValue = key[key[0]];
    }
    if (action) {
      ascValue = (mssg[i] - 'A' + 1) + keyValue;
      if (ascValue > 26)
        ascValue -= 26;
      stringTemp[0] = ascValue + 'A' - 1;
      encr.append(stringTemp);
    } else {
      ascValue = (mssg[i] - 'A' + 1) - keyValue;
      if (ascValue < 1)
        ascValue += 26;
      stringTemp[0] = ascValue + 'A' - 1;
      encr.append(stringTemp);
    }
  }
}


/*
 * ChangeString manipulates mssg so that it
 * only has alphabetical letters in uppercase
 * and adds 'X's to the end until it is equal
 * to a multiple of 5. It puts everything in
 * a temperory string and then sets mssg to this
 * temp string.
 */
void Solitaire::changeString() {
  string temp = "";
  string charString = " ";
  for (int i = 0; i < mssg.length(); i++) {
    if (!(mssg[i] == ' ' || !isalpha(mssg[i]))) {
      charString[0] = toupper(mssg[i]);
      temp.append(charString);
    }
  }
  if (temp.length() % 5 != 0) {
    int remainder = 5 - (temp.length() % 5);
    for (int i = 0; i < remainder; i++)
      temp.append("X");
  }
  mssg = temp;
}


/*
 * Swap moves the jokers the correct
 * amount of places "down the line" like
 * the encryption algorithm dictates. There
 * are two swapping loops and depending on the
 * situation they are used a different amount
 * of times.
 */
void Solitaire::swap(bool AorB) {
  int pos = -1;
  int temp = -1;
  for (int i = 0; i < SIZE; i++) {
    if (AorB) {
      if (key[i] == JA)
        pos = i;
    } else {
      if (key[i] == JB)
        pos = i;
    }
  }

  int repeat = 1;
  int repeat2 = 0;


  if (AorB && key[27] == JA) {
    repeat = 0;
    repeat2 = 1;
  }
  if (!AorB) {
    repeat = 2;
    if (key[26] == JB) {
      repeat = 1;
      repeat2 = 1;
    }
    if (key[27] == JB) {
      repeat = 0;
      repeat2 = 2;
    }
  }


  for (int i = 0; i < repeat; i++) {
    temp = key[pos];
    key[pos] = key[pos+1];
    key[pos+1] = temp;
    pos++;
  }
  for (int j = 0; j < repeat2; j++) {
    temp = key[pos];
    key[pos] = key[j];
    key[j] = temp;
    pos = j;
  }
}


/*
 * tripleCut creates a temporary array
 * and then moves pieces of "key" into
 * that array like the encryption algorithm
 * specifies. At the end it copies all of
 * the values from temp into key.
 */
void Solitaire::tripleCut() {
  int temp[SIZE];
  int tempPos = -1;
  int posA = -1;
  int posB = -1;
  for (int i = 0; i < SIZE; i++) {
    if (key[i] == JA)
      posA = i;
    else if (key[i] == JB)
      posB = i;
  }
  if (posA < posB) {
    tempPos = posA;
    posA = posB;
    posB = tempPos;
  }
  int j = 0;
  for (int i = posA+1; i < SIZE; i++) {
    temp[j] = key[i];
    j++;
  }
  for (int i = posB; i < posA+1; i++) {
    temp[j] = key[i];
    j++;
  }
  for (int i = 0; i < posB; i++) {
    temp[j] = key[i];
    j++;
  }
  for (int i = 0; i < SIZE; i++)
    key[i] = temp[i];
}


/*
 * topCardShuffle moves as many cards
 * to the top that the card at position
 * 27 is. If it is a 28 it moves 27 instead.
 * It moves these values into a temperory array
 * and then at the end sets all of the key values
 * to the temperory array values.
 */
void Solitaire::topCardShuffle() {
  int temp[SIZE];
  int marker1 = 0;
  int marker2 = key[27];
  if (key[27] == JB)
    marker2 = JA;
  for (marker1 = 0; marker1 < 27-key[27]; marker1++) {
    temp[marker1] = key[marker2];
    marker2++;
  }
  marker2 = 0;
  while (marker1 < 27) {
    temp[marker1] = key[marker2];
    marker1++;
    marker2++;
  }
  temp[27] = key[27]; //Not necessary but clarifies
  for (int i = 0; i < SIZE; i++) {
    key[i] = temp[i];
  }
}
