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
#include <Epsilon.h>

std::vector<Component *> Symtab::getComponents() const
{
	return m_components;
}

std::vector<Terminal *> Symtab::getTerminals() const
{
	std::vector<Terminal *> termlist;
	
	for (auto comp : m_components)
	{
		if (dynamic_cast<Terminal *>(comp) == nullptr)
		{
			continue;
		}
		
		termlist.push_back((Terminal *)comp);
	}
	
	return termlist;
}

std::vector<Nonterminal *> Symtab::getNonterminals() const
{
	std::vector<Nonterminal *> nontermlist;
	
	for (auto comp : m_components)
	{
		if (dynamic_cast<Nonterminal *>(comp) == nullptr)
		{
			continue;
		}
		
		nontermlist.push_back((Nonterminal *)comp);
	}
	
	return nontermlist;
}

Epsilon* Symtab::getEpsilon() const
{
	return dynamic_cast<Epsilon *>(getComponent("$"));
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
	m_components.push_back(new Epsilon());
}

Symtab::~Symtab()
{
	for (auto comp : m_components)
	{
		delete comp;
	}
}