/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Symtab.h>
#include <Component.h>
#include <Terminal.h>
#include <Nonterminal.h>

std::vector<Component *> Symtab::getComponents() const
{
	return m_components;
}

Component* Symtab::getComponent(std::string name) const
{
	auto compare_component = [name](Component* comp) -> bool
	{
		return comp->getName() == name;
	};
	
	auto it = std::find_if(m_components.begin(), m_components.end(),
						   compare_component);

	if (it == m_components.end())
	{
		return nullptr;
	}
	
	return *it;
}

Terminal* Symtab::getTerminal(std::string name) const
{
	return dynamic_cast<Terminal *>(getComponent(name));
}

Nonterminal* Symtab::getNonterminal(std::string name) const
{
	return dynamic_cast<Nonterminal *>(getComponent(name));
}

Terminal* Symtab::addTerminal(std::string name)
{
	auto term = getTerminal(name);
	if (term != nullptr)
	{
		return term;
	}
	
	term = new Terminal(name);
	m_components.push_back(term);
	return term;
}

Nonterminal* Symtab::addNonterminal(std::string name)
{
	auto nonterm = getNonterminal(name);
	if (nonterm != nullptr)
	{
		return nonterm;
	}
	
	nonterm = new Nonterminal(name);
	m_components.push_back(nonterm);
	return nonterm;
}

Symtab::Symtab()
{
	// Do nothing.
}

Symtab::~Symtab()
{
	for (auto comp : m_components)
	{
		delete comp;
	}
}