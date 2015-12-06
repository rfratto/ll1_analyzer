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
}

%start start

%token NONTERMINAL TERMINAL SEPARATOR SEMICOLON COLON EPSILON

%type <str> NONTERMINAL TERMINAL

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
	;

rule_list
	: rule_list SEPARATOR rule
	| rule
	;

/* A rule is a string of nonterminals and terminals or a single epsilon */
rule
	: rule_composition
	| EPSILON
	;

rule_composition
	: rule_composition component
	| component
	;

component
	: NONTERMINAL
	{
		grammar->getSymtab()->addNonterminal($1);
	}
	| TERMINAL
	{
		grammar->getSymtab()->addTerminal($1);
	}
	;

%%
