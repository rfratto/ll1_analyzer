/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <DerivationManager.h>
#include <Nonterminal.h>

bool DerivationManager::hasNext() const
{
	return m_recurse_list.size() > 0;
}

Nonterminal* DerivationManager::getNext()
{
	if (hasNext() == false)
	{
		return nullptr;
	}
	
	auto ret = m_recurse_list.back();
	m_recurse_list.pop_back();
	return ret;
}

void DerivationManager::recurseOn(Component *component)
{
	auto nonterm = dynamic_cast<Nonterminal *>(component);
	if (nonterm != nullptr)
	{
		auto it = std::find(m_recursed.begin(), m_recursed.end(), nonterm);
		if (it != m_recursed.end())
		{
			return;
		}
		
		m_recurse_list.push_back(nonterm);
		m_recursed.push_back(nonterm);
	}
}