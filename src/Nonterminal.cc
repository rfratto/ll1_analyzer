/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
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

Component* Nonterminal::derives(Grammar *grammar, Component *component)
{
	auto prods = grammar->getProductions(this);
	for (auto prod : prods)
	{
		auto ret = prod->derives(grammar, component);
		if (ret != nullptr)
		{
			return ret;
		}
	}
	
	return nullptr;
}

Component* Nonterminal::derives(Grammar *grammar, Component *component,
								DerivationCallback cb)
{
	auto prods = grammar->getProductions(this);
	for (auto prod : prods)
	{
		auto ret = prod->derives(grammar, component, cb);
		if (ret != nullptr)
		{
			return ret;
		}
	}
	
	return nullptr;
}

Nonterminal::Nonterminal(std::string name)
: Component(name)
{
	// Do nothing.
}
