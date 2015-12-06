/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <vector>

class Component;

class Production
{
private:
	std::vector<Component *> m_components;
public:
	std::vector<Component *> getComponents() const;
	
	Production(std::vector<Component *> components);
};