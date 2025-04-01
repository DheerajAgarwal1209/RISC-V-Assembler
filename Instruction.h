#ifndef RISC_V_INSTRUCTION_H
#define RISC_V_INSTRUCTION_H

#include<bits/stdc++.h>
#include <string>
#include <unordered_map>
using namespace std;

// helping functions
void Parse(vector<string> program);
string trim(const string &str);

// Function declarations
uint32_t convertRType(const string& opcode, const string& funct3, const string& funct7, int rd, int rs1, int rs2);
uint32_t convertIType(const string& opcode, const string& funct3, int rd, int rs1, int imm);
uint32_t convertBType(const string& opcode, const string& funct3, int rs1, int rs2, int imm);
uint32_t convertSType(const string& opcode, const string& funct3, int rs1, int rs2, int imm);
uint32_t convertJType(const string& opcode, int rd, int imm);
uint32_t convertUType(const string& opcode, int rd, int imm);

// Register alias to register number map
extern unordered_map<string, int> registerMap;
extern unordered_map<string, int> labelAddress;

#endif // INSTRUCTION_H




