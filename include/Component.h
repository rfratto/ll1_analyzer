/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include <string>

/**
 * Component is a base class for a symbol that is either a 
 * terminal or a nonterminal.
 */
class Component
{
private:
	std::string m_name;
public:
	/// Gets the name assigned to this component.
	std::string getName() const;

	/**
	 * Creates a new Component with a given name. The name must not be
	 * empty.
	 * @param name The name of this component.
	 */
	Component(std::string name);
	
	virtual ~Component();
};
