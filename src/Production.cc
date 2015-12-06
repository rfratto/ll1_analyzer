/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Production.h>
#include <Nonterminal.h>

std::vector<Component *> Production::getComponents() const
{
	return m_components;
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