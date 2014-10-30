/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef SOLITAIRE_H
#define SOLITAIRE_H
#include <iostream>
#include "Terminal.h"

class Solitaire {
 public:
  Solitaire(Terminal *TO) {T = TO;}
  void setter(bool tempEncrypt=true, int theArray[]=0,
            std::string message="-1");
  void start(std::string SA[]);
  void starter();
  void setEncrypt(bool tempEncrypt) {encrypt=tempEncrypt;}
  bool getEncrypt() {return encrypt;}
  void setMessage(std::string message) {mssg=message;}
  std::string getMessage() {return mssg;}
  std::string getEncrypted() {return encr;}
  int getSize() {return SIZE;}
  void setKey(int []);
  int *getKey();
 private:
  Terminal *T;
  static const int JA = 27;
  static const int JB = 28;
  static const int SIZE = 28;
  static const int deck[28];

  int key[28];
  bool encrypt;
  std::string mssg;
  std::string encr;

  void swap(bool);
  void tripleCut();
  void topCardShuffle();

  void changeString();
};

#endif
