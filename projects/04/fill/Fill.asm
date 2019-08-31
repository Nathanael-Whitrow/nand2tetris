// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm
// Solution by Nathanael Whitrow (n8)
// 31/08/2019

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, R16.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.


// R16 holds address of current pixel

(START)
	// set counter to start of screen address
	@SCREEN
	D=A
	@R16
	M=D
	// check if keyboard pressed.
	@KBD
	D=M
	@BLACK
	D;JNE

(WHITE)
	// loop through entire screen making each pixel white
	@R16
	A=M
	M=0
	// only increment until end of screen, then start again
	@R16
	D=M+1
	@KBD
	D=D-A
	@START
	D;JEQ
	// else increment counter and go again
	@R16
	M=M+1

	@KBD // check if keyboard has changed. if not, repeat.
	D=M
	@WHITE
	D;JEQ
	@START // otherwise restart
	0;JMP

(BLACK)
	// loop through entire screen making each pixel white
	@R16
	A=M
	M=-1
	
	@R16
	D=M+1
	@KBD
	D=D-A
	@START
	D;JEQ
	// else increment counter and go again
	@R16
	M=M+1

	@KBD // check if keyboard has changed. if not, repeat.
	D=M
	@BLACK
	D;JNE
	@START // otherwise restart
	0;JMP
