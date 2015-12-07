/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

class Grammar;

/**
 * Analyzer accepts a grammar and provides
 * a method to determine whether or not that grammar is valid.
 */
class Analyzer
{
private:
	Grammar* m_grammar;
 
	bool m_throw = false;
	
 	bool has_undefined();
	bool has_left_recursion();
public:
	bool valid();
	
	void setThrowExceptions(bool shouldThrow);
	
	Analyzer(Grammar* g);
};