#ifndef CODE_HPP
#define CODE_HPP

#include <fstream>
#include <iostream>
#include <string>

class Code
{
public:
	Code(std::string assemblyFile)
	{
		// build output file name
		std::string binaryFile = assemblyFile.substr(0, assemblyFile.find('.'));
		binaryFile.append(".hack");
		fileWriter.open(binaryFile, std::fstream::out);
	}
	
	~Code() { fileWriter.close(); }

	// return binary of immediate
	std::string getImmediateBinary(std::string& line)
	{
		// convert to string which represents binary
		int num = std::stoi(line);
		std::bitset<15> bits(num);
		std::string binary = bits.to_string();
		return binary.insert(0, "0");
	}


	// returns the binary of the dest mnemonic
	std::string getDestBinary(std::string& mnemonic)
	{
		std::string dest = "000";
		if (mnemonic.find('A') != std::string::npos) 	{ dest[0] = '1'; }
		if (mnemonic.find('D') != std::string::npos)	{ dest[1] = '1'; }
		if (mnemonic.find('M') != std::string::npos)	{ dest[2] = '1'; }
		return dest;
	}

	// Return the 'a' bit (memory bit) concatenated with
	// the 6 digit binary to control the ALU
	std::string getCompBinary(std::string& mnemonic)
	{
		if      (mnemonic == "0"  )	{ return "0101010"; }
		else if (mnemonic == "1"  )	{ return "0111111"; }
		else if (mnemonic == "-1" )	{ return "0111010"; }
		else if (mnemonic == "D"  )	{ return "0001100"; }
		else if (mnemonic == "A"  )	{ return "0110000"; }
		else if (mnemonic == "M"  )	{ return "1110000"; }
		else if (mnemonic == "!D" )	{ return "0001101"; }
		else if (mnemonic == "!A" )	{ return "0110001"; }
		else if (mnemonic == "!M" )	{ return "1110001"; }
		else if (mnemonic == "-D" )	{ return "0001111"; }
		else if (mnemonic == "-A" )	{ return "0110011"; }
		else if (mnemonic == "D+1")	{ return "0011111"; }
		else if (mnemonic == "A+1")	{ return "0110111"; }
		else if (mnemonic == "M+1")	{ return "1110111"; }
		else if (mnemonic == "D-1")	{ return "0001110"; }
		else if (mnemonic == "A-1")	{ return "0110010"; }
		else if (mnemonic == "M-1")	{ return "1110010"; }
		else if (mnemonic == "D+A")	{ return "0000010"; }
		else if (mnemonic == "D+M")	{ return "1000010"; }
		else if (mnemonic == "D-A")	{ return "0010011"; }
		else if (mnemonic == "D-M")	{ return "1010011"; }
		else if (mnemonic == "A-D")	{ return "0000111"; }
		else if (mnemonic == "M-D")	{ return "1000111"; }
		else if (mnemonic == "D&A")	{ return "0000000"; }
		else if (mnemonic == "D&M")	{ return "1000000"; }
		else if (mnemonic == "D|A")	{ return "0010101"; }
		else if (mnemonic == "D|M")	{ return "1010101"; }
		else						{ return ""       ;	}
	}

	std::string getJumpBinary(std::string& mnemonic)
	{
		if 		(mnemonic == "JGT")	{ return "001"; }
		else if (mnemonic == "JEQ")	{ return "010"; }
		else if (mnemonic == "JGE")	{ return "011"; }
		else if (mnemonic == "JLT")	{ return "100"; }
		else if (mnemonic == "JNE")	{ return "101"; }
		else if (mnemonic == "JLE")	{ return "110"; }
		else if (mnemonic == "JMP")	{ return "111"; }
		else						{ return "000"; }
	}

	// This module also writes assembly to file
	void putLine(std::string& line)
	{
		fileWriter << line << std::endl;
	}


private:
	std::fstream fileWriter;
};

#endif