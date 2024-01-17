# Machine Language
This is a programming language based on the old machine languages before assembly languages existed. All commands are in hexadecimal format, and some have operands following the initial command.

>When using registers, you write the hexadecimal value and not the decimal value.

- [Simplified Docs](#simplified-documentation)
- - [Opcodes](#opcodes)
- [Full Docs](#full-documentation)
- - [Opcodes](#opcodes-1)
- - [Registers](#registers)


## Simplified Documentation
### Opcodes
- NOP - 00
- ADD - 01
- SUB - 02
- NOT - 03
- AND - 04
- OR  - 05
- XOR - 06
- CLF - 07
- STC - 08
- DEC - 09
- INC - 0A
- JMP - 0B
- IN  - 0C
- ROL - 0D
- ROR - 0E
- SAL - 0F
- SAR - 10
- MOV - 11
- STI - 12
- JNZ - 13
- JWZ - 14
- JIE - 15
- JIG - 16
- JIL - 17
- OTH - 18
- OTD - 19
- OTB - 1A
- OTA - 1B
- RET - 1C

## Full Documentation
### Opcodes
- NOP - 00 - does nothing for 50 milliseconds
- ADD - 01 - adds register 01h and 02h and outputs into 03h, carry goes into carry flag
- SUB - 02 - subtracts register 01h and 02h and outputs into 03h, negative goes into negative flag
- NOT - 03 - performs NOT operation on register 04h  and outputs to 06h
- AND - 04 - performs AND operation on register 04h and 05h and outputs to 06h
- OR  - 05 - performs OR operation on register 04h and 05h and outputs to 06h
- XOR - 06 - performs XOR operation on register 04h and 05h and outputs to 06h
- CLF - 07 - clear carry flag
- STC - 08 - set carry flag
- DEC - 09 - decrement register by 1 - OPERAND: register address
- INC - 0A - increment register by 1 - OPERAND: register address
- JMP - 0B - jump to command number. ALL JUMP COMMANDS SET REGISTER '0C' TO OLD LOCATION- OPERAND: location
- IN  - 0C - get input as char, converts to int - OPERAND: register to store input
- ROL - 0D - rotate bits left - OPERAND: register
- ROR - 0E - rotate bits right - OPERAND: register
- SAL - 0F - shift left - OPERAND: register
- SAR - 10 - shift right - OPERAND: register
- MOV - 11 - copy data from one place to another - OPERAND 1: source register - OPERAND 2: target register
- STI - 12 - store immediate - OPERAND 1: target register - OPERAND 2: immediate value
- JNZ - 13 - jump if register "0B" is not zero - OPERAND: jump location
- JWZ - 14 - jump if register "0B" is zero - OPERAND: jump location
- JIE - 15 - jump if "0B" is equal to operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
- JIG - 16 - jump if "0B" is greater than the operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
- JIL - 17 - jump if "0B" is less than the operand register value - OPERAND 1: jump location - OPERAND 2: register to compare
- OTH - 18 - output as hexadecimal - OPERAND: register to output
- OTD - 19 - output as decimal - OPERAND: register to output
- OTB - 1A - output as binary - OPERAND: register to output
- OTA - 1B - output as ascii - OPERAND: register to output
- RET - 1C - returns to location at 0C register

### Registers
- 00 - constant 0
- 01 - input 1 for add and sub
- 02 - input 2 for add and sub
- 03 - output for add and sub
- 04 - input 1 for all logic gates
- 05 - input 2 for logic gates except NOT
- 06 - output for all logic gates
- 07 - carry flag
- 08 - negative flag 
- 09 - shift bit
- 0A - program counter
- 0B - jump register
- 0C - return loction

### Storage Registers
- 0D
- ..
- ff
