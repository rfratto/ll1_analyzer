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
#include <Errors.h>
#include <Production.h>

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
			if (m_throw)
			{
				throw undefined_error(nonterm);
			}
			else
			{
				std::cerr << "error: nonterminal " << nonterm->getName() << " "
    			          << "used but has no production rules\n";
    			had_undefined = true;
			}
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

bool Analyzer::has_left_recursion()
{
	bool had_left_recursion = false;
	
	auto prod_sets = m_grammar->getProductions();
	for (auto pair : prod_sets)
	{
		auto nonterm = pair.first;
		auto cb = [nonterm](Production* prod, DerivationManager& mgr) -> bool
		{
			// If the production has at least one component and its first
			// component is us, it is directly left-recursive. Otherwise,
			// recurse on that first component.
			auto comps = prod->getComponents();
			if (comps.size() == 0)
			{
				return false;
			}
			
			auto comp = comps.at(0);
			if (comp == nonterm)
			{
				return true;
			}
			
			mgr.recurseOn(comp);
			
			return false;
		};
		
		if (nonterm->derives(m_grammar, nonterm, cb))
		{
			if (m_throw)
			{
				throw left_recursion_error(pair.first);
			}
			else
			{
				std::cerr << "error: nonterminal " << nonterm->getName() << " "
						  << "is left recursive.\n";
				had_left_recursion = true;
			}
		}
	}
	
	return had_left_recursion;
}

bool Analyzer::valid()
{
	bool has_error = has_undefined() || has_left_recursion();
	return has_error == false;
}

void Analyzer::setThrowExceptions(bool shouldThrow)
{
	m_throw = shouldThrow;
}

Analyzer::Analyzer(Grammar *g)
{
	if (g == nullptr)
	{
		throw std::invalid_argument("g must not be nullptr");
	}
	
	m_grammar = g;
}