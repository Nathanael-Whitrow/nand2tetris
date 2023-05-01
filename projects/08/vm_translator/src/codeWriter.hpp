#ifndef CODE_WRITER_HPP
#define CODE_WRITER_HPP

#include "commandTypes.hpp"

#include <filesystem>
#include <fstream>

class CodeWriter
{
public:
  CodeWriter(std::filesystem::path);
  ~CodeWriter();

  void setFileName(std::filesystem::path);
  void writeArithmetic(std::string, uint);
  void writeCall(std::string functionName, uint unique_label_count, int numArgs);
  void writeFunction(std::string functionName, int numLocals);
  void writeGoTo(std::string label);
  void writeIf(std::string label);
  void writeInit();
  void writeLabel(std::string label);
  void writePushPop(commandTypes, std::string segment, std::string index);
  void writeReturn();
  void close();

private:
  std::fstream fileWriter;
  std::filesystem::path filename;
};

#endif