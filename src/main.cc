/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#include <iostream>
#include <fstream>

bool file_exists(const char* pathname)
{
	bool exists = false;
	
	std::ifstream file(pathname);
	exists = file.is_open();
	file.close();
	
	return exists;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cerr << "usage: " << argv[0] << " [parser file]\n";
		return 1;
	}
	
	// Verify path exists.
	const char* pathname = argv[1];
	if (file_exists(pathname) == false)
	{
		std::cerr << "could not open " << pathname << " for reading\n";
		return 1;
	}
	
	return 0;
}
