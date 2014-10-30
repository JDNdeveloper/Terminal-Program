/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef USERLOGIN_H
#define USERLOGIN_H
#include "Terminal.h"


class UserLogin {
    public:
        UserLogin(Terminal *TO) {T = TO;}
        void start(string SA[]);
    private:
        Terminal *T;
        void upperCase(string &S);
        void changePassword();
        bool allAlpha(string S);
        static int IA[28];
        void createAccount();
        bool directoryExists(string S);
};

#endif
