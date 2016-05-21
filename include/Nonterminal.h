/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once

#include "Component.h"
#include "Production.h"

#include <vector>

class Nonterminal : public Component
{
private:
	std::vector<Production *> m_references;
public:
	std::vector<Production *> getReferences() const;
	
	/// Checks all productions of this non terminal to see if they derive
	/// a certain component. Returns the component that is housing it if it exists.
	Component* derives(Grammar* grammar, Component* component);
	Component* derives(Grammar* grammar, Component* component, DerivationCallback cb);
	
	void addReference(Production* reference);
	
	Nonterminal(std::string name);
};