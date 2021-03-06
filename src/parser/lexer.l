/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

%{
	#include <Grammar.h>
	#include <Component.h>
	#include "parser.hh"

	#define SAVE_STR() yylval.str = new std::string(yytext, yyleng);

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

[a-z][a-z0-9_']*    SAVE_STR(); return NONTERMINAL;
[A-Z][A-Z0-9_]*     SAVE_STR(); return TERMINAL;
\"(\\.|[^\\"])*\"   SAVE_STR(); return TERMINAL;

.                   yyerror(grammar, "invalid token");

%%
