#include "codeWriter.hpp"

#include <iostream>
#include <string>

// Constructor - open the output file for writing
CodeWriter::CodeWriter(std::filesystem::path asmFile)
{
  std::cout << "output file: " << asmFile << std::endl;
  fileWriter.open(asmFile, std::fstream::out);
  // preamble and setup here?
}

// Destructor
CodeWriter::~CodeWriter() { fileWriter.close(); }

// Called when translation of a new file starts
// Used for name-spacing static variables
void CodeWriter::setFileName(std::filesystem::path path)
{
  filename = path.stem();
  return;
}

// Writes assembly for given arithmetic command
void CodeWriter::writeArithmetic(std::string command, uint unique_label_count)
{
  auto unique_label = std::to_string(unique_label_count);
  if (command == "add")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M" << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=D+M" << std::endl;
    fileWriter << "  M=D" << std::endl;
  }
  else if (command == "sub")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M" << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=M-D" << std::endl;
    fileWriter << "  M=D" << std::endl;
  }
  else if (command == "neg")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  D=!M" << std::endl;
    fileWriter << "  M=D+1" << std::endl;
  }
  else if (command == "eq")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M" << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=D-M" << std::endl;
    fileWriter << "  @TRUE" << unique_label << std::endl;
    fileWriter << "  D;JEQ" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=0" << std::endl;
    fileWriter << "  @END" << unique_label << std::endl;
    fileWriter << "  0;JMP" << std::endl;
    fileWriter << "(TRUE" << unique_label << ")" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=-1" << std::endl;
    fileWriter << "(END" << unique_label << ")" << std::endl;
  }
  else if (command == "gt")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M" << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=M-D" << std::endl;
    fileWriter << "  @TRUE" << unique_label << std::endl;
    fileWriter << "  D;JGT" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=0" << std::endl;
    fileWriter << "  @END" << unique_label << std::endl;
    fileWriter << "  0;JMP" << std::endl;
    fileWriter << "(TRUE" << unique_label << ")" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=-1" << std::endl;
    fileWriter << "(END" << unique_label << ")" << std::endl;
  }
  else if (command == "lt")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M" << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=M-D" << std::endl;
    fileWriter << "  @TRUE" << unique_label << std::endl;
    fileWriter << "  D;JLT" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=0" << std::endl;
    fileWriter << "  @END" << unique_label << std::endl;
    fileWriter << "  0;JMP" << std::endl;
    fileWriter << "(TRUE" << unique_label << ")" << std::endl;
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=-1" << std::endl;
    fileWriter << "(END" << unique_label << ")" << std::endl;
  }
  else if (command == "and")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M " << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=D&M" << std::endl;
    fileWriter << "  M=D" << std::endl;
  }
  else if (command == "or")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  M=M-1" << std::endl;
    fileWriter << "  A=M" << std::endl;
    fileWriter << "  D=M " << std::endl;
    fileWriter << "  A=A-1" << std::endl;
    fileWriter << "  D=D|M" << std::endl;
    fileWriter << "  M=D" << std::endl;
  }
  else if (command == "not")
  {
    fileWriter << "  @SP" << std::endl;
    fileWriter << "  A=M-1" << std::endl;
    fileWriter << "  M=!M" << std::endl;
  }

  return;
}

// Write the assembly for the push/pop command
void CodeWriter::writePushPop(commandTypes commandType,
                              std::string segment,
                              std::string index)
{
  if (segment == "local")
    segment = "LCL";
  else if (segment == "argument")
    segment = "ARG";
  else if (segment == "temp")
    segment = "R5";
  else if (segment == "pointer")
    segment = "R3";

  if (commandType == C_PUSH)
  {
    if (segment == "constant")
    {
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=A" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  D=A+1" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
    else if (segment == "R5" || segment == "R3")
    {
      std::transform(segment.begin(), segment.end(), segment.begin(), ::toupper);
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=A" << std::endl;
      fileWriter << "  @" << segment << std::endl;
      fileWriter << "  A=D+A" << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  D=A+1" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
    else if (segment == "static")
    {
      index = filename.string() + "." + index;
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=M+1" << std::endl;
    }
    else
    {
      // LCL, ARG, THIS, THAT
      std::transform(segment.begin(), segment.end(), segment.begin(), ::toupper);
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=A" << std::endl;
      fileWriter << "  @" << segment << std::endl;
      fileWriter << "  A=D+M" << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  D=A+1" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
  }
  else if (commandType == C_POP)
  {
    if (segment == "R5" || segment == "R3")
    {
      std::transform(segment.begin(), segment.end(), segment.begin(), ::toupper);
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=A" << std::endl;
      fileWriter << "  @" << segment << std::endl;
      fileWriter << "  D=A+D" << std::endl;
      fileWriter << "  @R14" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=M-1" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @R14" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
    else if (segment == "static")
    {
      index = filename.string() + "." + index;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=M-1" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
    else
    {
      std::transform(segment.begin(), segment.end(), segment.begin(), ::toupper);
      fileWriter << "  @" << index << std::endl;
      fileWriter << "  D=A" << std::endl;
      fileWriter << "  @" << segment << std::endl;
      fileWriter << "  D=M+D" << std::endl;
      fileWriter << "  @R14" << std::endl;
      fileWriter << "  M=D" << std::endl;
      fileWriter << "  @SP" << std::endl;
      fileWriter << "  M=M-1" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  D=M" << std::endl;
      fileWriter << "  @R14" << std::endl;
      fileWriter << "  A=M" << std::endl;
      fileWriter << "  M=D" << std::endl;
    }
  }
  return;
}

void CodeWriter::writeCall(std::string functionName, uint unique_label_count, int numArgs)
{
  auto unique_label = std::to_string(unique_label_count);
  fileWriter << "  @" << unique_label << "$return-address" << std::endl;
  fileWriter << "  D=A" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M+1" << std::endl;
  fileWriter << "  @LCL" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @SP " << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M+1" << std::endl;
  fileWriter << "  @ARG" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @SP " << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M+1" << std::endl;
  fileWriter << "  @THIS" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @SP " << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M+1" << std::endl;
  fileWriter << "  @THAT" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @SP " << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M+1" << std::endl;
  fileWriter << "  @" << std::to_string(numArgs) << std::endl;
  fileWriter << "  D=A" << std::endl;
  fileWriter << "  @5" << std::endl;
  fileWriter << "  D=D+A" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  D=M-D" << std::endl;
  fileWriter << "  @ARG" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @LCL" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @" << functionName << std::endl;
  fileWriter << "  0;JMP" << std::endl;
  fileWriter << "(" << unique_label << "$return-address)" << std::endl;
  return;
}

void CodeWriter::writeFunction(std::string functionName, int numLocals)
{
  // fileWriter << "// C_FUNCTION " << functionName << " " << numLocals << std::endl;
  fileWriter << "(" << functionName << ")" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  A=M" << std::endl;
  for (int i = 0; i < numLocals; i++)
  {
    fileWriter << "  M=0" << std::endl;
    fileWriter << "  A=A+1" << std::endl;
  }
  fileWriter << "  D=A" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=D" << std::endl;
  return;
}

void CodeWriter::writeGoTo(std::string label)
{
  fileWriter << "  @" << label << " // C_GOTO " << label << std::endl;
  fileWriter << "  0;JMP" << std::endl;
  return;
}

void CodeWriter::writeIf(std::string label)
{
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M-1" << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @" << label << std::endl;
  fileWriter << "  D;JNE" << std::endl;
  return;
}

void CodeWriter::writeInit()
{
  fileWriter << "  @256"
             << " // Bootstrap" << std::endl;
  fileWriter << "  D=A" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=D" << std::endl;
  writeCall("Sys.init", 0, 0);
  return;
}

void CodeWriter::writeLabel(std::string label)
{
  // fileWriter << "// C_LABEL " << label << std::endl;
  fileWriter << "(" << label << ")" << std::endl;
  return;
}

void CodeWriter::writeReturn()
{
  fileWriter << "  @LCL" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @5" << std::endl;
  fileWriter << "  A=D-A" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @R14" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=M-1" << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @ARG" << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @ARG" << std::endl;
  fileWriter << "  D=M+1" << std::endl;
  fileWriter << "  @SP" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  A=M-1" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @THAT" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  A=M-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @THIS" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  A=M-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @ARG" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R13" << std::endl;
  fileWriter << "  A=M-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  A=A-1" << std::endl;
  fileWriter << "  D=M" << std::endl;
  fileWriter << "  @LCL" << std::endl;
  fileWriter << "  M=D" << std::endl;
  fileWriter << "  @R14" << std::endl;
  fileWriter << "  A=M" << std::endl;
  fileWriter << "  0;JMP" << std::endl;
  return;
}

// The destructor should do this so this shouldn't be needed
// Leaving here because of spec
void CodeWriter::close() { return; }