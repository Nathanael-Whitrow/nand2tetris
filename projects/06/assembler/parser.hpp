#ifndef PARSER_HPP
#define PARSER_HPP

#include "commandTypes.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Parser
{
public:
	Parser(std::string assemblyFile) 	{ fileReader.open(assemblyFile, std::fstream::in); }
	~Parser() 							{ fileReader.close(); }


	// Checks if the eof bit has been set by getline()
	bool hasMoreLines()
	{
		if(fileReader.eof())
		{
			std::cout << "eof reached!" << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}

	// getline inherently dumps delimiter (in this case newline)
	std::string advance()
	{
		std::string line;
		getline(fileReader, line);
		return line;
	}

	// Scrubs line of comments and white space.
	// Then returns false if line is empty
	// returns true if not empty after removing white space and comments
	// Note that at this point, this code assumes a valid .asm file.
	bool isCommand(std::string& line)
	{
		// remove carriage returns.
		if ((line.length() > 0) && isspace(line.back())) 	{ line.pop_back(); }
		if (line.length() == 0) 							{ return false; }

		// remove comments
		auto position = line.find("//");
		if (position != std::string::npos)
		{
			line = line.substr(0, position);
			if (line.length() == 0)
				return false;
		}

		// remove white-space
		std::string newLine;
		for(auto it : line)
			if(!isspace(it))
				newLine.push_back(it);
		line = newLine;

		if (line.length() == 0) { return false; }

		return true;
	}

	// assumes line is a valid command - only called if isCommand returns true
	commandTypes commandType(std::string& line)
	{
		if 		(line.front() == '@')	{ return A_command; }
		else if (line.front() == '(')	{ return L_command; }
		else							{ return C_command; }
	}

	// return the immediate for an A command
	std::string getImmediate(std::string& line)
	{
		return line.substr(1, line.length()-1);
	}

	std::string getLabel(std::string& line)
	{
		return line.substr(1,line.length()-2);
	}

	// Return the dest symbol
	std::string getDest(std::string& line)
	{
		auto it = line.find("=");
		if (it != std::string::npos)
			return line.substr(0, it);
		else
			return "";
	}

	// Return the comp symbol
	std::string getComp(std::string& line)
	{
		// find the start of comp
		auto start = line.find("=");
		auto finish = line.find(";");
		if (start == std::string::npos)
			start = 0;
		else
			++start;
		return line.substr(start, finish);
	}

	// return the jump symbol
	std::string getJump(std::string& line)
	{
		auto start = line.find(";");
		if (start != std::string::npos)
			return line.substr(++start, 3);
		else
			return "";
	}

	void printLineHex(std::string& line)
	{
		for (auto x : line)
			std::cout << std::hex << (int) x;
		std::cout << std::endl;
	}

private:
	std::fstream fileReader;
};


#endif