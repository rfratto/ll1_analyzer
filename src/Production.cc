/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Production.h>
#include <Nonterminal.h>
#include <Grammar.h>

std::vector<Component *> Production::getComponents() const
{
	return m_components;
}

bool Production::derives(Grammar *grammar, Component *component,
						 DerivationCallback cb)
{
	DerivationManager mgr;
	
	std::vector<Production *> searched;
	searched.push_back(this);
	
	// Call our callback to see if this production
	// has the derivation we want.
	if (cb(this, component, mgr) == true)
	{
		return true;
	}

	// If it didn't return true, use our DerivationManager
	// to see what rules to search next.
	while (mgr.hasNext())
	{
		// Get the next nonterminal and get its productions.
		auto nonterm = mgr.getNext();
		auto prods = grammar->getProductions(nonterm);
		
		for (auto prod : prods)
		{
			// If we've already searched the production,
			// skip it.
			auto it = std::find(searched.begin(), searched.end(), prod);
			if (it != searched.end())
			{
				continue;
			}
			
			// Add it to the list.
			searched.push_back(prod);
			
			// Do a recursive search on that production.
			if (cb(prod, component, mgr) == true)
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Production::derives(Grammar *grammar, Component *component)
{
	auto cb = [](Production* prod, Component* component,
						  DerivationManager& mgr) -> bool
	{
		auto comps = prod->getComponents();
		for (auto comp : comps)
		{
			if (comp == component)
			{
				return true;
			}
			
			mgr.recurseOn(comp);
		}
		
		return false;
	};
	
	return derives(grammar, component, cb);
}

Production::Production(std::vector<Component *> components)
{
	m_components = components;
	
	// For each of our nonterminals, add this as a reference.
	for (auto component : components)
	{
		auto nonterm = dynamic_cast<Nonterminal *>(component);
		if (nonterm == nullptr)
		{
			continue;
		}
		
		nonterm->addReference(this);
	}
}