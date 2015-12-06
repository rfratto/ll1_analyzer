/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <map>
#include <vector>

class Production;
class Nonterminal;
class Symtab;

typedef std::map<Nonterminal*, std::vector<Production*>> ProductionSet;

/**
 * A Grammar defines a list of productions for nonterminals.
 * Rules can be looked up by searching for a terminal by name.
 */
class Grammar
{
private:
	ProductionSet m_productions;
	Symtab* m_symbol_table;
public:
	Symtab* getSymtab() const;
	
	/// Gets all productions.
	ProductionSet getProductions() const;
	
	/// Returns whether or not a nonterminal has defined productions.
	bool hasProductions(Nonterminal* nonterminal) const;
	
	/// Gets all productions for a given nonterminal.
	std::vector<Production *> getProductions(Nonterminal* nonterminal) const;
	
	/// Adds a production rule for a given nonterminal.
	void addProduction(Nonterminal* nonterminal, Production* production);
	
	Grammar(Symtab* symbolTable);
	~Grammar();
};