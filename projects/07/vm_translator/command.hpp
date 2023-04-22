#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "commandTypes.hpp"
#include <string>

class Command
{
public:
  Command() : line(""),
              command(commandTypes::ERROR),
              arg1(""),
              arg2("")
  {
  }
  ~Command(){};

  void clear()
  {
    line = "";
    command = commandTypes::ERROR;
    arg1 = "";
    arg2 = "";
  }

  void setLine(std::string newLine)
  {
    line = newLine;
    return;
  };
  void setCommandType(commandTypes newType)
  {
    command = newType;
    return;
  }
  void setArg1(std::string newArg1)
  {
    arg1 = newArg1;
    return;
  }
  void setArg2(std::string newArg2)
  {
    arg2 = newArg2;
    return;
  }

  std::string getLine() { return line; }
  commandTypes getCommandType() { return command; }
  std::string getArg1() { return arg1; }
  std::string getArg2() { return arg2; }

private:
  std::string line;
  commandTypes command;
  std::string arg1;
  std::string arg2;
};

#endif