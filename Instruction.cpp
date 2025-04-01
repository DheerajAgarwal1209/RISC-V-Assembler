#include<bits/stdc++.h>
#include "Instruction.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void Parse(vector<string> program){
    ofstream outfile("output.hex");
     for (unsigned int i = 0; i < program.size(); i++)
    {  
        string line = program[i];
        size_t colonPos = line.find(':');
   
        if (colonPos != string::npos) {
            // Skip the label and get the rest of the line
            string restOfLine = line.substr(colonPos + 1);
            line = restOfLine;  // Set line to the part after the label
        }

        stringstream ss(line);
        string opcode;
        ss >> opcode;

        if (opcode == "add" || opcode == "sub" || opcode == "and" || opcode == "or" || opcode == "xor" ||
            opcode == "sll" || opcode == "srl" || opcode == "sra" || opcode == "slt" || opcode == "sltu")
        {
            string rd, rs1, rs2;
            // Get rd, rs1, and rs2, handling commas
            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            getline(ss, rs2);

            // remove the leading and trailing spaces(if any) 
            rd = trim(rd);
            rs1 = trim(rs1);
            rs2 = trim(rs2);

            if(registerMap.find(rd) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs2) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }

            int rdNum = registerMap[rd];
            int rs1Num = registerMap[rs1];
            int rs2Num = registerMap[rs2];

            string funct3, funct7;
            if (opcode == "add")
                funct3 = "0x0",    funct7 = "0x00";
            else if (opcode == "sub")
                funct3 = "0x0",    funct7 = "0x20";
            else if (opcode == "and")
                funct3 = "0x7",    funct7 = "0x00";
            else if (opcode == "or")
                funct3 = "0x6",    funct7 = "0x00";
            else if (opcode == "xor")
                funct3 = "0x4",    funct7 = "0x00";
            else if (opcode == "sll")
                funct3 = "0x1",    funct7 = "0x00";
            else if (opcode == "srl")
                funct3 = "0x5",    funct7 = "0x00";
            else if (opcode == "sra")
                funct3 = "0x5",    funct7 = "0x20";
            else if(opcode == "slt")
                funct3 = "0x2",    funct7 = "0x00";
            else if(opcode == "sltu")
                funct3 = "0x3",    funct7 = "0x00";

            uint32_t machineCode = convertRType("0x33", funct3, funct7, rdNum, rs1Num, rs2Num);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }

        else if (opcode == "addi" || opcode == "andi" || opcode == "ori" || opcode == "xori" || opcode == "slli" ||
                 opcode == "srli" || opcode == "srai" || opcode == "slti" || opcode == "sltiu")
        {
            string rd, rs1, offset;

            getline(ss, rd, ',');
            getline(ss, rs1, ',');
            getline(ss, offset);

            rd = trim(rd);
            rs1 = trim(rs1);
            offset = trim(offset);

            if(registerMap.find(rd) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }

            int imm = stoi(offset);

            if (imm > 2047 || imm < -2048){
                    outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                    continue;
                }

            if((opcode == "srli" || opcode == "slli" || opcode == "srai") && (imm < 0 || imm > 63)){
                    outfile << dec << "Error: Immediate value " << imm << " is inavalid for " << opcode << " at line " << i+1 << "." << endl;
                    continue;
            }

            int rdNum = registerMap[rd];
            int rs1Num = registerMap[rs1];

            string funct3;
            if (opcode == "addi")
                        funct3 = "0x0";
            else if (opcode == "andi")
                        funct3 = "0x7";
            else if (opcode == "ori")
                        funct3 = "0x6";
            else if (opcode == "xori")
                        funct3 = "0x4";
            else if (opcode == "slli")
                        funct3 = "0x1";
            else if (opcode == "srli")
                        funct3 = "0x5";
            else if (opcode == "srai")
                        funct3 = "0x5",    imm |= 0x400;
            else if (opcode == "slti")
                        funct3 = "0x2";
            else if (opcode == "sltiu")
                        funct3 = "0x3";

            uint32_t machineCode = convertIType("0x13", funct3, rdNum, rs1Num, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }

        else if (opcode == "ld" || opcode == "lw" || opcode == "lh" || opcode == "lb" ||
                 opcode == "lhu" || opcode == "lbu" || opcode == "lwu")
        {
            string rs1, rd, offset;


            getline(ss, rd, ',');
            getline(ss, offset, '(');
            getline(ss, rs1, ')');

            rd = trim(rd);
            rs1 = trim(rs1);

            if(registerMap.find(rd) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }

            int imm = stoi(trim(offset));
            int rdNum = registerMap[rd];
            int rs1Num = registerMap[rs1];


            if (imm > 2047 || imm < -2048){
                    outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                    continue;
            }


            string funct3;
            if (opcode == "lb")
                        funct3 = "0x0";
            else if (opcode == "lh")
                        funct3 = "0x1";
            else if (opcode == "lw")
                        funct3 = "0x2";
            else if (opcode == "ld")
                        funct3 = "0x3";
            else if (opcode == "lbu")
                        funct3 = "0x4";
            else if (opcode == "lhu")
                        funct3 = "0x5";
            else if (opcode == "lwu")
                        funct3 = "0x6";


            uint32_t machineCode = convertIType("0x03", funct3, rdNum, rs1Num, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }
        else if (opcode == "jalr")
        {
            string rs1, rd, offset;


            getline(ss, rd, ',');
            getline(ss, offset, '(');
            getline(ss, rs1, ')');


            rd = trim(rd);
            rs1 = trim(rs1);
            if(registerMap.find(rd) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }


           /* if(isdigit(rd[0]) || isdigit(rs1[0])){
                    outfile << dec << "Error: Invalid operand at line no " << i+1 << endl;
                    continue;
            }  */
           
            int imm = stoi(trim(offset));
            int rdNum = registerMap[rd];
            int rs1Num = registerMap[rs1];


            if (imm > 2047 || imm < -2048){
                    outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                    continue;
            }


            string funct3 = "0x0";


            uint32_t machineCode = convertIType("0x67", funct3, rdNum, rs1Num, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }
         else if(opcode == "jal")
            {
                string rd, offset;
                getline(ss, rd, ',');
                getline(ss, offset);


                offset = trim(offset);
                rd = trim(rd);


                if(registerMap.find(rd) == registerMap.end()){
                       outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                       continue;
                }

                int rdNum = registerMap[rd];
                int imm;


                if(isdigit(offset[0]) || offset[0] == '-')
                            imm = stoi(offset);
                else{
                    if(labelAddress.find(offset) != labelAddress.end())
                            imm = labelAddress[offset] - 4*i ;
                    else{
                            outfile << dec << "Error: Undefined Label at line " << i+1 << "." << endl;
                            continue;
                    }
                }


                if(imm > 1048574 || imm < -1048576) {
                        outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                        continue;
                }


                uint32_t machineCode = convertJType("0x6f", rdNum, imm);
                outfile << hex << setw(8) << setfill('0') << machineCode << endl;
            }
        else if (opcode == "lui" || opcode == "auipc")
        {
            if(opcode == "lui")
                        opcode = "0x37";

            else if(opcode == "auipc")
                        opcode = "0x17";

            string rd, immediate;

            getline(ss, rd, ',');
            getline(ss,immediate);

            rd = trim(rd);

            if(registerMap.find(rd) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }

            int rdNum = registerMap[rd];
            int imm = stoi(immediate);
            if(imm < 0)
                    imm += 1048576;

            else if((imm > 1048575))
                    outfile << dec << "Error: Immediate value " << imm << "is out of range at line no " << i +1 << "." << endl;


            uint32_t machineCode = convertUType(opcode, rdNum, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }
       
        else if (opcode == "sd" || opcode == "sb" || opcode == "sw" || opcode == "sh")
        {
            string rs1, rs2, offset;

            getline(ss, rs2, ',');
            getline(ss, offset, '(');
            getline(ss, rs1, ')');

            rs2 = trim(rs2);
            rs1 = trim(rs1);

            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs2) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }

            int imm = stoi(offset);
            int rs2Num = registerMap[rs2];
            int rs1Num = registerMap[rs1];


            if (imm > 2047 || imm < -2048){
                    outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                    continue;
            }


            string funct3;
            if (opcode == "sb")
                funct3 = "0x0";
            else if (opcode == "sh")
                funct3 = "0x1";
            else if (opcode == "sw")
                funct3 = "0x2";
            else if (opcode == "sd")
                funct3 = "0x3";


            uint32_t machineCode = convertSType("0x23", funct3, rs1Num, rs2Num, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }
        else if (opcode == "beq" || opcode == "bne" || opcode == "blt" ||
                 opcode == "bge" || opcode == "bltu" || opcode == "bgeu")
        {
            string rs1,rs2,offset;


            getline(ss, rs1, ',');
            getline(ss, rs2, ',');
            getline(ss, offset);


            rs2 = trim(rs2);
            rs1 = trim(rs1);
            offset = trim(offset);

            if(registerMap.find(rs1) == registerMap.end()){
                 outfile << dec << "Error: invalid input at line no " << i+1 << "." << endl;
                 continue;
            }
            if(registerMap.find(rs2) == registerMap.end()){         
                outfile << dec<<"Error: invalid input at line no " << i+1<< "." << endl;
                 continue;
            }

            int imm;
            int rs2Num = registerMap[rs2];
            int rs1Num = registerMap[rs1];

            if(isdigit(offset[0]) || offset[0] == '-')
                    imm = stoi(offset);
            else{
                if(labelAddress.find(offset) != labelAddress.end())
                        imm = labelAddress[offset] - 4*i;
                else{
                        outfile << dec<<"Error: Undefined Label at line " << i+1 <<"." << endl;
                        continue;
                }
            }
            if(imm > 4094 || imm < -4096){
                    outfile << dec << "Error: Immediate value " << imm << " out of range at line " << i+1 << "." << endl;
                    continue;
            }


            string funct3;
            if (opcode == "beq")
                funct3 = "0x0";
            else if (opcode == "bne")
                funct3 = "0x1";
            else if (opcode == "blt")
                funct3 = "0x4";
            else if (opcode == "bge")
                funct3 = "0x5";
            else if (opcode == "bltu")
                funct3 = "0x6";
            else if (opcode == "bgeu")
                funct3 = "0x7";


            uint32_t machineCode = convertBType("0x63", funct3, rs1Num, rs2Num, imm);
            outfile << hex << setw(8) << setfill('0') << machineCode << endl;
        }
        else{
                outfile << dec << "Error: Unsupported or incorrect instruction at line " << i + 1 << endl;
                // return 1;
        }
    }
    outfile.close();
}
