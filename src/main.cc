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
#include <Nonterminal.h>
#include <Terminal.h>

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

void analyzeGrammar(Grammar* grammar)
{
	const unsigned int START_LENGTH = 0;
	const unsigned int TAB_SIZE = 4;
	
	unsigned int line_length = START_LENGTH + TAB_SIZE;
	
	auto termlist = grammar->getSymtab()->getTerminals();
	auto nontermlist = grammar->getSymtab()->getNonterminals();
	
	std::cout << "Terminals:\n\t";
	for (unsigned int i = 0; i < termlist.size(); i++)
	{
		std::cout << termlist.at(i)->getName();
		line_length += termlist.at(i)->getName().length();
		
		if (i + 1 < termlist.size())
		{
			std::cout << ", ";
			line_length += 2;
		}
		
		
		if (line_length > 40)
		{
			std::cout << "\n\t";
			line_length = START_LENGTH + TAB_SIZE;
		}
	}
	
	std::cout << "\n";
	
	line_length = START_LENGTH + TAB_SIZE;
	
	std::cout << "Nonterminals:\n\t";
	for (unsigned int i = 0; i < nontermlist.size(); i++)
	{
		std::cout << nontermlist.at(i)->getName();
		line_length += nontermlist.at(i)->getName().length();
		
		if (i + 1 < nontermlist.size())
		{
			std::cout << ", ";
			line_length += 2;
		}
		
		if (line_length > 40)
		{
			std::cout << "\n\t";
			line_length = START_LENGTH + TAB_SIZE;
		}
	}
	
	std::cout << "\n";
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
	
	analyzeGrammar(grammar);
	
	delete grammar->getSymtab();
	delete grammar;
	
	return 0;
}
