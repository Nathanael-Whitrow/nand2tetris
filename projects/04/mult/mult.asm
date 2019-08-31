// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm
// Solution by Nathanael Whitrow (n8)
// 31/08/2019

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)


	@R2
	M=0
(LOOP)
	@R1
	D=M
	@DONE
	D;JLE
	@R0
	D=M
	@R2
	M=D+M
	@R1
	M=M-1
	@LOOP
	0;JMP
(DONE)
	@DONE
	0;JMP