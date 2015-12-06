/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Component.h>

std::string Component::getName() const
{
	return m_name;
}

Component::Component(std::string name)
{
	if (name == "")
	{
		throw std::invalid_argument("A component cannot have an empty name");
	}
	
	m_name = name;
}