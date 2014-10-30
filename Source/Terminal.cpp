/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include "Terminal.h"
#include "StandardKeywords.h"
#include "UserLogin.h"
#include "Solitaire.h"
#include "9mm.h"
#include "Cinco.h"
#include "Scrambler.h"
#include "FutureValue.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;


string Terminal::keyword[19] =
    {"CAT", "TAC", "ENCRYPT", "DECRYPT", "LOGIN", "9MM", "CHANGE", "WRITE", "DELETE", "LIST",
      "FOLDER", "HELP", "CF", "CINCO", "MOVE", "COPY", "LOCATION", "FV", "SCRAMBLE"};

void Terminal::start() {
    const int SIZE = 4;
    bool nmm = false;
    string userInput[SIZE] = {"","","",""};
    string rawInput = "";
    UserLogin UL(this);
    UL.start(userInput);
    while (userInput[0].compare("EXIT")!=0
            && userInput[0].compare("LOGOUT")!=0) {
        for (int i = 0; i < SIZE; i++)
            userInput[i] = "";
        if (!nmm) {
            printName();
        }
        getline(cin, rawInput);
        parseString(SIZE, rawInput, userInput);
        int place = -2;
        for (int i = 0; i < ASIZE; i++) {
            if (userInput[0].compare(keyword[i])==0)
                place = i;
        }
        if (userInput[0].compare("EXIT")==0
            || userInput[0].compare("LOGOUT")==0)
            place = -1;
        if (nmm)
            place = -6;

        switch (place+1) {
            case 0:
                break;
            case 1: case 2: case 8: case 9: case 10: case 11:
            case 12: case 13: case 15: case 16: case 17:
                starter<StandardKeywords>(userInput);
                break;
            case 3: case 4:
                starter<Solitaire>(userInput);
                break;
            case 5: case 7:
                starter<UserLogin>(userInput);
                break;
            case 6:
                cout << "Command not found\n";
                nmm = true; //fixes strange error
                break;
            case -5:
                nmm = false;
                break;
            case 14:
                starter<Cinco>(userInput);
                nmm = true;
                break;
            case 18:
                starter<FutureValue>(userInput);
                nmm = true;
                break;
            case 19:
                starter<Scrambler>(userInput);
                break;
            default:
                if (userInput[0].length() != 0)
                    cout << "\"" << userInput[0] << "\" not a keyword" << endl;
                else
                    cout << "No keyword entered" << endl;
                break;
        }
    }
}

void Terminal::printName() {
    if (location.length()==0)
        cout << "< " << userName << " >$ ";
    else
        cout << "< " << userName << " - " << location << " >$ ";
}

void Terminal::parseString(const int LENGTH, string S, string A[]) {
    string names[LENGTH];
    int counter = 0;
    for (int j = 0; j < LENGTH; j++) {
        for (int i = 0; S[counter] != ' ' && counter < S.length(); i++) {
            names[j].append(1, S[counter]);
            counter++;
        }
        A[j] = names[j];
        counter++;
    }
    for (int i = 0; i < A[0].length(); i++)
        A[0][i] = toupper(A[0][i]);
}
