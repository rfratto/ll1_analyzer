/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Component.h"

#include <vector>

class Production;

class Nonterminal : public Component
{
private:
	std::vector<Production *> m_references;
public:
	std::vector<Production *> getReferences() const;
	
	void addReference(Production* reference);
	
	Nonterminal(std::string name);
};