//
// A virtual machine translator
// by Nathanael Whitrow

#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "Venomous translator online with arguments:" << std::endl;
	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}

	return 0;
}
