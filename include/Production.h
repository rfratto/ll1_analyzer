/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <vector>
#include <functional>

#include "DerivationManager.h"

class Component;
class Grammar;
class Production;

typedef std::function<bool(Production*,Component*,DerivationManager&)>
	DerivationCallback;

class Production
{
private:
	std::vector<Component *> m_components;
public:
	std::vector<Component *> getComponents() const;
	
	/// Returns the component where a derivation exists from this
	/// production, in some number of transitions, to a specific component.
	Component* derives(Grammar* grammar, Component* component);
	Component* derives(Grammar* grammar, Component* component, DerivationCallback cb);
	
	Production(std::vector<Component *> components);
};