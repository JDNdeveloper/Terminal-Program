/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <windows.h>
#include <string>
#include "StandardKeywords.h"
#include "Solitaire.h"

using std::string;
using std::endl;
using std::cout;
using std::cin;


int StandardKeywords::IA[28] =
    {16, 10, 14, 3, 6, 22, 11, 7, 26, 9, 5, 19,
    18, 27, 17, 3, 25, 28, 13, 20, 1, 15, 2, 12, 23, 21, 4, 24};

void StandardKeywords::start(string SA[]) {
    if (SA[0].compare("CAT")==0)
        cat(SA[1]);
    else if (SA[0].compare("TAC")==0)
        tac(SA[1]);
    else if (SA[0].compare("WRITE")==0)
        write(SA[1]);
    else if (SA[0].compare("DELETE")==0) {
        upperCase(SA[1]);
        if (SA[1].compare("ACCOUNT")==0)
            deleteAccount();
        else
            deleteFileFolder(SA[1]);
    }
    else if (SA[0].compare("LIST")==0)
        list(SA[1]);
    else if (SA[0].compare("FOLDER")==0)
        makeFolder(SA[1]);
    else if (SA[0].compare("HELP")==0)
        help(SA[1]);
    else if (SA[0].compare("CF")==0)
        changeFolder(SA[1]);
    else if (SA[0].compare("MOVE")==0)
        move(SA[1], SA[2]);
    else if (SA[0].compare("COPY")==0)
        copy(SA[1], SA[2]);
    else if (SA[0].compare("LOCATION")==0)
        location();
}

void StandardKeywords::upperCase(string &S) {
    for (int i = 0; i < S.length(); i++)
        S[i] = toupper(S[i]);
}

void StandardKeywords::cat(string filename) {
    string fullPath = T->getCompletePath() + "/" + filename;

    std::ifstream inf;
    inf.open(fullPath.c_str());
    while (inf.fail()) {
        std::cerr << "Error opening file: " << filename << endl;
        return;
    }
    string input = "";
    while(getline(inf, input))
        cout << input << endl;
    inf.close();
}

void StandardKeywords::tac(string filename) {
    string fullPath = T->getCompletePath() + "/" + filename;

    std::ifstream inf;
    inf.open(fullPath.c_str());
    while (inf.fail()) {
        std::cerr << "Error opening file: " << filename << endl;
        return;
    }
    string input = "";
    std::vector<string> V1;
    while(getline(inf, input)) {
        V1.push_back(input);
    }
    for (int i = (V1.size()-1); i >= 0; i--)
        cout << V1[i] << endl;
    inf.close();
}

void StandardKeywords::write(string filename) {
    string fullPath = "";
    std::ofstream outf;
    string message = "1";

    if (filename.length()==0) {
        cout << "Please enter a filename to write to: ";
        getline(cin, filename);
    }
    string temp = filename;
    upperCase(temp);
    if (temp.compare("BACK")==0) {
        std::cerr << "BACK cannot be used as filename" << endl;
        return;
    }
    fullPath = T->getCompletePath() + "/" + filename;
    outf.open(fullPath.c_str());
    if (outf.fail()) {
        std::cerr << "Error opening file: " << filename << endl;
        return;
    }
    cout << "Start typing in text, press ENTER twice when done" << endl;
    getline(cin, message);
    while (message.length() != 0) {
        outf << message << "\r\n";
        getline(cin, message);
    }
    outf.close();
    cout << "SAVED" << endl;
}

bool StandardKeywords::IsDirectory(const char path[]) {
    DWORD dwAttrib = GetFileAttributes(path);

    return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
            (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool StandardKeywords::RemoveDirectory(string path) {
    if (path[path.length()-1] != '\\') path += "\\";
    // first off, we need to create a pointer to a directory
    DIR *pdir = NULL; // remember, it's good practice to initialise a pointer to NULL!
    pdir = opendir (path.c_str());
    struct dirent *pent = NULL;
    if (pdir == NULL) { // if pdir wasn't initialised correctly
        return false; // return false to say "we couldn't do it"
    } // end if
    char file[256];

    int counter = 1; // use this to skip the first TWO which cause an infinite loop (and eventually, stack overflow)
    while (pent = readdir (pdir)) { // while there is still something in the directory to list
        if (counter > 2) {
            for (int i = 0; i < 256; i++) file[i] = '\0';
            strcat(file, path.c_str());
            if (pent == NULL) { // if pent has not been initialised correctly
                return false; // we couldn't do it
            } // otherwise, it was initialised correctly, so let's delete the file~
            strcat(file, pent->d_name); // concatenate the strings to get the complete path
            remove(file);
            if (IsDirectory(file) == true)
                RemoveDirectory(file);
        } counter++;
    }

    // finally, let's clean up
    closedir (pdir); // close the directory
    if (!rmdir(path.c_str())) return false; // delete the directory
    return true;
}

void StandardKeywords::deleteAccount() {
    string fullPath = T->getUserName();
    string loginPath = "Users/pwd/" + T->getUserName() + "_LOGIN.pvt";
    std::ifstream inf;
    string passwordEncr = "";
    string password = "";
    int counter = 0;

    if (fullPath.compare("GUEST")==0) {
        cout << "\nGUEST account cannot be deleted\n" << endl;
        return;
    }
    fullPath = "Users/" + fullPath;

    string answer = "";

    Solitaire H(T);
    inf.open(loginPath.c_str());
    if (inf.fail()) {
        std::cerr << "Login file error" << endl;
        return;
    }
    getline(inf, passwordEncr);
    inf.close();

    H.setter(false, IA, passwordEncr);
    H.starter();
    password = H.getEncrypted();

    while (answer.compare(password) != 0) {
        if (counter != 0)
            cout << "WRONG try again or CTRL-C to quit" << endl;
        cout << "\nPlease enter password to delete account: ";
        getline(cin, answer);
        upperCase(answer);
        if (answer[answer.length()-1]=='X')
            answer = "";
        if (answer.length() % 5 != 0) {
            int remainder = 5 - (answer.length() % 5);
            for (int i = 0; i < remainder; i++)
                answer.append("X");
        }
        counter++;
    }


    RemoveDirectory(fullPath);
    remove(loginPath.c_str());
    cout << "\nACCOUNT DELETED" << endl;
    T->setUserName("GUEST");
    T->setFullUserName();
    T->setCompletePath(T->getFullUserName());
    T->setLocation("");
}

void StandardKeywords::deleteFileFolder(string filename) {
    string string1 = filename;
    int success1 = -1;
    bool success2 = false;
    upperCase(string1);
    if (string1.compare("LOGIN.PVT")==0) {
        cout << "Cannot delete LOGIN.pvt" << endl;
        return;
    }
    filename = "./" + T->getCompletePath() + "/" + filename;
    success1 = remove(filename.c_str());
    if (IsDirectory(filename.c_str()))
        success2 = RemoveDirectory(filename);
}

void StandardKeywords::list(string filename) {
    string fullPath = "";
    if (filename.length() == 0)
        fullPath = T->getCompletePath();
    else
        fullPath = T->getCompletePath() + "/" + filename;
    DIR *dir;
    struct dirent *ent;
        dir = opendir (fullPath.c_str());
    if (dir != NULL) {

      /* print all the files and directories within directory */
      int counter = 0;
      while ((ent = readdir (dir)) != NULL) {
        if (counter > 1)
            printf ("%s\n", ent->d_name);
        counter++;
      }
      if (counter == 2)
        cout << "No files or folders" << endl;
      closedir (dir);
    } else {
      std::cerr << "Could not open folder: " << filename << endl;
      return;
    }
}

void StandardKeywords::makeFolder(string foldername) {
    if (foldername.length() == 0)
        return;
    string temp = foldername;
    upperCase(temp);
    if (temp.compare("BACK")==0) {
        std::cerr << "BACK cannot be used as foldername" << endl;
        return;
    }
    for (int i = 0; i < foldername.length(); i++) {
        if (foldername[i] == '.') {
            std::cerr << "Cannot create folder with '.' in the name" << endl;
            return;
        }
    }
    string pathName = T->getCompletePath() + "/" + foldername;

    LPSECURITY_ATTRIBUTES attr;
    attr = NULL;

    if (CreateDirectory(pathName.c_str(), attr)==0)
        std::cerr << "Error creating folder" << endl;
}

void StandardKeywords::help(string command) {
    upperCase(command);
    if (command.length()==0) {
        cout << "\nWelcome to Terminal version 1.2" << endl;
        cout << "Coded by Jayden Navarro - 6/7/12" << endl;
        cout << "---------------------------------------" << endl;
        cout << "This is a command prompt environment" << endl;
        cout << "with games and minimal file management" << endl;
        cout << "or complexity." << endl;
        cout << "---------------------------------------" << endl;
        cout << "Type HELP KEYWORDS for list of keywords\n" << endl;
    } else if (command.compare("KEYWORDS")==0) {
        cout << "\n    KEYWORDS:" << endl;
        cout << "------------------" << endl;
        cout << "\"HELP or + KEYWORDS\": Brings up program info or this page" << endl;
        cout << "\"CAT + filename\": Reads text files" << endl;
        cout << "\"TAC + filename\": Reads text files in reverse order" << endl;
        cout << "\"ENCRYPT\": Allows you to encrypt information" << endl;
        cout << "\"DECRYPT\": Allows you to decrypt information" << endl;
        cout << "\"LOGIN\": Let's you relogin" << endl;
        cout << "\"CHANGE PASSWORD\": Allows you to change your password" << endl;
        cout << "\"WRITE + filename\": Allows you to write to a file" << endl;
        cout << "\"FOLDER + foldername\": Creates a folder" << endl;
        cout << "\"LIST or + foldername\": Lists all files and folders" << endl;
        cout << "\"CF + HOME or BACK or foldername\": Changes folder location" << endl;
        cout << "\"LOCATION\": Prints out current location" << endl;
        cout << "\"DELETE + filename/foldername\": Deletes a file/folder" << endl;
        cout << "\"DELETE ACCOUNT\": Deletes account" << endl;
        cout << "\"EXIT or LOGOUT\": Closes program and logs you out" << endl;
        cout << "\"COPY + filename + filename\": Copies first file to second" << endl;
        cout << "\"MOVE + filename + filename\": Moves first file to second" << endl;
        cout << "\"FV\": Calculates future value" << endl;
        cout << "\"SCRAMBLE\": Scrambles text for fun" << endl;
        cout << "\"CINCO\": Plays the game Cinco\n" << endl;
    } else
        cout << "Command not recognized" << endl;
}

void StandardKeywords::changeFolder(string filename) {
    string fullPath = "";
    string temp = filename;
    upperCase(temp);
    if (filename.length()==0) {
        std::cerr << "No folder specified" << endl;
        return;
    } else if (temp.compare("HOME")==0) {
        T->setCompletePath(T->getFullUserName());
        T->setLocation("");
        return;
    }
    fullPath = T->getCompletePath() + "/" + filename;
    if (cfDot(filename))
        return;
    ridSlash(fullPath);
    ridSlash(filename);
    parsePath(filename, 1);
    if (temp.compare("BACK")==0) {
        fullPath = T->getCompletePath() + "/..";
        if (T->getCompletePath().compare(T->getFullUserName())==0) {
            std::cerr << "LOCATION RESTRICTED" << endl;
            return;
        } else {
            ridSlash(fullPath);
            filename = fullPath;
            parsePath(filename, 1);
            parsePath(filename, 2);
            parsePath(fullPath, 2);
            if (filename.compare(T->getUserName())==0) {
                T->setCompletePath(T->getFullUserName());
                T->setLocation("");
                return;
            }
        }
    }
    if (cfDot(filename))
        return;
    if (IsDirectory(fullPath.c_str())) {
        T->setCompletePath(fullPath);
        T->setLocation(filename);
    } else {
        std::cerr << "Not a valid folder" << endl;
        return;
    }
}

bool StandardKeywords::cfDot(string file) {
    int nextTo = 0;
    int single = 0;
    if (file.length() > 1) {
        for (int i = 1; i < file.length(); i++) {
            if (file[i] == '.' && file[i-1] == '.')
                nextTo++;
            if (file[i] == '.' && file[i-1] != '.')
                single++;
            if ((file[i] == '/' || file[i] == '\\')
                && (file[i-1] == '/' || file[i-1] == '\\'))
                nextTo++;
        }
    } else if (file[0] == '.') {
        single = 1;
    }
    if (single != 0 && nextTo == 0)
        return true;
    else if (nextTo != 0) {
        std::cerr << "Invalid location" << endl;
        return true;
    } else {
        return false;
    }
}

void StandardKeywords::ridSlash(string &S) {
    string temp = S;
    int length = S.length();
    for (int i = length-1; i > 0; i--) {
        if (temp[i] == '\\')
            S[i] = '/';
        if (temp[i-1] == '\\') {
            S[i-1] = '/';
        }
    }
    temp = S;
    for (int i = 0; i < length; i++) {
        if (temp[i] == '/' && temp[i-1] == '/')
            S.erase(i-1, 1);
    }
    if (S[S.length()-1] == '/')
        S.erase(S.length()-1, 1);
}

void StandardKeywords::parsePath(string &S, int position) {
    int slashes = 0;
    int counter = 0;
    string temp = S;
    int length = temp.length();
    int j = 0;
    if (position == 1) {
        for (int i = 0; i < length; i++) {
            if ((S[i] == '/' || S[i] == '\\')
                    && i != (length-1))
                slashes++;
        }
        if ((temp[length-1] == '/' || temp[length-1] == '\\')
                && temp[length-2] == '.'
                && temp[length-3] == '.') {
            counter = 3;
        }
        if (temp[length-1] == '.' && temp[length-2] == '.'
                && (temp[length-3] == '/'
                || temp[length-3] == '\\')) {
            counter = 2;
        }
        while (counter < slashes) {
            if ((temp[j] == '/' || temp[j] == '\\')
                    && j != (length-1))
                counter++;
            S.erase(0, 1);
            j++;
        }
    } else if (position == 2) {
        if (temp[length-1] == '\\' || temp[length-1] == '/') {
            S.erase(length-4, 4);
        } else {
            S.erase(length-3, 3);
        }

        length = S.length();
        for (int i = 0; i < length; i++) {
            if ((S[i] == '/' || S[i] == '\\')
                    && i != (length-1))
                slashes++;
        }

        if (slashes > 0) {
            j = S.length()-1;
            while (counter < 1) {
                if (temp[j] == '/' || temp[j] == '\\')
                    counter++;
                S.erase(S.length()-1, 1);
                j--;
            }
        }
    }
}

bool StandardKeywords::move(string file1, string file2) {
    string temp1 = file1;
    string temp2 = file2;
    if (copy(temp1, temp2)) {
        temp1 = T->getCompletePath() + "/" + temp1;
        if (remove(temp1.c_str())==0)
            return true;
    }
    return false;
}

bool StandardKeywords::copy(string file1, string file2) {
    string temp = "";
    if (file1.length()==0 || file2.length()==0) {
        std::cerr << "No file names given" << endl;
        return false;
    }
    file1 = T->getCompletePath() + "/" + file1;
    file2 = T->getCompletePath() + "/" + file2;
    std::ifstream inf(file1.c_str());
    std::ofstream outf(file2.c_str());
    if (inf.fail() || outf.fail()) {
        std::cerr << "Could not open files" << endl;
        return false;
    }
    while (getline(inf, temp)) {
        outf << temp << "\r\n";
    }
    inf.close();
    outf.close();
    return true;
}

void StandardKeywords::location() {
    string temp = T->getCompletePath();
    temp.erase(0, 5);
    cout << temp << endl;
}
