/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Analyzer.h>
#include <Grammar.h>
#include <Symtab.h>
#include <Nonterminal.h>
#include <Terminal.h>

#include <iostream>

bool Analyzer::has_undefined()
{
	bool had_undefined = false;
	
	auto termlist = m_grammar->getSymtab()->getTerminals();
	auto nontermlist = m_grammar->getSymtab()->getNonterminals();
	
	for (auto nonterm : nontermlist)
	{
		if (m_grammar->hasProductions(nonterm) == false)
		{
			std::cerr << "error: nonterminal " << nonterm->getName() << " "
			<< "used but has no production rules\n";
			had_undefined = true;
		}
		
		if (nonterm->getReferences().size() == 0 &&
			m_grammar->getStart() != nonterm)
		{
			std::cerr << "warning: nonterminal " << nonterm->getName() << " "
			<< "defined but is not used\n";
		}
	}
	
	return had_undefined;
}

bool Analyzer::valid()
{
	bool has_error = has_undefined();
	return has_error == false;
}

Analyzer::Analyzer(Grammar *g)
{
	if (g == nullptr)
	{
		throw std::invalid_argument("g must not be nullptr");
	}
	
	m_grammar = g;
}