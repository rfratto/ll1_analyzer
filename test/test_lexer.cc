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

	TEST(Lexer, LexesWhiteSpace) {
		std::stringstream ss("                 \
			                     ");
		Lexer l(ss);

		EXPECT_FALSE(l.eof());
		EXPECT_EQ(l.readToken(), nullptr);
	}

	TEST_TOKEN(Lexer, LexesToken, "%token", TokenType::TOKEN);

	TEST_TOKEN(Lexer, LexesColon, ":", TokenType::COLON);

	TEST_TOKEN(Lexer, LexesBar, "|", TokenType::BAR);

	TEST_TOKEN(Lexer, LexesEpsilon, "%epsilon", TokenType::EPSILON);

	TEST_TOKEN(Lexer, LexesSemicolon, ";", TokenType::SEMICOLON);

	TEST_TOKEN(Lexer, LexesIdentifier, "hello_w0rld",
	           Token(TokenType::IDENTIFER, "hello_w0rld"));

	TEST_TOKEN(Lexer, LexesConstant, "\"01234\\\"FOOBAR\\\"5678\"",
	           Token(TokenType::CONSTANT, "01234\\\"FOOBAR\\\"5678"));
}

TEST(Lexer, LexesStream) {
	using namespace ast;

	std::stringstream ss(R"(
		%token %epsilon HELLO_WORLD1234
"const string""const"
			"const!?@";;||;| | ;
	)");

	Lexer l(ss);

	std::vector<TokenType> expects = {
		TOKEN, EPSILON, IDENTIFER, CONSTANT, CONSTANT, CONSTANT,
		SEMICOLON, SEMICOLON, BAR, BAR, SEMICOLON, BAR,
	    BAR, SEMICOLON
	};

	while (expects.size() > 0) {
		auto token = expects.front();
		expectToken(l, token);

		expects.erase(expects.begin());
	}
}

TEST(Lexer, ThrowsExceptionOnBadToken) {
	std::vector<std::string> badInputs = {
		"%tokenbad", "@", "!", "?"
	};

	while (badInputs.size() > 0) {
		auto input = badInputs.back();

		std::stringstream ss(input);
		ast::Lexer l(ss);

		EXPECT_THROW(l.readToken(), std::runtime_error);

		badInputs.pop_back();
	}
}