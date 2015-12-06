/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <Grammar.h>
	#include <Component.h>
	#include "parser.hh"

	#define YY_DECL int yylex(Grammar* grammar)
	void yyflushbuffer() { YY_FLUSH_BUFFER; }

	extern void yyerror(Grammar*,const char*);
%}

%option noyywrap
%option nounistd
%option never-interactive
%option nounput
%option noinput

%%

[\ \t\r\n]			;

"$"                 return EPSILON;
":"                 return COLON;
";"                 return SEMICOLON;
"|"                 return SEPARATOR;

[a-z][a-z0-9_']*    yylval.str = yytext; return NONTERMINAL;
[A-Z][A-Z0-9_]*     yylval.str = yytext; return TERMINAL;
\"(\\.|[^\\"])*\"   yylval.str = yytext; return TERMINAL;

.                   yyerror(grammar, "invalid token");

%%
