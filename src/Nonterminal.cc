/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <Nonterminal.h>

std::vector<Production *> Nonterminal::getReferences() const
{
	return m_references;
}

void Nonterminal::addReference(Production *reference)
{
	m_references.push_back(reference);
}

Nonterminal::Nonterminal(std::string name)
: Component(name)
{
	// Do nothing.
}
