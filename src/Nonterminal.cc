/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Nonterminal.h>
#include <Grammar.h>

std::vector<Production *> Nonterminal::getReferences() const
{
	return m_references;
}

void Nonterminal::addReference(Production *reference)
{
	m_references.push_back(reference);
}

bool Nonterminal::derives(Grammar *grammar, Component *component)
{
	auto prods = grammar->getProductions(this);
	for (auto prod : prods)
	{
		if (prod->derives(grammar, component) == true)
		{
			return true;
		}
	}
	
	return false;
}

bool Nonterminal::derives(Grammar *grammar, Component *component,
						  DerivationCallback cb)
{
	auto prods = grammar->getProductions(this);
	for (auto prod : prods)
	{
		if (prod->derives(grammar, component, cb) == true)
		{
			return true;
		}
	}
	
	return false;
}

Nonterminal::Nonterminal(std::string name)
: Component(name)
{
	// Do nothing.
}
