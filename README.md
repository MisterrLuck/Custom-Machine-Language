# Machine Language

This is a programming language based on the old machine languages before assembly languages existed. All commands are in hexadecimal format, and some have operands following the initial command.

## Table Of Contents

- [Usage](#usage)
- [Simplified Docs](#simplified-documentation)
    - [Opcodes](#opcodes)
- [Full Docs](#full-documentation)
    - [Opcodes](#opcodes-1)
    - [Registers](#registers)

## Usage

Compile main.cpp using your compiler of choice.

Run the program with your program as an argument.

```bash
./main countdown.txt
```

One example program is provided to you. It is located in the examples directory.

Refer to the documentation below to write your own programs.

> When using registers, you write the hexadecimal value and not the decimal value.

## Simplified Documentation

### Opcodes

| Name | Opcode |
|------|--------|
| NOP | 00 |
| ADD | 01 |
| SUB | 02 |
| NOT | 03 |
| AND | 04 |
| OR  | 05 |
| XOR | 06 |
| CLF | 07 |
| STC | 08 |
| DEC | 09 |
| INC | 0A |
| JMP | 0B |
| IN  | 0C |
| ROL | 0D |
| ROR | 0E |
| SAL | 0F |
| SAR | 10 |
| MOV | 11 |
| STI | 12 |
| JNZ | 13 |
| JWZ | 14 |
| JIE | 15 |
| JIG | 16 |
| JIL | 17 |
| OTH | 18 |
| OTD | 19 |
| OTA | 1B |
| RET | 1C |

## Full Documentation

### Opcodes

#### No Operands

| Name | Opcode | Description |
|------|--------|-------------|
| NOP  | 00 | does nothing for 50 milliseconds |
| ADD  | 01 | adds register 01h and 02h and outputs into 03h, carry goes into carry flag |
| SUB  | 02 | subtracts register 01h and 02h and outputs into 03h, negative goes into negative flag |
| NOT  | 03 | performs NOT operation on register 04h  and outputs to 06h |
| AND  | 04 | performs AND operation on register 04h and 05h and outputs to 06h |
| OR   | 05 | performs OR operation on register 04h and 05h and outputs to 06h |
| XOR  | 06 | performs XOR operation on register 04h and 05h and outputs to 06h |
| CLF  | 07 | clear carry flag |
| STC  | 08 | set carry flag |
| RET  | 1C | returns to location at 0C register |

#### Single Operand

| Name | Opcode | Description | Operand |
|------|--------|-------------|---------|
| DEC  | 09 | decrement register by 1 | register address |
| INC  | 0A | increment register by 1 | register address |
| JMP  | 0B | jump to command number. ALL JUMP COMMANDS SET REGISTER '0C' TO OLD LOCATION | location |
| IN   | 0C | get input as char, converts to int | register to store input |
| ROL  | 0D | rotate bits left | register |
| ROR  | 0E | rotate bits right | register |
| SAL  | 0F | shift left | register |
| SAR  | 10 | shift right | register |
| JNZ  | 13 | jump if register "0B" is not zero | jump location |
| JWZ  | 14 | jump if register "0B" is zero | jump location |
| OTH  | 18 | output as hexadecimal | register to output |
| OTD  | 19 | output as decimal | register to output |
| OTA  | 1B | output as ascii | register to output |

#### Double Operand

| Name | Opcode | Description | Operand 1 | Operand 2 | 
|------|--------|-------------|-----------|----------|
| MOV   | 11 | copy data from one place to another |  source register |  target register |
| STI   | 12 | store immediate |  target register |  immediate value |
| JIE   | 15 | jump if "0B" is equal to operand register value |  jump location |  register to compare |
| JIG   | 16 | jump if "0B" is greater than the operand register value |  jump location |  register to compare |
| JIL   | 17 | jump if "0B" is less than the operand register value |  jump location |  register to compare |


### Registers

| Opcode | Description |
|--------|-------------|
| 00 | constant 0 |
| 01 | input 1 for add and sub |
| 02 | input 2 for add and sub |
| 03 | output for add and sub |
| 04 | input 1 for all logic gates |
| 05 | input 2 for logic gates except NOT |
| 06 | output for all logic gates |
| 07 | carry flag |
| 08 | negative flag | 
| 09 | shift bit |
| 0A | program counter |
| 0B | jump register |
| 0C | return location |

### Storage Registers

- 0D
- ..
- ff
