#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdint> // for the 8 bit integers
using namespace std;

string line;
string code;
vector<string> formatCode;
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
    // make sure file length is divisible by 2
    if (code.size()%2 != 0) {cout << "incorrect number of characters";return -1;}

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


// Opcodes

// 0 OPERANDS:

// NOP - 00h - does nothing
// ADD - 01h - adds register 1 and 2 and outputs into 3, carry goes into register
// SUB
// log AND
// log NOT
// log OR
// log XOR
// CLF - clear carry flag
// STC - set carry flag
// DEC - decrement
// INC - increment
// Jcc - jump if condition - library of jump conditions
// JMP
// MOV - copy data from one place to another
// STI - store immediate
// IN  - get input, convert to hex. warning for overflow
// OUT - output as hex, decimal, binary, or ascii - different commands
// ROL - rotate bits left
// ROR - rotate bits right
// SAL - shift left
// SAR - shift right


// Registers

// 01 - 
// 02 - 
// 03 - 
// 04 - carry flag - may move somewhere else
// 05 - program counter
// 06
// 07
// 08
// 09
// 0A
// 0B
// 0C
// 0D
// 0E
// 0F
// 10

// storage registers
// 11
// ..
// 20
