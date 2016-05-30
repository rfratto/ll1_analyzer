//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <cctype>
#include "lexer.h"

using namespace ast;


static char peekChar(std::istream& s) {
	return std::istream::traits_type::to_char_type(s.peek());
}

static char getChar(std::istream& s) {
	return std::istream::traits_type::to_char_type(s.get());
}

static std::string str(char c) { return std::string(1, c); }

Lexer::Lexer(std::istream &stream) : mStream(stream) { }

void Lexer::consumeComment() {
	auto pos = mStream.tellg();

	if (getChar(mStream) != '/') {
		mStream.seekg(pos, mStream.beg);
		return;
	}

	if (peekChar(mStream) == '/') {
		// One-line comment
		getChar(mStream);
		while (!eof() && peekChar(mStream) != '\n') getChar(mStream);
	} else if (peekChar(mStream) == '*') {
		// Block comment
		getChar(mStream);

		int count = 1;

		char last_char = 0;
		while (!eof() && count > 0) {
			char this_char = getChar(mStream);

			if (last_char == '*' && this_char == '/') count--;
			if (last_char == '/' && this_char == '*') count++;

			last_char = this_char;
		}

		if (count > 0) {
			throw std::runtime_error("Unterminated block comment");
		}
	} else {
		mStream.seekg(pos, mStream.beg);
	}
}


Token* Lexer::readConstant() {
	if (peekChar(mStream) != '"') return nullptr;
	getChar(mStream);

	std::string buf = "";

	while (!eof()) {
		char this_char = getChar(mStream);

		if (this_char == '"') break;
		else if (this_char == '\n') {
			throw std::runtime_error("Unterminated string");
		} else if (this_char == '\\') { // Escape character
			buf += str(this_char) + str(getChar(mStream));
			continue;
		}

		buf += str(this_char);
	}

	return new Token(TokenType::IDENTIFER, buf);
}

Token* Lexer::readKeyword() {
	if (peekChar(mStream) == ':') {
		return new Token(TokenType::COLON, str(getChar(mStream)));
	} else if (peekChar(mStream) == '|') {
		return new Token(TokenType::BAR, str(getChar(mStream)));
	} else if (peekChar(mStream) == ';') {
		return new Token(TokenType::SEMICOLON, str(getChar(mStream)));
	} else if (peekChar(mStream) == '%') {
		std::string buf = str(getChar(mStream));

		while (!eof() && std::isalpha(peekChar(mStream))) {
			buf += str(getChar(mStream));
		}

		if (buf == "%token") {
			return new Token(TokenType::TOKEN, buf);
		} else if (buf == "%epsilon") {
			return new Token(TokenType::EPSILON, buf);
		} else {
			throw new std::runtime_error("Unknown directive " + buf);
		}
	}

	return nullptr;
}

Token* Lexer::readIdentifier() {
	if (!std::isalpha(peekChar(mStream))) {
		return nullptr;
	}

	std::string buf = str(getChar(mStream));

	while (!eof() && (std::isalnum(peekChar(mStream)) || peekChar(mStream) == '_')) {
		buf += str(getChar(mStream));
	}

	return new Token(TokenType::IDENTIFER, buf);
}


Token* Lexer::readToken() {
	if (eof()) return nullptr;

	// Ignore whitespace
	while (!eof() && isspace(peekChar(mStream))) {
		getChar(mStream);
	}

	// Consume comments
	consumeComment();

	auto pos = mStream.tellg();
	if (auto tok = readKeyword()) return tok;

	mStream.seekg(pos, mStream.beg);
	if (auto tok = readIdentifier()) return tok;

	mStream.seekg(pos, mStream.beg);
	if (auto tok = readConstant()) return tok;

	throw std::runtime_error("Unknown token " + str(peekChar(mStream)));
}

bool Lexer::eof() const {
	return mStream.eof();
}
