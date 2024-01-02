#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string code;
int i = 0;
ifstream exeFile;

int main(int argc, char *argv[]) {
    // Error checking
    if (argc != 2) {
        return -1;
    }

    // Opening and reading the file
    exeFile.open(argv[1]);
    // did the file succesfully open
    if (exeFile.is_open()) {
        // while there are still lines
        while (getline(exeFile, code)) {

       }

    }

    // printing maybe
    for ( ; i < 8; i++) {
        cout << code[i] << endl;
    }
    return 0;
}

// 32 * (32bit register)
// register $0 is hardwired to zero and writes to it are discarded
// register $31 is the link register

// git commands

// git add --all -- :!.vscode
// git commit -m ""