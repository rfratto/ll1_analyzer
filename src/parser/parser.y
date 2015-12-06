/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	extern void yyerror(const char* s);
	extern int yylex();
%}

%start start

%token NONTERMINAL TERMINAL SEPARATOR SEMICOLON COLON EPSILON

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
	| TERMINAL
	;

%%
