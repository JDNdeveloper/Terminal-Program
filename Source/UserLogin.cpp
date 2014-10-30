/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include <fstream>
#include <windows.h>
#include <dirent.h>
#include "UserLogin.h"
#include "Solitaire.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int UserLogin::IA[28] =
    {16, 10, 14, 3, 6, 22, 11, 7, 26, 9, 5, 19,
    18, 27, 17, 3, 25, 28, 13, 20, 1, 15, 2, 12, 23, 21, 4, 24};

void UserLogin::start(string SA[]) {
    if (SA[0].compare("CHANGE")==0) {
        upperCase(SA[1]);
        if (SA[1].compare("PASSWORD")==0) {
            changePassword();
            return;
        } else {
            cout << "\"" << SA[1] << "\" not recognized" << endl;
            return;
        }
    }
    Solitaire H(T);

    string dir = "";
    string fullDir = "";
    string path = "";
    LPSECURITY_ATTRIBUTES attr;
    attr = NULL;

    CreateDirectory("Users", attr);
    CreateDirectory("Users/GUEST", attr);
    CreateDirectory("Users/pwd", attr);
    SetFileAttributes("Users/pwd", FILE_ATTRIBUTE_HIDDEN);

    int counter = 0;
    bool test = false;
    bool fail = true;

    std::ifstream inf;
    string passwordEncr = "";
    string password = "";

    while (fail) {
        while (!test && dir.compare("NEW")!=0
                && dir.compare("GUEST")!=0 && dir.compare("EXIT")) {
            if (counter != 0) {
                cout << endl << "Username not recognized, "
                << "try again" << endl;
                cout << "Or type \'GUEST\' or \'NEW\' or \'EXIT\'" << endl << endl;
            }
            dir = "";
            while (dir.length() == 0) {
                cout << "Please enter username: ";
                getline(cin, dir);
            }
            upperCase(dir);
            path = "Users/" + dir;
            counter++;
            test = directoryExists(path);
        }
        if (dir.compare("NEW")==0) {
            createAccount();
            return;
        } else if (dir.compare("GUEST")==0) {
            T->setUserName(dir);
            T->setFullUserName();
            T->setCompletePath(T->getFullUserName());
            T->setLocation("");
            cout << "LOGGED IN" << endl;
            return;
        } else if (dir.compare("EXIT")==0) {
            exit(1);
        }

        fullDir = "Users/pwd/" + dir + "_LOGIN.pvt";
        inf.open(fullDir.c_str());
        if (inf.fail()) {
            std::cerr << "\nError opening login file" << endl;
            test = false;
            dir = "";
        }
        fail = inf.fail();
    }
    getline(inf, passwordEncr);
    inf.close();
    H.setter(false, IA, passwordEncr);
    H.starter();
    password = H.getEncrypted();


    counter = 0;
    string guess = "";
    while (guess.compare(password) != 0) {
        if (counter != 0)
            cout << "WRONG try again or CTRL-C to quit" << endl;
        cout << "\nPlease enter password: ";
        getline(cin, guess);
        upperCase(guess);
        if (guess[guess.length()-1]=='X')
            guess = "";
        if (guess.length() % 5 != 0) {
            int remainder = 5 - (guess.length() % 5);
            for (int i = 0; i < remainder; i++)
                guess.append("X");
        }
        counter++;
    }
    cout << "LOGGED IN" << endl;
    T->setUserName(dir);
    T->setFullUserName();
    T->setCompletePath(T->getFullUserName());
    T->setLocation("");
}

bool UserLogin::directoryExists(string S) {
    if (S.length() == 0)
        return false;
    S = "./" + S;
    DIR *pDir;
    bool bExists = false;

    pDir = opendir(S.c_str());

    if (pDir != NULL) {
        bExists = true;
        (void) closedir(pDir);
    }
    return bExists;
}

void UserLogin::upperCase(string &S) {
    for (int i = 0; i < S.length(); i++)
        S[i] = toupper(S[i]);
}

bool UserLogin::allAlpha(string S) {
    for (int i = 0; i < S.length(); i++) {
        if (!isalpha(S[i]))
            return false;
    }
    return true;
}

void UserLogin::createAccount() {
    Solitaire H(T);
    string name = "";
    string fullPath = "";
    string password = "111";
    string passwordEncr = "";
    string path1 = "";
    int counter = 0;
    bool test = true;
    bool taken = false;
    while (test) {
        name = "";
        if (counter != 0) {
            cout << "\nUsername already taken\n" << endl;
            taken = true;
        }
        while (name.length() < 5) {
          if (!taken)
            cout << "Username must be at least five LETTERS OR NUMBERS\n" << endl;
          cout << "Please enter desired username: ";
          getline(cin, name);
          taken = false;
        }
        upperCase(name);
        path1 = "Users/" + name;
        test = directoryExists(path1);
        counter++;
    }
    cout << "\nUSERNAME AVAILABLE" << endl;
    while (password.length() < 5 || !allAlpha(password)) {
        cout << "Password must be at least FIVE LETTERS\n" << endl;
        cout << "Please enter password: ";
        getline(cin, password);
        string temp = password;
        upperCase(temp);
        if (temp[temp.length()-1]=='X') {
            password = "";
            std::cerr << "\nPassword cannot end with \'X\'" << endl;
        }
    }
    LPSECURITY_ATTRIBUTES attr;
    attr = NULL;
    CreateDirectory(path1.c_str(), attr);

    H.setter(true, IA, password);
    H.starter();
    passwordEncr = H.getEncrypted();
    fullPath = "Users/pwd/" + name + "_LOGIN.pvt";
    std::ofstream of(fullPath.c_str());
    if (of.fail()) {
        std::cerr << "Error creating login file" << endl;
        return;
    }
    of << passwordEncr << endl;
    of.close();
    SetFileAttributes(fullPath.c_str(), FILE_ATTRIBUTE_READONLY);
    cout << endl << "Now Login" << endl << endl;
    string temp[1];
    start(temp);
}

void UserLogin::changePassword() {
    if (T->getUserName().compare("GUEST")==0) {
        cout << "GUEST does not have a password" << endl;
        return;
    }
    Solitaire H(T);
    std::ifstream inf;
    std::ofstream outf;
    string fullPath = "";
    string oldPassword = "";
    string newPassword = "";
    string password = "";
    string passwordEncr = "";
    int counter = 0;

    fullPath = "Users/pwd/" + T->getUserName() + "_LOGIN.pvt";
    inf.open(fullPath.c_str());
    if (inf.fail()) {
        std::cerr << "Login file error" << endl;
        return;
    }
    getline(inf, passwordEncr);
    inf.close();

    H.setter(false, IA, passwordEncr);
    H.starter();
    password = H.getEncrypted();


    while (oldPassword.compare(password) != 0) {
        if (counter != 0)
            cout << "WRONG try again or CTRL-C to quit" << endl;
        cout << "\nPlease enter current password: ";
        getline(cin, oldPassword);
        upperCase(oldPassword);
        if (oldPassword[oldPassword.length()-1]=='X')
            oldPassword = "";
        if (oldPassword.length() % 5 != 0) {
            int remainder = 5 - (oldPassword.length() % 5);
            for (int i = 0; i < remainder; i++)
                oldPassword.append("X");
        }
        counter++;
    }
    while (newPassword.length() != 5 || !allAlpha(newPassword)) {
        cout << "Password must be FIVE LETTERS\n" << endl;
        cout << "Please enter new password: ";
        getline(cin, newPassword);
    }
    H.setter(true, IA, newPassword);
    H.starter();
    passwordEncr = H.getEncrypted();

    SetFileAttributes(fullPath.c_str(), FILE_ATTRIBUTE_NORMAL);

    outf.open(fullPath.c_str());
    outf << passwordEncr;
    outf << endl;
    outf.close();

    cout << "NEW PASSWORD SAVED" << endl;

    SetFileAttributes(fullPath.c_str(), FILE_ATTRIBUTE_READONLY);
}
