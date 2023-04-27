// push/pop constant 111
  @111
  D=A
  @SP
  A=M
  M=D
  D=A+1
  @SP
  M=D
// push/pop constant 333
  @333
  D=A
  @SP
  A=M
  M=D
  D=A+1
  @SP
  M=D
// push/pop constant 888
  @888
  D=A
  @SP
  A=M
  M=D
  D=A+1
  @SP
  M=D
// push/pop static 8
  @SP
  M=M-1
  A=M
  D=M
  @StaticTest.8
  M=D
// push/pop static 3
  @SP
  M=M-1
  A=M
  D=M
  @StaticTest.3
  M=D
// push/pop static 1
  @SP
  M=M-1
  A=M
  D=M
  @StaticTest.1
  M=D
// push/pop static 3
  @StaticTest.3
  D=M
  @SP
  A=M
  M=D
  @SP
  M=M+1
// push/pop static 1
  @StaticTest.1
  D=M
  @SP
  A=M
  M=D
  @SP
  M=M+1
// C_ARITHMETIC sub
  @SP
  M=M-1
  A=M
  D=M
  A=A-1
  D=M-D
  M=D
// push/pop static 8
  @StaticTest.8
  D=M
  @SP
  A=M
  M=D
  @SP
  M=M+1
// C_ARITHMETIC add
  @SP
  M=M-1
  A=M
  D=M
  A=A-1
  D=D+M
  M=D
