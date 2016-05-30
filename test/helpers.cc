//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include "helpers.h"

// Helper printing functions
namespace ast {
	std::ostream& operator<<(std::ostream& os, const ast::TokenType& ty) {
		switch (ty) {
			case TOKEN:
				return os << "TOKEN";
			case COLON:
				return os << "COLON";
			case BAR:
				return os << "BAR";
			case EPSILON:
				return os << "EPSILON";
			case SEMICOLON:
				return os << "SEMICOLON";
			case IDENTIFER:
				return os << "IDENTIFIER";
			case CONSTANT:
				return os << "CONSTANT";
			default:
				return os << ty;
		}
	}
}

using namespace ast;

template <>
bool tokensEq(Token* tok, Token to) { return tok->ty == to.ty && tok->value == to.value; }

template <>
bool tokensEq(Token* tok, TokenType ty) { return tok->ty == ty; }

template <>
bool tokensEq(Token* tok, std::string val) { return tok->value == val; }

template <>
bool tokensEq(Token* tok, const char* val) { return tok->value == val; }


template <>
void expectToken(ast::Lexer& l, Token val) {
	auto tok = l.readToken();
	EXPECT_EQ(tok->ty, val.ty);
	EXPECT_EQ(tok->value, val.value);
}

template <>
void expectToken(ast::Lexer& l, TokenType val) { EXPECT_EQ(l.readToken()->ty, val); }

template <>
void expectToken(ast::Lexer& l, std::string val) { EXPECT_EQ(l.readToken()->value, val); }

template <>
void expectToken(ast::Lexer& l, const char* val) { EXPECT_EQ(l.readToken()->value, val); }
