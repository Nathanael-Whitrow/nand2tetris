Arithmetic commands:

Truth:
By VM convention:
TRUE => -1 0xffff
FALSE => 0 0x0000

Given Stack state:
x
y
0<-SP

add ( x + y )
sub ( x - y )
neg ( -y )
eq  ( true if x=y, else false )
gt  ( true if x>y, else false )
lt  ( true if x<y, else false )
and ( x AND y )
or  ( x OR y )
not ( NOT y )



add:
  @SP
  M=M-1
  A=M // A points to y
  D=M 
  A=A-1 // A points to x
  D=D+M
  M=D

sub:
  @SP
  M=M-1
  A=M
  D=M // D holds y
  A=A-1 // A points to x
  D=M-D
  M=D

neg:
  @SP
  A=M-1
  D=!M
  M=D+1

eq:
  @SP
  M=M-1 // decrement SP
  A=M   // A points to y
  D=M // D holds y
  A=A-1 // A points to x
  D=D-M // store y-x in D
  // Jump based on result
  // put -1 on stack for true
  // put 0 on stack for false


  @TRUE
  D;JEQ
  @SP
  A=M-1
  M=0
  @END
  0;JMP
(TRUE)
  @SP
  A=M-1
  M=-1
(END)

gt: (x>y)
  @SP
  M=M-1
  A=M
  D=M // D holds y
  A=A-1 // A points to x
  D=M-D // store x-y in D
  // Jump based on result
  @TRUE
  D;JGT
  @SP
  A=M-1
  M=0
  @END
  0;JMP
(TRUE)
  @SP
  A=M-1
  M=-1
(END)


lt: (x<y)
  @SP
  M=M-1
  A=M
  D=M // D holds y
  A=A-1 // A points to x
  D=M-D // store x-y in D
  // Jump based on result
  @TRUE
  D;JLT
  @SP
  A=M-1
  M=0
  @END
  0;JMP
(TRUE)
  @SP
  A=M-1
  M=-1
(END)

AND:
  @SP
  M=M-1
  A=M
  D=M 
  A=A-1
  D=D&M
  M=D

OR:
  @SP
  M=M-1
  A=M
  D=M 
  A=A-1
  D=D|M
  M=D

NOT:
  @SP
  A=M-1
  M=!M


Memory commands:
  push segment index
  pop segment index

RAM address usage map
0-15        Holds pointers
16-255      Holds static (global) variables
256-2047    Stack
2048-16483  Heap
16384-24575 Memory mapped IO

push constant x:
  @x
  D=A
  @SP
  A=M
  M=D
  D=A+1
  @SP
  M=D



At this point I should build a translator that will read
the previous IR instructions and spit out the associated
asesmbly like lil wayne spittin rhymes.


// Assembly notes

// constants: non negative and decimal notation

// user-defined symbols: letters, digits, underscore, dot, dollar, colon
// upper case for lables, lower case for variable names

// Predefind symbols:
// Label  | RAM address
// SP     | 0
// LCL    | 1
// ARG    | 2
// THIS   | 3
// THAT   | 4
// R0-R15 | 0-15
// SCREEN | 16384
// KBD    | 24576

// @LOCAL is translated as a variable and stored in RAM[16]

// Label symbols (xxx)

// Variable symbols: Any other symbol appearing in an assembly program
//  is treated as a variable. These are mapped to consecutive memory
// locations starting at 0x0010 RAM[16]


// push - get variable from memory segment and put it on the stack
// These push commands are the same except for their respective labels
push local x:
push arg x:
push this x:
push that x:
// Add index to memory base location: x + i
// access and push onto stack
  @x      // index into local
  D=A     // store x in d
  @LCL    // assembly symbol
  A=D+M   // M now points to x + i
  D=M     // Store variable in D
  @SP
  A=M     // Point to stack
  M=D     // put variable on stack
  D=A+1   // increment stack pointer
  @SP
  M=D


push temp x:
push pointer x:
  @x
  D=A
  @R5
  A=D+A
  D=M // get variable and store in D
  .
  .
  .

// Takes a variable on the stack and puts it in the segment at index x\
// valid segments are LCL, ARG, THIS, THAT
pop segment x:
  // calculate memory address
  @x
  D=A
  @SEGMENT
  D=M+D
  @R14
  M=D // Store final location
  @SP
  M=M-1
  A=M // Read SP -> A points to stack
  D=M // store top of stack in D
  @R14
  A=M
  M=D


pop temp x:
  // calculate memory address
  @index
  D=A
  @R3/R5
  D=D+A
  @R14
  M=D // Store final location
  @SP
  M=M-1
  A=M // Read SP -> A points to stack
  D=M // store top of stack in D
  @R14
  A=M
  M=D

Statics...
RAM[15] - RAM[255] are used as variables by the assembler
// Variable symbols: Any other symbol appearing in an assembly program
//  is treated as a variable. These are mapped to consecutive memory
// locations starting at 0x0010 RAM[16]

in file xxx.vm there's a static called j; i.e.
test.vm ->
pop static 8

should translate into RAM[16+8] == RAM[23]
The assembler builds it's own symbol table and translates all new symbols to
start at RAM[16] anyway
so @SYMBOL will start at RAM16
So I just need to give each static a unique symbol...
using the above example of test.vm -> pop static 8
@test.8
is the correct translation

push static x:
  @file.x // point to static variable
  D=M
  @SP
  A=M
  M=D
  @SP
  M=M+1

pop static x:
  @SP
  M=M-1 // decrement SP
  A=M   // Point to stack
  D=M   // Grab top of stack and store in D
  @file.x // point to static variable
  M=D   // put D into static storage