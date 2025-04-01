#include "Instruction.h"
#include<bits/stdc++.h>
#include<vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

// globally declaration of maps
unordered_map<string, int> labelAddress;

unordered_map<string, int> registerMap = {
  {"x0", 0}, {"x1", 1}, {"x2", 2}, {"x3", 3}, {"x4", 4}, {"x5", 5}, {"x6", 6}, {"x7", 7}, {"x8", 8}, {"x9", 9}, {"x10", 10}, {"x11", 11}, {"x12", 12}, {"x13", 13}, {"x14", 14}, {"x15", 15}, {"x16", 16}, {"x17", 17}, {"x18", 18}, {"x19", 19}, {"x20", 20}, {"x21", 21}, {"x22", 22}, {"x23", 23}, {"x24", 24}, {"x25", 25}, {"x26", 26}, {"x27", 27}, {"x28", 28}, {"x29", 29}, {"x30", 30}, {"x31", 31},
 // Register aliases
{"zero", 0}, {"ra", 1}, {"sp", 2}, {"gp", 3}, {"tp", 4}, {"t0", 5}, {"t1", 6}, {"t2", 7}, {"s0", 8}, {"fp", 8}, {"s1", 9},     {"a0", 10}, {"a1", 11}, {"a2", 12}, {"a3", 13}, {"a4", 14}, {"a5", 15}, {"a6", 16}, {"a7", 17}, {"s2", 18}, {"s3", 19},{"s4", 20}, {"s5", 21}, {"s6", 22}, {"s7", 23}, {"s8", 24}, {"s9", 25}, {"s10", 26}, {"s11", 27}, {"t3", 28}, {"t4", 29}, {"t5", 30}, {"t6", 31} 
};

// Function to trim spaces from start and end of a string
string trim(const string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
          return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}


int main()
{
    ifstream infile("input.s");
    string line;
    vector<string> program;

    if (!infile.is_open()){
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    // Read the entire file
    while (getline(infile, line))
    {
        // Handle comments
        if (line.find(';') != string::npos)
                  line = line.substr(0, line.find(';'));
        // Skip empty lines
        line = trim(line);
        if (line.empty())
                continue;

        program.push_back(line);
    }
    infile.close();

    // First pass for label addresses (if necessary)
    int address = 0;
    for (unsigned int i = 0; i < program.size(); i++){
            line = program[i];
            size_t colonPos =  line.find(':');
            string label;
                    if (colonPos != string::npos) {
                   
                    string restOfLine = line.substr(colonPos + 1);   // Skip the label and get the rest of the line
                    restOfLine=trim(restOfLine);
                    if(restOfLine.empty()){
                    auto it = program.begin() + i;
                        program.erase(it);
                        continue;
                        }

                     label =line.substr(0,colonPos);

                    if (labelAddress.find(label) != labelAddress.end()){
                            cerr << "Error: Duplicate label '" << label << "' at line " << i + 1 << endl;
                            return 1;
                    }
                        line = restOfLine;  // Set line to the part after the label
                        labelAddress[label] = address;    
                    }
            address += 4;
    }

    Parse(program);
    return 0;
}
