/*
 * Terminal Program
 *
 * @author Jayden Navarro
 * Date: 6/7/2012
 */

#ifndef STANDARDKEYWORDS_H
#define STANDARDKEYWORDS_H
#include "Terminal.h"

using std::string;

class StandardKeywords {
    public:
        StandardKeywords(Terminal *TO) {T = TO;}
        void start(string SA[]);
    private:
        Terminal *T;
        static int IA[28];
        void upperCase(string &S);
        void cat(string filename="");
        void tac(string filename="");
        void write(string filename="");
        void deleteAccount();
        void deleteFileFolder(string filename="");
        bool IsDirectory(const char path[]);
        bool RemoveDirectory(string path);
        void list(string filename="");
        void makeFolder(string foldername="");
        void help(string command="");
        void changeFolder(string foldername="");
        bool cfDot(string foldername="");
        void ridSlash(string &S);
        void parsePath(string &S, int position=0);
        bool move(string file1="", string file2="");
        bool copy(string file1="", string file2="");
        void location();
};

#endif
