//
// A virtual machine translator
// by Nathanael Whitrow

#include <iostream>
#include <filesystem>

int main(const int argc, const char *argv[])
{
	std::cout << "IR_asm translator online." << std::endl;

	// Accept one command line parameter
	// --> VMTranslator.out source
	// where source is either:
	//	a file name of the form Xxx.vm
	//	a directory name containing one or more .vm files
	if (argc != 2)
	{
		std::cout << "IR_asm takes one parameter: a target file or directory" << std::endl;
		return 0;
	}

	// Vector for holding all .vm files
	std::vector<std::filesystem::path> file_list;

	// Assume we have a path
	auto path = std::filesystem::path(argv[1]);

	// Search whole directory for .vm
	if (std::filesystem::is_directory(path))
	{
		// we have a folder, find all .vm files and add to vector
		for (auto const &dir_entry : std::filesystem::directory_iterator{path})
			if (dir_entry.path().has_extension())
				if (dir_entry.path().extension() == ".vm")
					file_list.push_back(dir_entry.path());

		if (file_list.empty())
		{
			std::cout << "No .vm files found. Exiting." << std::endl;
			return 0;
		}
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

	// After parsing input, should have a vector of .vm files for translating
	for (auto const &vm_file : file_list)
		std::cout << vm_file << std::endl;

	// Result of running this program will always be a single .asm file
	return 0;
}
