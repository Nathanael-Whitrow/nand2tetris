//
// A virtual machine translator
// by Nathanael Whitrow

#include "codeWriter.hpp"
#include "command.hpp"
#include "commandTypes.hpp"
#include "parser.hpp"

#include <iostream>
#include <filesystem>

std::vector<std::filesystem::path> getFiles(std::string arg)
{
	// Assume we have a path
	auto path = std::filesystem::path(arg);

	std::vector<std::filesystem::path> file_list;

	// Search whole directory for .vm
	if (std::filesystem::is_directory(path))
	{
		// we have a folder, find all .vm files and add to vector
		for (auto const &dir_entry : std::filesystem::directory_iterator{path})
			if (dir_entry.path().has_extension())
				if (dir_entry.path().extension() == ".vm")
					file_list.push_back(dir_entry.path());
	}
	// check for single file
	else if (path.has_extension() && path.extension() == ".vm")
	{
		file_list.push_back(path);
	}
	else
	{
		std::cout << "Bad argument: please provide vm file or directory containing vm file" << std::endl;
	}
	return file_list;
}

// MAIN BABY!!!
int main(const int argc, const char *argv[])
{
	std::cout << "IR to assembly translator online." << std::endl;

	if (argc != 2)
	{
		std::cout << "IR_asm takes one parameter: a target file or directory" << std::endl;
		return 0;
	}

	// Vector for holding all .vm files
	std::vector<std::filesystem::path> file_list = getFiles(argv[1]);

	if (file_list.empty())
	{
		std::cout << "No .vm files found. Exiting." << std::endl;
		return 0;
	}

	// After parsing command line parameter,
	// should have a vector of .vm files for translating
	std::cout << "files list: " << std::endl;
	for (auto const &vm_file : file_list)
		std::cout << vm_file << std::endl;
	std::cout << "end of list" << std::endl;

	// Construct parser and code generator
	Parser parser(file_list.front()); // just deal with one file for now
	CodeWriter writer(std::filesystem::path("output.asm"));
	Command command;

	// Clean each line of input file
	// Add real commands to instruction vector
	std::vector<std::string> commandList;

	while (parser.hasMoreCommands())
	{
		command.clear();
		command.setLine(parser.advance());

		if (parser.isCommand(command.getLine()))
		{
			command.setCommandType(parser.commandType(command.getLine()));
			command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));

			switch (command.getCommandType())
			{
			case C_ARITHMETIC:
				commandList.push_back("C_ARITHMETIC " + command.getArg1());
				writer.writeArithmetic(command.getArg1());
				break;
			case C_PUSH:
				command.setArg2(parser.arg2(command.getLine(), command.getCommandType()));
				commandList.push_back("C_PUSH " + command.getArg1() + " " + command.getArg2());
				writer.writePushPop(command.getCommandType(), command.getArg1(), command.getArg2());
				break;
			case ERROR:
				std::cout << "No valid command found - check vm file" << std::endl;
				return 0;
			default:
				std::cout << "default - no command recognised. Stopping." << std::endl;
				return 0;
			}
		}
	}

	// print the command list.
	std::cout << std::endl;
	for (const auto it : commandList)
		std::cout << it << std::endl;
	std::cout << std::endl;

	// Result of running this program will always be a single .asm file
	return 0;
}
