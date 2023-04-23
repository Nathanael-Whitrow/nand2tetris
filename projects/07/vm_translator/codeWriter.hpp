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
  void writeArithmetic(std::string);
  void writePushPop(commandTypes, std::string segment, std::string index);
  void close();

private:
  std::fstream fileWriter;
};

#endif