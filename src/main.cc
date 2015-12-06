/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <iostream>
#include <fstream>
#include <Grammar.h>
#include <Symtab.h>

bool file_exists(const char* pathname)
{
	bool exists = false;
	
	std::ifstream file(pathname);
	exists = file.is_open();
	file.close();
	
	return exists;
}

Grammar* parseGrammar(const char* pathname)
{
	// Verify path exists.
	if (file_exists(pathname) == false)
	{
		std::cerr << "could not open " << pathname << " for reading\n";
		return nullptr;
	}
	
	auto symtab = new Symtab();
	auto grammar = new Grammar(symtab);
	
	return grammar;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "usage: " << argv[0] << " [parser file]\n";
		return 1;
	}

	const char* pathname = argv[1];
	auto grammar = parseGrammar(pathname);
	if (grammar == nullptr)
	{
		return 1;
	}
	
	delete grammar->getSymtab();
	delete grammar;
	
	return 0;
}
