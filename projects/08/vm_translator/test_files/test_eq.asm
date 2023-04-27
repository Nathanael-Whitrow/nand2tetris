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