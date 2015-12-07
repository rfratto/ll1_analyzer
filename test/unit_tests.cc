/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Grammar.h>
#include <Symtab.h>
#include <Analyzer.h>
#include <Errors.h>

#include <iostream>

Grammar* parseGrammar(const char* pathname)
{
	auto symtab = new Symtab();
	auto grammar = new Grammar(symtab);

	extern FILE* yyin;
	extern int yyparse(Grammar*);
	extern void yyflushbuffer();

	auto file = fopen(pathname, "r");
	if (file == nullptr)
	{
		std::cerr << "could not open " << pathname << " for reading\n";
		return nullptr;
	}

	yyflushbuffer();
	yyin = file;
	yyparse(grammar);

	fclose(file);
	return grammar;
}

int expectPass(const char* path)
{
	int retcode = 0;

	auto grammar = parseGrammar(path);

	Analyzer analyzer(grammar);

	try
	{
		if (analyzer.valid() == false)
		{
			retcode = 1;
		}
	}
	catch (std::exception& e)
	{
		retcode = 1;
	}

	delete grammar->getSymtab();
	delete grammar;

	return retcode;
}

template <typename T>
int getException(const char* path)
{
	int retcode = 1;

	auto grammar = parseGrammar(path);

	Analyzer analyzer(grammar);
	analyzer.setThrowExceptions(true);

	try
	{
		analyzer.valid();
	}
	catch (T& e)
	{
		retcode = 0;
	}
	catch (std::exception& e)
	{
		// Do nothing.
	}

	delete grammar->getSymtab();
	delete grammar;

	return retcode;
}

int main()
{
	int retcode = 0;

	if (getException<left_recursion_error>("grammars/left_recursive_2.y") == 1)
	{
		std::cerr << "failed: grammars/left_recursive_2.y\n";
		retcode = 1;
	}

	if (getException<left_recursion_error>("grammars/left_recursive_epsilon.y") == 1)
	{
		std::cerr << "failed: grammars/left_recursive_epsilon.y\n";
		retcode = 1;
	}

	if (getException<left_recursion_error>("grammars/left_recursive_indirect.y") == 1)
	{
		std::cerr << "failed: grammars/left_recursive_indirect.y\n";
		retcode = 1;
	}

	if (getException<left_recursion_error>("grammars/left_recursive.y") == 1)
	{
		std::cerr << "failed: grammars/left_recursive.y\n";
		retcode = 1;
	}

	if (getException<undefined_error>("grammars/undefined.y") == 1)
	{
		std::cerr << "failed: grammars/undefined.y\n";
		retcode = 1;
	}

	if (expectPass("grammars/unused.y") == 1)
	{
		std::cerr << "failed: grammars/unused.y\n";
		retcode = 1;
	}

	return retcode;
}
