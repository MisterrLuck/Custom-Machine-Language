#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdint> // for the 8 bit integers
using namespace std;

string line;
string code;
vector<vector<string>> formatCode;
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

    for (int i = 0; i < code.size()/2; i++) {
        int pos = i*2;

    }

    cout << code;
    return 0;
}

struct Registers {
    // from 01 to 0A is settings registers. I dont know what difference this makes
    uint8_t reg[255];

    void setReg(int regInd, uint8_t val) {
        reg[regInd] = val;
    }
    uint8_t getReg(int regInd) {
        return reg[regInd];
    }
    void copMem(int regInd1, int regInd2) {
        // value from regInd1 copied into regInd2
        setReg(regInd2, getReg(regInd1));
    }
};

// run commands

// .\MachineLanguage.exe test.mll


// git commands

// git add --all -- :!.vscode
// git commit -m ""


// Opcodes

// HEXADECIMAL is the normal state

// NOP - does nothing
// ADD - adds register 01h and 02h and outputs into 03h, carry goes into register
// SUB - subtracts register 01h and 02h and outputs into 03h, negative
// log NOT - performs NOT operation on register 04h  and outputs to 06h
// log AND - performs AND operation on register 04h and 05h and outputs to 06h
// log OR - performs AND operation on register 04h and 05h and outputs to 06h
// log XOR - performs AND operation on register 04h and 05h and outputs to 06h
// CLF - clear carry flag
// STC - set carry flag
// DEC - decrement register by 1 - OPERAND: register address
// INC - increment register by 1 - OPERAND: register address
// JMP - jump to command number - OPERAND: location
// MOV - copy data from one place to another - OPERAND 1: beginning register - OPERAND 2: target register
// STI - store immediate - OPERAND 1: target register - OPERAND 2: immediate value
// IN  - get input, as char, converts to hex. warning for overflow - OPERAND: register to store input
// ROL - rotate bits left - OPERAND: register
// ROR - rotate bits right - OPERAND: register
// SAL - shift left - OPERAND: register
// SAR - shift right - OPERAND: register

// Jcc - jump if condition - library of jump conditions
// OUT - output as hex, decimal, binary, or ascii - different commands

// Registers

// Register settings - i dont know another name for this
// 01 - input 1 for add and sub
// 02 - input 2 for add and sub
// 03 - output for add and sub
// 04 - input 1 for all logic gates
// 05 - input 2 for logic gates except NOT
// 06 - output for all logic gates
// 07 - carry flag
// 08 - negative flag 
// 09 - shift bit
// 0A - program counter

// Storage registers

// 0B
// ..
// ff
