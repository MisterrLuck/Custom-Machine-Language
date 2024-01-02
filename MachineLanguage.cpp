#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

string line;
string code;
string formatCode;
ifstream exeFile;

int main(int argc, char *argv[]) {
    // Error checking - has to have an argument
    if (argc != 2) {cout << "Has to have an argument";return -1;}

    // Opening and reading the file
    exeFile.open(argv[1]);
    // did the file succesfully open?
    if (exeFile.is_open()) {
        // while there are still lines
        while (getline(exeFile, line)) {
            code = code.append(line);
        }
        exeFile.close();
    } else {cout << "file didn't open properly";return -1;}

    // Formatting
    // remove all spacing
    code.erase(remove(code.begin(), code.end(), ' '), code.end());
    // only have hexadecimal characters
    bool notHex = code.find_first_not_of("1234567890abcdefABCDEF") != string::npos;
    if (notHex) {cout << "you should only have hexadecimal characters";return -1;}

    cout << code;
    return 0;
}

// 32 * (32bit register)
// register $0 is hardwired to zero and writes to it are discarded
// register $31 is the link register

// run commands

// .\MachineLanguage.exe test.mll


// git commands

// git add --all -- :!.vscode
// git commit -m ""