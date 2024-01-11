#include <iostream>
#include <fstream> // file opening and reading
#include <string> // strings
#include <algorithm> // to erase spaces and newlines from code // i think
#include <vector>
#include <cstdint> // for the 8 bit integers
#include <map> // for the lookup table
#include <iomanip> // hex to decimal
#include <sstream> // for isstringstream to convert hex to dec

#define ZERO 0x00
#define MATHINP1 0x01  // 01 - input 1 for add and sub
#define MATHINP2 0x02  // 02 - input 2 for add and sub
#define MATHOUT 0x03   // 03 - output for add and sub
#define LOGINP1 0x04   // 04 - input 1 for all logic gates
#define LOGINP2 0x05   // 05 - input 2 for logic gates except NOT
#define LOGOUT 0x06   // 06 - output for all logic gates
#define CARRYFLAG 0x07 // 07 - carry flag
#define NEGFLAG 0x08   // 08 - negative flag 
#define SHIFTBIT 0x09 // 09 - shift flag
#define PROGCOUNT 0x0A // 0A - program counter
#define JMPREG 0x0B    // 0B - jump register
using namespace std;

// declaring functions to define below main()
template <size_t N>
bool isInArr(int (&arr)[N], int val);
void printVec(vector<vector<string>> vec);
void runCode(vector<vector<string>> code);

struct Registers {
    // from 01 to 0A is settings registers. I dont know what difference this makes
    uint8_t reg[255] = {0};

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
} Register;

string line;
string code;
vector<vector<string>> formatCode;
ifstream exeFile;

// opcodes with 1 and 2 operands
int com1[] = {9, 10, 11, 12, 13, 14, 15, 16, 19, 20, 24, 25, 26, 27};
int com2[] = {17, 18, 21, 22, 23};

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
    // printVec(formatCode);
    runCode(formatCode);


    return 0;
}

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

void runCode(vector<vector<string>> code) {
    Register.reg[PROGCOUNT] = 0x00;
    for ( ; Register.reg[PROGCOUNT] < code.size(); Register.reg[PROGCOUNT]++) {
        int opcode;

        istringstream(code[Register.reg[PROGCOUNT]][0]) >> hex >> opcode;
        switch (opcode) {
            case 0x01:
            {// ADD
                int num1 = Register.reg[MATHINP1];
                int num2 = Register.reg[MATHINP2];
                int sum = (num1+num2);
                Register.reg[CARRYFLAG] = ((num1+num2)&0b100000000)>>8;
                Register.reg[MATHOUT] = sum;
            }break;
            // case 0x02: // SUB
            //     break;
            case 0x03:
            {// NOT
                int num = ~Register.reg[LOGINP1];
                Register.reg[LOGOUT] = num;
            }break;
            case 0x04:
            {// AND
                int num1 = Register.reg[LOGINP1];
                int num2 = Register.reg[LOGINP2];
                int out = num1 & num2;
                Register.reg[LOGOUT] = out;
            }break;
            case 0x05:
            {// OR
                int num1 = Register.reg[LOGINP1];
                int num2 = Register.reg[LOGINP2];
                int out = num1 | num2;
                Register.reg[LOGOUT, out];
            }break;
            case 0x06:
            {// XOR
                int num1 = Register.reg[LOGINP1];
                int num2 = Register.reg[LOGINP2];
                int out = num1 ^ num2;
                Register.reg[LOGOUT] = out;
            }break;
            case 0x07:
            {// CLF
                Register.reg[CARRYFLAG] = 0x00;
            }break;
            case 0x08:
            {// STC
                Register.reg[CARRYFLAG] = 0x01;
            }break;
            case 0x09:
            {// DEC
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                Register.reg[reg]--;
            }break;
            case 0x0A:
            {// INC
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                Register.reg[reg]++;
            }break;
            case 0x0B:
            {// JMP
                int location;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                Register.reg[PROGCOUNT] = location-1;
            }break;
            case 0x0C:
            // {//IN doesnt work

            //     int reg;
            //     istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
            //     char c;
            //     cout << dec;
            //     cin >> c;
            //     cout << "this wont print" << endl;
            //     Register.reg[reg] = c;
            // }
            case 0x0D:
            {// ROL
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                int num = Register.reg[reg];
                int shiftBit = (num & 0b10000000)>>7;
                num <<= 1;
                num |= shiftBit;
                Register.reg[reg] = num;
            }break;
            case 0x0E:
            {// ROR
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                int num = Register.reg[reg];
                int shiftBit = (num & 0b1)<<7;
                num >>= 1;
                num |= shiftBit;
                Register.reg[reg] = num;
            }break;
            case 0x0F:
            {// SAL
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                int num = Register.reg[reg];
                int shiftBit = (num & 0b10000000)>>7;
                Register.reg[SHIFTBIT] = shiftBit;
                num <<= 1;
                Register.reg[reg] = num;
            }break;
            case 0x10:
            {// SAR
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                int num = Register.reg[reg];
                int shiftBit = (num & 0b1);
                Register.reg[SHIFTBIT] = shiftBit;
                num >>= 1;
                Register.reg[reg] = num;
            }break;
            case 0x11:
            {// MOV
                int reg1, reg2;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg1;
                istringstream(code[Register.reg[PROGCOUNT]][2]) >> hex >> reg2;
                Register.reg[reg2] = Register.reg[reg1];
            }break;
            case 0x12:
            {// STI
                int reg, val;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                istringstream(code[Register.reg[PROGCOUNT]][2]) >> hex >> val;
                Register.reg[reg] = val;
            }break;
            case 0x13:
            {//JNZ
                int location;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                if (Register.reg[JMPREG] != 0) {
                    Register.reg[PROGCOUNT] = location-1;
                }
            }break;
            case 0x14:
            {//JWZ
                int location;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                if (Register.reg[JMPREG] == 0) {
                    Register.reg[PROGCOUNT] = location-1;
                }
            }break;
            case 0x15:
            {//JIE
                int location, reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                istringstream(code[Register.reg[PROGCOUNT]][2]) >> hex >> reg;
                if (Register.reg[JMPREG] == Register.reg[reg]) {
                    Register.reg[PROGCOUNT] = location-1;
                }
            }break;
            case 0x16:
            {//JIG
                int location, reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                istringstream(code[Register.reg[PROGCOUNT]][2]) >> hex >> reg;
                if (Register.reg[JMPREG] > Register.reg[reg]) {
                    Register.reg[PROGCOUNT] = location-1;
                }
            }break;
            case 0x17:
            {//JIL
                int location, reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> location;
                istringstream(code[Register.reg[PROGCOUNT]][2]) >> hex >> reg;
                if (Register.reg[JMPREG] < Register.reg[reg]) {
                    Register.reg[PROGCOUNT] = location-1;
                }
            }break;
            case 0x18:
            {// OTH
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                cout << hex << int(Register.reg[reg]) << dec << endl;
            }break;
            case 0x19:
            {// OTD
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                cout << int(Register.reg[reg]) << endl;
            }break; 

            case 0x1B:
            {// OTA
                int reg;
                istringstream(code[Register.reg[PROGCOUNT]][1]) >> hex >> reg;
                cout << char(Register.reg[reg]) << endl;
            }break;
        }
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
// ADD - 01 - adds register 01h and 02h and outputs into 03h, carry goes into carry flag
// SUB - 02 - subtracts register 01h and 02h and outputs into 03h, negative goes into negative flag
// NOT - 03 - performs NOT operation on register 04h  and outputs to 06h
// AND - 04 - performs AND operation on register 04h and 05h and outputs to 06h
// OR  - 05 - performs OR operation on register 04h and 05h and outputs to 06h
// XOR - 06 - performs XOR operation on register 04h and 05h and outputs to 06h
// CLF - 07 - clear carry flag
// STC - 08 - set carry flag
// DEC - 09 - decrement register by 1 - OPERAND: register address
// INC - 0A - increment register by 1 - OPERAND: register address
// JMP - 0B - jump to command number - OPERAND: location
// IN  - 0C - get input as char, converts to int. warning for overflow - OPERAND: register to store input
// ROL - 0D - rotate bits left - OPERAND: register
// ROR - 0E - rotate bits right - OPERAND: register
// SAL - 0F - shift left - OPERAND: register
// SAR - 10 - shift right - OPERAND: register
// MOV - 11 - copy data from one place to another - OPERAND 1: source register - OPERAND 2: target register
// STI - 12 - store immediate - OPERAND 1: target register - OPERAND 2: immediate value
// JNZ - 13 - jump if register "0B" is not zero - OPERAND: jump location
// JWZ - 14 - jump if register "0B" is zero - OPERAND: jump location
// JIE - 15 - jump if "0B" is equal to operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
// JIG - 16 - jump if "0B" is greater than the operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
// JIL - 17 - jump if "0B" is less than the operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
// OTH - 18 - output as hexadecimal - OPERAND: register to output
// OTD - 19 - output as decimal - OPERAND: register to output
// OTB - 1A - output as binary - OPERAND: register to output
// OTA - 1B - output as ascii - OPERAND: register to output

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
// 0B - jump register

// Storage registers

// 0B
// ..
// ff
