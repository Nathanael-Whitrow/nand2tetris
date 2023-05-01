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
					file_list.push_back(dir_entry.path().filename());
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

	// Generate path for output file
	auto outputFileName = std::filesystem::absolute(file_list.front()).parent_path().stem().replace_extension(".asm");

	CodeWriter writer(outputFileName);
	Command command;

	// Clean each line of input file
	// Add real commands to instruction vector
	std::vector<std::string> commandList;

	// Counter for unique labelling
	uint unique_label_count = 0;
	std::string nameSpace = "sys";
	std::string delimiter = "$";

	// Set filename for static variables
	writer.setFileName(file_list.front());

	// Loop here for parsing multiple .vm files
	Parser parser(file_list.front()); // just deal with one file for now

	// Loops through one file
	while (parser.hasMoreCommands())
	{
		// Doesn't matter if we skip a few numbers, as long as we're unique.
		unique_label_count++;
		command.clear();
		command.setLine(parser.advance());

		if (parser.isCommand(command.getLine()))
		{
			command.setCommandType(parser.commandType(command.getLine()));

			switch (command.getCommandType())
			{
			case C_ARITHMETIC:
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				commandList.push_back("C_ARITHMETIC " + command.getArg1());
				writer.writeArithmetic(command.getArg1(), unique_label_count);
				break;

			case C_PUSH:
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				command.setArg2(parser.arg2(command.getLine(), command.getCommandType()));
				commandList.push_back("C_PUSH " + command.getArg1() + " " + command.getArg2());
				writer.writePushPop(command.getCommandType(), command.getArg1(), command.getArg2());
				break;

			case C_POP:
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				command.setArg2(parser.arg2(command.getLine(), command.getCommandType()));
				commandList.push_back("C_POP " + command.getArg1() + " " + command.getArg2());
				writer.writePushPop(command.getCommandType(), command.getArg1(), command.getArg2());
				break;

			case C_LABEL:
				// Can just hand the function name to the code writer
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				commandList.push_back("C_LABEL " + nameSpace + delimiter + command.getArg1());
				writer.writeLabel(nameSpace + delimiter + command.getArg1());
				break;

			case C_GOTO:
				// Hand the funciton name to the code writer
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				commandList.push_back("C_GOTO " + nameSpace + delimiter + command.getArg1());
				writer.writeGoTo(nameSpace + delimiter + command.getArg1());
				break;

			case C_IF:
				// Hand the function name to the code writer
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				commandList.push_back("C_IF " + nameSpace + delimiter + command.getArg1());
				writer.writeIf(nameSpace + delimiter + command.getArg1());
				break;

			case C_FUNCTION:
				// Set the function name
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				command.setArg2(parser.arg2(command.getLine(), command.getCommandType()));
				commandList.push_back("C_FUNCTION " + command.getArg1() + " " + command.getArg2());
				writer.writeFunction(command.getArg1(), std::stoi(command.getArg2()));
				nameSpace = command.getArg1();
				break;

			case C_RETURN:
				// Clear the function name
				writer.writeReturn();
				nameSpace = "sys";
				commandList.push_back("C_RETURN");
				break;

			case C_CALL:
				command.setArg1(parser.arg1(command.getLine(), command.getCommandType()));
				command.setArg2(parser.arg2(command.getLine(), command.getCommandType()));
				commandList.push_back("C_CALL " + command.getArg1() + " " + command.getArg2());
				writer.writeCall(command.getArg1(), unique_label_count, std::stoi(command.getArg2()));
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
