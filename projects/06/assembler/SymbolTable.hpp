#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

#include <unordered_map>

class SymbolTable
{
public:
	SymbolTable()
	{
		symbolTable = {	{"SP",		"0"		},
						{"LCL",		"1"		},
						{"ARG",		"2"		},
						{"THIS",	"3"		},
						{"THAT",	"4"		},
						{"R0", 		"0"		},
						{"R1", 		"1"		},
						{"R2", 		"2"		},
						{"R3", 		"3"		},
						{"R4", 		"4"		},
						{"R5", 		"5"		},
						{"R6", 		"6"		},
						{"R7", 		"7"		},
						{"R8", 		"8"		},
						{"R9", 		"9"		},
						{"R10",		"10"	},
						{"R11",		"11"	},
						{"R12",		"12"	},
						{"R13",		"13"	},
						{"R14",		"14"	},
						{"R15",		"15"	},
						{"SCREEN",	"16384" },
						{"KBD",		"24576"	} 	};
	}

	~SymbolTable() {}

	// Returns true if the entry isn't already in the symbol table
	void addEntry (std::string symbol, std::string address)
	{
		symbolTable[symbol] = address;
	}

	bool contains (std::string symbol)
	{
		auto it = symbolTable.find(symbol);
		if (it != symbolTable.end())
			return true;
		else
			return false;
	}

	std::string getAddress(std::string symbol)
	{
		return symbolTable[symbol];
	}

	void printTable()
	{
		for (const auto& it : symbolTable)
		{
			std::cout << it.first << " == " << it.second << std::endl;
		}
	}

private:
	std::unordered_map<std::string, std::string> symbolTable;

};

#endif // SYMBOL_TABLE_HPP