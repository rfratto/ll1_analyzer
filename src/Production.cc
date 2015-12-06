/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Production.h>

std::vector<Component *> Production::getComponents() const
{
	return m_components;
}

Production::Production(std::vector<Component *> components)
{
	m_components = components;
}