/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>
#include <vector>

class Terminal;

/**
 * Component is a base class for a symbol that is either a 
 * terminal or a nonterminal.
 */
class Component
{
private:
	std::string m_name;
	
	std::vector<Terminal *> m_first;
public:
	/// Gets the name assigned to this component.
	std::string getName() const;
	
	std::vector<Terminal* > getFirst() const;
	
	/// Determines if a terminal already exists in first.
	bool hasInFirst(Terminal* terminal) const;
	
	/// Adds a terminal to FIRST, if it didn't already exist.
	void addToFirst(Terminal* terminal);
	
	/// Appends FIRST(component) to FIRST for elements FIRST(this)
	/// doesn't already have.
	void appendToFirst(Component* component);

	/**
	 * Creates a new Component with a given name. The name must not be
	 * empty.
	 * @param name The name of this component.
	 */
	Component(std::string name);
	
	virtual ~Component();
};
