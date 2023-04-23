#include "codeWriter.hpp"

// Constructor - open the output file for writing
CodeWriter::CodeWriter(std::filesystem::path asmFile) { fileWriter.open(asmFile, std::fstream::out); }

// Destructor
CodeWriter::~CodeWriter() { fileWriter.close(); }

// Called when translation of a new file starts
void CodeWriter::setFileName(std::filesystem::path path)
{
  // I expect this to write some sort of label into the assembly
  return;
}

// Writes assembly for given arithmetic command
void CodeWriter::writeArithmetic(std::string command)
{
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
  return;
}

// Write the assembly for the push/pop command
void CodeWriter::writePushPop(commandTypes commandType,
                              std::string segment,
                              std::string index)
{
  if (commandType == C_PUSH)
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
  return;
}

// The destructor should do this so this shouldn't be needed
// Leaving here because of spec
void CodeWriter::close() { return; }