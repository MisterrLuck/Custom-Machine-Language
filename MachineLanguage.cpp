#include <iostream>
#include <fstream> // file opening and reading
#include <string> // strings
#include <algorithm> // to erase spaces and newlines from code // i think
#include <vector>
#include <cstdint> // for the 8 bit integers
#include <map> // for the lookup table
#include <iomanip> // hex to decimal
#include <sstream> // for isstringstream to convert hex to dec

#define carryFlag 7
#define negFlag 8
#define shiftBit 9
#define progCount 10
using namespace std;

// declaring structs and functions to define below main()
struct Registers;
template <size_t N>
bool isInArr(int (&arr)[N], int val);
void printVec(vector<vector<string>> vec);

string line;
string code;
vector<vector<string>> formatCode;
ifstream exeFile;

// opcodes with 1 and 2 operands
int com1[] = {9, 10, 11, 12, 13, 14, 15, 16};
int com2[] = {17, 18};

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

    // goes through every pair of opcodes. 
    for (int i = 0; i < code.size()/2; i++) {
        int pos = i*2;
        vector<string> currCommand;
        string hexStr;
        // sets hexStr to the current hexcode
        hexStr += code[pos];
        hexStr += code[pos+1];
        // pushes to the current command vector
        currCommand.push_back(hexStr);

        int comDec;
        // gets opcode for command in decimal and looks up number of operands
        istringstream(hexStr) >> hex >> comDec;
        // one operand, pushes to after the opcode
        if (isInArr(com1, comDec)) {
            i++;
            pos = i*2;
            hexStr = code[pos];
            hexStr += code[pos+1];
            currCommand.push_back(hexStr);
        }
        // two operands, pushes both to after the opcode
        else if (isInArr(com2, comDec)) {
            for (int j = 0; j < 2; j++) {
                i++;
                pos = i*2;
                hexStr = code[pos];
                hexStr += code[pos+1];
                currCommand.push_back(hexStr);
            }
        }
        // pushes current command to the overall formatted code
        formatCode.push_back(currCommand);
    }

    // prints out formatted code for debugging
    printVec(formatCode);

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


template <size_t N>
bool isInArr(int (&arr)[N], int val) {
    for (int element : arr) {
        if (element == val) {
            return true;
        }
    }
    return false;
}

void printVec(vector<vector<string>> vec) {
    for (auto &row : vec) {
        for (auto &column : row) {
            cout << column << " ";
        }
        cout << endl;
    }
}

// run commands

// .\MachineLanguage.exe test.mll


// git commands

// git add --all -- :!.vscode
// git commit -m ""


// Opcodes

// HEXADECIMAL is the normal state

// NOP - 00 - does nothing
// ADD - 01 -  adds register 01h and 02h and outputs into 03h, carry goes into register
// SUB - 02 - subtracts register 01h and 02h and outputs into 03h, negative
// NOT - 03 - performs NOT operation on register 04h  and outputs to 06h
// AND - 04 - performs AND operation on register 04h and 05h and outputs to 06h
// OR  - 05 - performs AND operation on register 04h and 05h and outputs to 06h
// XOR - 06 - performs AND operation on register 04h and 05h and outputs to 06h
// CLF - 07 - clear carry flag
// STC - 08 - set carry flag
// DEC - 09 - decrement register by 1 - OPERAND: register address
// INC - 0A - increment register by 1 - OPERAND: register address
// JMP - 0B - jump to command number - OPERAND: location
// IN  - 0C - get input, as char, converts to hex. warning for overflow - OPERAND: register to store input
// ROL - 0D - rotate bits left - OPERAND: register
// ROR - 0E - rotate bits right - OPERAND: register
// SAL - 0F - shift left - OPERAND: register
// SAR - 10 - shift right - OPERAND: register
// MOV - 11 - copy data from one place to another - OPERAND 1: source register - OPERAND 2: target register
// STI - 12 - store immediate - OPERAND 1: target register - OPERAND 2: immediate value

// Jcc - jump if condition - library of jump conditions
// OUT - output as hex, decimal, binary, or ascii - different commands

// Registers

// Register settings - i dont know another name for this
// 00 - constant 0
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
