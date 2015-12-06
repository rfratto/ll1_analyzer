/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <Grammar.h>
	#include <Symtab.h>
	#include <Component.h>
	#include <Production.h>

	#include <sstream>

	extern void yyerror(Grammar* grammar, const char* s);
	extern int yylex(Grammar* grammar);
%}

%error-verbose
%lex-param { Grammar* grammar }
%parse-param { Grammar* grammar }

%union {
	int i;
	const char* str;
	std::vector<Production *>* production_list;
	std::vector<Component *>* component_list;
	Component* component;
}

%start start

%token NONTERMINAL TERMINAL SEPARATOR SEMICOLON COLON EPSILON

%type <str> NONTERMINAL TERMINAL
%type <component_list> rule rule_composition
%type <production_list> rule_list
%type <component> component

%%

start
	: production_rules
	;

production_rules
	: production_rules production_rule
	|
	;

production_rule
	: NONTERMINAL COLON rule_list SEMICOLON
	{
		auto nonterm = grammar->getSymtab()->addNonterminal($1);
		for (auto prod : *$3)
		{
			grammar->addProduction(nonterm, prod);
		}

		delete $3;
	}
	;

rule_list
	: rule_list SEPARATOR rule
	{
		auto prod = new Production(*$3);
		$$ = $1;
		$$->push_back(prod);

		delete $3;
	}
	| rule
	{
		auto prod = new Production(*$1);
		$$ = new std::vector<Production *>();
		$$->push_back(prod);

		delete $1;
	}
	;

/* A rule is a string of nonterminals and terminals or a single epsilon */
rule
	: rule_composition { $$ = $1; }
	| EPSILON { $$ = new std::vector<Component* >(); }
	;

rule_composition
	: rule_composition component { $$ = $1; $$->push_back($2); }
	| component { $$ = new std::vector<Component *>(); $$->push_back($1); }
	;

component
	: NONTERMINAL
	{
		$$ = (Component *)grammar->getSymtab()->addNonterminal($1);
	}
	| TERMINAL
	{
		$$ = (Component *)grammar->getSymtab()->addTerminal($1);
	}
	;

%%
