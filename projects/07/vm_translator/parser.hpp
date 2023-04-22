#ifndef PARSER_HPP
#define PARSER_HPP

#define NUM_ARITHMETIC_COMMANDS 9

#include "command.hpp"
#include "commandTypes.hpp"

#include <filesystem>
#include <fstream>

class Parser
{
public:
  Parser(std::filesystem::path);
  ~Parser();

  bool hasMoreCommands();
  std::string advance();
  bool isCommand(std::string);
  commandTypes commandType(std::string);
  std::string arg1(std::string, commandTypes);
  std::string arg2(std::string, commandTypes);

private:
  std::fstream fileReader;
};

#endif