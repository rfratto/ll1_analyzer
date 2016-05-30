//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <istream>
#include <string>

///
/// lexer regex
///
/// token -> "%token"
/// colon -> ":"
/// bar -> "|"
/// epsilon -> "%epsilon"
/// semicolon -> ";"
/// identifier -> [A-Za-z][A-Za-z0-9_]*
/// constant -> \"(\\.|[^\\"])*\"
/// whitespace -> [\ \t\r\n]
/// comment -> "//"[^\r\n]*
/// block_comment -> "/*"   { consume until matching */ }
///

namespace ast {
	enum TokenType {
		TOKEN, COLON, BAR, EPSILON, SEMICOLON,
		IDENTIFER, CONSTANT
	};

	class Token {
	public:
		TokenType ty;
		std::string value;

		Token() { }

		Token(TokenType ty, std::string v) : ty(ty), value(v) { }
	};

	class Lexer {
	private:
		std::istream& mStream;

		Token* readKeyword();
		Token* readIdentifier();
		Token* readConstant();

		void consumeComment();
	public:
		/// Reads the next token from the stream.
		/// Returns nullptr on EOF.
		Token* readToken();

		/// Returns whether or not we're at the end of file.
		bool eof() const;

		Lexer(std::istream& stream);
	};
}