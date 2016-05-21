/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <vector>
#include <string>

class Component;
class Terminal;
class Nonterminal;
class Epsilon;

/**
 * The symbol table contains a list of components that can be looked 
 * up by name. 
 * The components are not sorted and lookup takes O(n) time.
 */
class Symtab
{
private:
	std::vector<Component *> m_components;
public:
	/// Gets all components in the symbol table.
	std::vector<Component *> getComponents() const;
	
	/// Gets all nonterminals in the symbol table.
	std::vector<Terminal *> getTerminals() const;
	
	/// Gets all terminals in the symbol table.
	std::vector<Nonterminal *> getNonterminals() const;
	
	/// Gets epsilon.
	Epsilon* getEpsilon() const;
	
	/// Gets a component by a given name, if one exists.
	Component* getComponent(std::string name) const;
	
	/// Gets a terminal by a given name, if one exists.
	Terminal* getTerminal(std::string name) const;
	
	/// Gets a nonterminal by a given name, if one exists.
	Nonterminal* getNonterminal(std::string name) const;
	
	/// Adds a terminal by a given name. Does nothing if one already exists.
	/// @return Returns a terminal with a given name.
	Terminal* addTerminal(std::string name);
	
	/// Adds a nonterminal by a given name. Does nothing if one already exists.
	/// @return Returns a nonterminal with a given name.
	Nonterminal* addNonterminal(std::string name);
	
	Symtab();
	~Symtab();
};