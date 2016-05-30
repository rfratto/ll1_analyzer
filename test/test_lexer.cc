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
#include "helpers.h"

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


	TEST_TOKEN(LexerTokenVal, Identifier, "hello_w0rld", "hello_w0rld");

	TEST_TOKEN(LexerTokenVal, Constant, "\"01234\\\"FOOBAR\\\"5678\"",
	               "01234\\\"FOOBAR\\\"5678");
}
