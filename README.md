# RISC-V Assembler

## Overview
This project implements a RISC-V assembler that converts assembly code into machine code. The implementation includes multiple C++ files and its functionality for changing assembly instructions, handling various RISC-V formats. It also shows its respective hexadecimal machine code. 

## Directory Structure
The project directory contains the following files:

- `Instruction.h`: Header file declaring functions for mapping of parsing and encoding RISC-V instructions.
- `formats.cpp` : contains the implementation for all type(R,I,S,B,J,U) of instruction encoding
- `Main.cpp`: The main file that coordinates reading input, parsing instructions, and generating machine code.
- `Instruction.cpp`: The Parse function processes each line of RISC-V assembly code, converts it into machine code, and writes the output to output.hex.
- `Makefile`: The Makefile used to build the project.
- `input.s`: Sample input assembly file (to be provided).
- `output.hex`: The generated machine code output file.

## Usage Instructions

### Compiling the Project

To compile the project, just run the command in terminal

```bash
make
```
To clean the temporaries/executables, run the command
```bash
make clean
```



