/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Component.h>
#include <stdexcept>
#include <algorithm>

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

std::vector<Terminal *> Component::getFirst() const
{
	return m_first;
}

bool Component::hasInFirst(Terminal *terminal) const
{
	auto it = std::find(m_first.begin(), m_first.end(), terminal);
	return it != m_first.end();
}

void Component::addToFirst(Terminal *terminal)
{
	if (hasInFirst(terminal))
	{
		return;
	}
	
	m_first.push_back(terminal);
}

void Component::appendToFirst(Component *component)
{
	auto component_first = component->getFirst();
	for (auto first : component_first)
	{
		addToFirst(first);
	}
}

Component::~Component()
{
	// Do nothing.
}