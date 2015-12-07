/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Grammar.h>
#include <Production.h>
#include <Nonterminal.h>
#include <Symtab.h>
#include <Epsilon.h>

Symtab* Grammar::getSymtab() const
{
	return m_symbol_table;
}

ProductionSet Grammar::getProductions() const
{
	return m_productions;
}

bool Grammar::hasProductions(Nonterminal *nonterminal) const
{
	typedef std::pair<Nonterminal*, std::vector<Production*>> pair;
	auto comp_terminal = [nonterminal](pair p) -> bool
	{
		return p.first == nonterminal;
	};
	
	auto it = std::find_if(m_productions.begin(), m_productions.end(),
						   comp_terminal);
	
	return it != m_productions.end();
}

std::vector<Production* > Grammar::getProductions(Nonterminal *nonterminal)
const
{
	typedef std::pair<Nonterminal*, std::vector<Production*>> pair;
	auto comp_terminal = [nonterminal](pair p) -> bool
	{
		return p.first == nonterminal;
	};
	
	auto it = std::find_if(m_productions.begin(), m_productions.end(),
						   comp_terminal);
	
	if (it == m_productions.end())
	{
		return std::vector<Production *>();
	}
	
	return it->second;
}

void Grammar::addProduction(Nonterminal *nonterminal, Production *production)
{
	if (m_productions.size() == 0)
	{
		m_start = nonterminal;
	}
	
	typedef std::pair<Nonterminal*, std::vector<Production*>> pair;
	auto comp_terminal = [nonterminal](pair p) -> bool
	{
		return p.first == nonterminal;
	};
	
	auto it = std::find_if(m_productions.begin(), m_productions.end(),
						   comp_terminal);
	
	if (it == m_productions.end())
	{
		m_productions[nonterminal] = std::vector<Production *>();
		m_productions[nonterminal].push_back(production);
	}
	else
	{
		it->second.push_back(production);
	}
}

Nonterminal* Grammar::getStart() const
{
	return m_start;
}

void Grammar::computeFirst(Nonterminal *nonterm)
{
	auto it = std::find(m_computed_first.begin(), m_computed_first.end(),
						nonterm);
	if (it != m_computed_first.end())
	{
		return;
	}
	
	m_computed_first.push_back(nonterm);
	
	auto prods = getProductions(nonterm);
	for (auto prod : prods)
	{
		auto components = prod->getComponents();
		for (unsigned int i = 0; i < components.size(); i++)
		{
			auto comp = components.at(i);
			auto nt_comp = dynamic_cast<Nonterminal *>(comp);
			
			if (nt_comp != nullptr)
			{
				computeFirst(nt_comp);
			}
			
			// Add FIRST(comp) to FIRST(nonterm)
			nonterm->appendToFirst(comp);
			
			// If FIRST(comp) doesn't contain Epsilon, then
			// exit the loop.
			if (comp->hasInFirst(getSymtab()->getEpsilon()) == false)
			{
				break;
			}
		}
	}
}

void Grammar::computeFirst()
{
	auto prod_set = getProductions();
	for (auto pair : prod_set)
	{
		computeFirst(pair.first);
	}
}

Grammar::Grammar(Symtab* symbolTable)
{
	if (symbolTable == nullptr)
	{
		throw std::invalid_argument("symbolTable cannot be nullptr");
	}
	
	m_symbol_table = symbolTable;
}

Grammar::~Grammar()
{
	for (auto pair : m_productions)
	{
		for (auto prod : pair.second)
		{
			delete prod;
		}
	}
}