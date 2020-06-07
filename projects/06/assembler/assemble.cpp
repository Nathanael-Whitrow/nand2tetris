#ifndef ASSEMBLE_CPP
#define ASSEMBLE_CPP

#include "code.hpp"
#include "commandTypes.hpp"
#include "parser.hpp"
#include "SymbolTable.hpp"

#include <cctype>
#include <filesystem>
#include <iostream>
#include <string>

bool checkInputFile(std::string file)
{
	if (!std::filesystem::exists(file))
	{
		std::cout << "file doesn't exist... Avengers going home." << std::endl;
		return false;
	}

	// non-robust check for .asm
	if((file.find(".asm", 0)) == std::string::npos)
	{
		std::cout << ".asm file type not detected!! Avengers are fed up with your incompetence." << std::endl;
		return false;
	}

	return true;
}

void buildACommand (Parser& parser,
					Code& code,
					SymbolTable& sTable,
					std::string& line,
					std::string& command,
					uint& varNo)
{
	std::string symbol = parser.getImmediate(line);
	if (isdigit(symbol[0]))
	{
		//we have an immedite!
		command = code.getImmediateBinary(symbol);
	}
	else
	{
		// we have a symbol, and need to resolve it to an address
		if (sTable.contains(symbol))
		{
			// either previously encountered variable or label
			symbol = sTable.getAddress(symbol);
		}
		else
		{
			// new variable
			sTable.addEntry(symbol, std::to_string(varNo));
			symbol = sTable.getAddress(symbol);
			++varNo;
		}
		command = code.getImmediateBinary(symbol);
	}
}

void buildCCommand (Parser& parser, Code& code, std::string& line, std::string& command)
{
	// get the mnemonics
	std::string dest = parser.getDest(line);
	std::string comp = parser.getComp(line);
	std::string jump = parser.getJump(line);
	// get the binary
	dest = code.getDestBinary(dest);
	comp = code.getCompBinary(comp);
	jump = code.getJumpBinary(jump);
	command = "111" + comp + dest + jump;
}

int main(int argc, char* argv[])
{
	std::cout << "Avengers!! Assemble!!" << std::endl;

	if(argc > 1)
	{
		if(!checkInputFile(argv[1])) { return 0; }
	}
	else
	{
		std::cout << "The Avengers need a target!\n";
		return 0;
	}


	Parser 	parser(argv[1]);
	Code 	code(argv[1]);
	SymbolTable sTable;

	// first pass
	// cleans each line of input file
	// add real commands to instruction vector
	std::string command;
	std::string line;
	std::string symbol;
	uint32_t count = 0;
	uint varNo = 16;
	std::vector<std::string> commandList;

	// First loop adds A and C commands to command vector
	// and builds symbol table, resolving labels.
	while (parser.hasMoreLines())
	{
		symbol = "";
		line = parser.advance();

		if (parser.isCommand(line))
		{
			switch (parser.commandType(line))
			{
				case A_command  : commandList.push_back(line); ++count; break;
				case C_command  : commandList.push_back(line); ++count; break;
				case L_command	: symbol = parser.getLabel(line);
								  if (!sTable.contains(symbol))
								  {
								      sTable.addEntry(symbol, std::to_string(count));
								  }
								  break;
				default 		: std::cout << "default - no command recognised.\n"; return 0;
			}
		}
	}

	std::cout << "first pass done\n";

	// Second loop resolves labels referenced in A command
	// and writes A and C commands as binary to file
	for (auto& it : commandList)
	{
		command = "";
		switch (parser.commandType(it))
		{
			case A_command  : buildACommand(parser, code, sTable, it, command, varNo); break;
			case C_command  : buildCCommand(parser, code ,it, command); break;
			default			: std::cout << "default - bad command in command vector.\n"; return 0;
		}
		code.putLine(command);
	}
}

#endif
