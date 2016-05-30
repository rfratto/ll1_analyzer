//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <string>
#include <ostream>
#include <sstream>
#include <gtest/gtest.h>
#include <lexer.h>

// Helper printing functions
namespace ast {
	std::ostream& operator<<(std::ostream& os, const ast::TokenType& ty) {
		switch (ty) {
			case TOKEN: return os << "TOKEN";
			case COLON: return os << "COLON";
			case BAR: return os << "BAR";
			case EPSILON: return os << "EPSILON";
			case SEMICOLON: return os << "SEMICOLON";
			case IDENTIFER: return os << "IDENTIFIER";
			case CONSTANT: return os << "CONSTANT";
			default: return os << ty;
		}
	}
}

bool tokensEq(ast::Token* a, ast::Token b) {
	return a->ty == b.ty && a->value == b.value;
}

void expectToken(ast::Lexer& l, ast::TokenType ty) {
	auto tok = l.readToken();
	EXPECT_EQ(tok->ty, ty);
}

void expectToken(ast::Lexer& l, std::string str) {
	auto tok = l.readToken();
	EXPECT_EQ(tok->value, str);
}

void expectToken(ast::Lexer& l, ast::Token tok) {
	EXPECT_TRUE(tokensEq(l.readToken(), tok));
}

#define TEST_TOKEN(test_case_name, test_name, input, ty) \
	TEST(test_case_name, test_name) {\
		std::stringstream ss(input); ast::Lexer l(ss);\
		EXPECT_FALSE(l.eof()); expectToken(l, ty);\
	}

#define TEST_TOKEN_VAL(test_case_name, test_name, input, ty) \
	TEST(test_case_name, test_name) {\
		std::stringstream ss(input); ast::Lexer l(ss);\
		EXPECT_FALSE(l.eof()); expectToken(l, ty);\
	}

/// Basic tests that only get one token
namespace BasicTests {
	using namespace ast;

	TEST(Lexer, EmptyInputTest) {
		std::stringstream ss("");
		Lexer l(ss);

		EXPECT_TRUE(l.eof());
		EXPECT_EQ(l.readToken(), nullptr);
	}

	TEST_TOKEN(LexerTokenTy, Token, "%token", TokenType::TOKEN);
	TEST_TOKEN(LexerTokenTy, Colon, ":", TokenType::COLON);
	TEST_TOKEN(LexerTokenTy, Bar, "|", TokenType::BAR);
	TEST_TOKEN(LexerTokenTy, Epsilon, "%epsilon", TokenType::EPSILON);
	TEST_TOKEN(LexerTokenTy, Semicolon, ";", TokenType::SEMICOLON);
	TEST_TOKEN(LexerTokenTy, Identifier, "hello_w0rld", TokenType::IDENTIFER);
	TEST_TOKEN(LexerTokenTy, Constant, "\"01234\\\"FOOBAR\\\"5678\"", TokenType::CONSTANT);

	TEST_TOKEN_VAL(LexerTokenVal, Identifier, "hello_w0rld", "hello_w0rld");
	TEST_TOKEN_VAL(LexerTokenVal, Constant, "\"01234\\\"FOOBAR\\\"5678\"",
	               "01234\\\"FOOBAR\\\"5678");
}
