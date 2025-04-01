#include "Instruction.h"
#include <bits/stdc++.h>
#include <string>
using namespace std;

// Function to convert R-type instructions
uint32_t convertRType(const string& opcode, const string& funct3, const string& funct7, int rd, int rs1, int rs2)
{
    int instruction = 0;
    instruction |= (stoi(funct7, 0, 16) << 25);  // funct7
    instruction |= (rs2 << 20);                  // rs2
    instruction |= (rs1 << 15);                  // rs1
    instruction |= (stoi(funct3, 0, 16) << 12);  // funct3
    instruction |= (rd << 7);                    // rd
    instruction |= stoi(opcode, 0, 16);          // opcode
    return instruction;
}

// Function to convert I-type instruction
uint32_t convertIType(const string& opcode, const string& funct3, int rd, int rs1, int imm )
{
    int instruction = 0;
    instruction |= (imm << 20);                       // imm
    instruction |= (rs1 << 15);                      // rs1
    instruction |= (stoi(funct3, 0, 16) << 12);      // funct3
    instruction |= (rd << 7);                       // rd
    instruction |= stoi(opcode, 0, 16);             // opcode

    return instruction;
}

// Function to convert B-type instruction
uint32_t convertBType(const string& opcode, const string& funct3, int rs1, int rs2, int imm)
{
        int instruction = 0;
        int imm1 = (imm & 0x1E) << 7;    
        int imm2 = (imm & 0x7E0) << 20;  
        int imm3 = (imm & 0x800) >> 4;  
        int imm4 = (imm & 0x1000) << 19;  
        instruction |= imm4 | (rs2 << 20) | (rs1 << 15) | (stoi(funct3, 0, 16) << 12) | imm2 | imm1 | imm3 | stoi(opcode, 0, 16);

        return instruction;
}

// Function to convert S-type instruction
uint32_t convertSType(const string& opcode, const string& funct3, int rs1, int rs2, int imm)
{
    int instruction = 0;
    int imm1 = (imm & 0x1F) << 7;
    int imm2 = (imm & 0xFE0) << 20;
    int funct = stoi(funct3, 0, 16);
    instruction |= imm2 | (rs2 << 20) | (rs1 << 15) | (funct << 12) | imm1 | stoi(opcode, 0, 16);

    return instruction;
}

// Function to convert U-type instruction
uint32_t convertUType(const string &opcode, int rd, int imm)
{
    int instruction = 0;
    int imm1 = imm << 12;
    instruction |= imm1 | (rd << 7) | stoi(opcode, 0, 16);

    return instruction;
}

// Function to convert J-type instruction
uint32_t convertJType(const string &opcode, int rd, int imm) {
    int instruction = 0;
    int imm1 = (imm & 0x7FE) << 20;    
    int imm2 = (imm & 0xFF000);        
    int imm3 = (imm & 0x800) << 9;    
    int imm4 = (imm & 0x100000) << 11;
    instruction |= imm4 | (rd << 7) | stoi(opcode, 0, 16) | imm1 | imm2 | imm3;

    return instruction;
}
