#include "command.hpp"
#include "parser.hpp"

#include <iostream>
#include <regex>

// Constructor
Parser::Parser(std::filesystem::path vmFile) { fileReader.open(vmFile, std::fstream::in); }

// Destructor
Parser::~Parser() { fileReader.close(); }

bool Parser::hasMoreCommands()
{
  if (fileReader.eof())
  {
    std::cout << "eof reached!" << std::endl;
    return false;
  }
  else
  {
    return true;
  }
}

// Scrubs line of comments and beginning and ending white space.
// Doesn't fix extra whitespace in between commands
// If there's not text then it returns an empty string.
std::string Parser::advance()
{
  std::string line;
  // getline inherently dumps delimiter
  getline(fileReader, line);

  // TODO: break out each of these into helper functions
  // Then I can use the call stack to debug

  // remove carriage returns.
  if ((line.length() > 0) && isspace(line.back()))
    line.pop_back();

  // remove comments
  auto position = line.find("//");
  if (position != std::string::npos)
    line = line.substr(0, position);

  // Trim any leading whitespace
  for (auto it : line)
  {
    if (!isspace(it))
    {
      line = line.substr(line.find_first_of(it), line.size());
      break;
    }
  }

  // Trim trailing whitespace
  auto it = line.end();
  while (it != line.begin())
  {
    --it;
    if (isspace(*it))
      line.pop_back();
    else
      break;
  }

  return line;
}

// returns true if not empty
// Then returns false if line is empty
//
// Note:
// This function tells if the line is not empty
// So if this returns true then we should look
// for a command. Not guarantee it's not a syntax
// error.
bool Parser::isCommand(std::string line)
{
  if (line.empty())
    return false;
  return true;
}

// Returns the command type
commandTypes Parser::commandType(std::string line)
{
  // Just tokenize the line...
  auto const re = std::regex{"\\s+"};
  auto const tokens = std::vector<std::string>(
      std::sregex_token_iterator{begin(line), end(line), re, -1},
      std::sregex_token_iterator{});

  // Look for arithmetic command
  std::array<std::string, NUM_ARITHMETIC_COMMANDS> arithmeticCommands{
      "add",
      "sub",
      "neg",
      "eq",
      "gt",
      "lt",
      "and",
      "or",
      "not"};

  for (const auto it : arithmeticCommands)
    if (it == tokens[0])
      return C_ARITHMETIC;

  // Look for PUSH command
  if (tokens[0] == "push")
    return C_PUSH;

  // Look for POP command
  else if (tokens[0] == "pop")
    return C_POP;

  // Look for "label" command
  else if (tokens[0] == "label")
    return C_LABEL;

  // Look for "goto label" command
  else if (tokens[0] == "goto")
    return C_GOTO;

  // Look for "if-goto label" command
  else if (tokens[0] == "if-goto")
    return C_IF;

  // Look for "function f n" command
  else if (tokens[0] == "function")
    return C_FUNCTION;

  // Look for "return" command
  else if (tokens[0] == "return")
    return C_RETURN;

  // Look for "call f n" command
  else if (tokens[0] == "call")
    return C_CALL;

  // No valid command found
  return ERROR;
}

std::string Parser::arg1(std::string line, commandTypes type)
{
  // Just tokenize the line...
  auto const re = std::regex{"\\s+"};
  auto const tokens = std::vector<std::string>(
      std::sregex_token_iterator{begin(line), end(line), re, -1},
      std::sregex_token_iterator{});

  switch (type)
  {
  case C_ARITHMETIC:
    return tokens[0];

  case C_PUSH:
  case C_POP:
  case C_LABEL:
  case C_GOTO:
  case C_IF:
  case C_FUNCTION:
  case C_CALL:
    return tokens[1];

  default:
    return "";
  }
  return "";
}

// Only called for push, pop, function and call commands
std::string Parser::arg2(std::string line, commandTypes type)
{
  // Just tokenize the line...
  auto const re = std::regex{"\\s+"};
  auto const tokens = std::vector<std::string>(
      std::sregex_token_iterator{begin(line), end(line), re, -1},
      std::sregex_token_iterator{});

  switch (type)
  {
  case C_PUSH:
  case C_POP:
  case C_FUNCTION:
  case C_CALL:
    return tokens[2];

  default:
    return "";
  }
}