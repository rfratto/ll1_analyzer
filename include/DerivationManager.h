/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <vector>

class Nonterminal;
class Component;

class DerivationManager
{
private:
	std::vector<Nonterminal *> m_recurse_list;
	std::vector<Nonterminal *> m_recursed;
public:
	bool hasNext() const;
	Nonterminal* getNext();
	
	void recurseOn(Component* component);
};