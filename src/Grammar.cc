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

Grammar::Grammar(Symtab* symbolTable)
{
	if (symbolTable == nullptr)
	{
		throw std::invalid_argument("symbolTable cannot be nullptr");
	}
	
	m_symbol_table = symbolTable;
}