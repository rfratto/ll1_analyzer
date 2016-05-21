/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Errors.h>
#include <Component.h>

#include <sstream>

const char* base_error::what() const noexcept
{
	return m_error.c_str();
}

left_recursion_error::left_recursion_error(Component* component,
										   Component* from)
{
	std::stringstream ss;
	ss << "error: nonterminal " << component->getName()
	   << " is left-recursive (from " << from->getName() << ")";
	m_error = ss.str();
}

undefined_error::undefined_error(Component* component)
{
	std::stringstream ss;
	ss << "error: nonterminal " << component->getName()
	   << " is used but has no production rules";
	m_error = ss.str();
}