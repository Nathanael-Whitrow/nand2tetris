Arithmetic commands:

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
  M=M-1
  A=M
  D=M // D holds y
  A=A-1 // A points to x
  D=D-M // store y-x in D
  // Jump based on result
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
  A=M // A points to y
  D=M 
  A=A-1 // A points to x
  D=D&M
  M=D

OR:
  @SP
  M=M-1
  A=M // A points to y
  D=M 
  A=A-1 // A points to x
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


