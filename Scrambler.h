/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef SCRAMBLER_H
#define SCRAMBLER_H

#include "Terminal.h"

class Scrambler {
    public:
     Scrambler(Terminal *h) {}
     void start(std::string bob[]) {readLines();}
    private:
     void readLines();
     void seperateString(std::string);
     int seperateWord(std::string, int);
     void wordScramble(std::string);
     int randomNum(int);
     bool checkPunctuation(std::string);
};

#endif
