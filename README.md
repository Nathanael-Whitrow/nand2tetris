# Nand to Tetris Solutions

## Description

This repository contains my solutions for the [Nand to Tetris course](https://www.nand2tetris.org/). The course takes you through building a modern computer system from first principles, starting from the most fundamental NAND gate all the way to a computer capable of running software written in a high-level language.

## Current Progress

As of now, the repository includes solutions up to Chapter 8 of the course. Here's a brief summary of the contents of each chapter:

1. **Chapter 1 - Boolean Functions and Gate Logic:** Introduction to binary codes and logic gates.
2. **Chapter 2 - Boolean Arithmetic:** Design of an Arithmetic Logic Unit (ALU) capable of performing operations on binary numbers.
3. **Chapter 3 - Sequential Logic:** Creation of memory units like flip-flops and registers.
4. **Chapter 4 - Machine Language:** Introduction to the machine language of the built computer system.
5. **Chapter 5 - Computer Architecture:** Design of the CPU and the computer system that integrates the ALU and memory units.
6. **Chapter 6 - Assembler:** Development of an assembler to translate programs written in assembly language into machine language.
7. **Chapter 7 - Virtual Machine I: Stack Arithmetic:** Design of a stack-based virtual machine to abstract the machine language.
8. **Chapter 8 - Virtual Machine II: Program Control:** Enhancements to the virtual machine to support program control operations.

## How to Use This Repository

The solutions in this repository are divided by chapter. Each chapter contains the relevant `.hdl` files, and starting from Chapter 6, there are also C++ source code and Makefiles for the relevant solutions.

To use these solutions, clone this repository and use the files as references while working through the problems in the Nand to Tetris course. Remember, try to solve the problems on your own first before referring to these solutions!

I have written the Makefiles to call the Clang compiler, but the code should be compatible with any UNIX style c++ compiler.

## Contributing

This repository is currently not accepting contributions. It is intended to be a personal record of my progress through the Nand to Tetris course.

## Contact

If you have any questions about this repository, feel free to reach out to me at `nathanael.whitrow@gmail.com`.

## Acknowledgments

A big thank you to the creators of the Nand to Tetris course for providing such a valuable resource for learning about computer architecture and systems.
