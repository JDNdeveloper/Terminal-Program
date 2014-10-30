/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

using std::string;

class Terminal {
    public:
        Terminal() {location=""; userName="GUEST"; member=false;
                    completePath = userName + location;}
        void start();
        string getLocation() const {return location;}
        string getCompletePath() {return completePath;}
        string getUserName() const {return userName;}
        string getFullUserName() {return fullUserName;}
        void setUserName(string name) {userName = name;}
        void setLocation(string place) {location = place;}
        void setCompletePath(string path) {completePath = path;}
        void setFullUserName() {fullUserName = "Users/" + userName;}
    private:
        static string keyword[19];
        string location;
        string completePath;
        string userName;
        string fullUserName;
        bool member;
        static const int ASIZE = 19;
        void printName();
        void parseString(const int LENGTH, string S, string A[]);
        template <class T>
        void starter(string A[]);
};

template <class T>
void Terminal::starter(string A[]) {
    T obj1(this);
    obj1.start(A);
}

#endif
