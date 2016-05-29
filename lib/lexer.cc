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

Lexer::Lexer(std::istream &stream) : mStream(stream) { }

void Lexer::consumeComment() {
	auto pos = mStream.tellg();

	if (mStream.get() != '/') {
		mStream.seekg(pos, mStream.beg);
		return;
	}

	if (mStream.peek() == '/') {
		// One-line comment
		mStream.get();
		while (!eof() && mStream.peek() != '\n') mStream.get();
	} else if (mStream.peek() == '*') {
		// Block comment
		mStream.get();

		int count = 1;

		int last_char = 0;
		while (!eof() && count > 0) {
			int this_char = mStream.get();

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
	if (mStream.peek() != '"') return nullptr;
	mStream.get();

	std::string buf = "";

	while (!eof()) {
		int this_char = mStream.get();

		if (this_char == '"') break;
		else if (this_char == '\n') {
			throw std::runtime_error("Unterminated string");
		} else if (this_char == '\\') { // Escape character
			buf += this_char;
			buf += mStream.get();
			continue;
		}

		buf += this_char;
	}

	return new Token(TokenType::IDENTIFER, buf);
}

Token* Lexer::readKeyword() {
	if (mStream.peek() == ':') {
		return new Token(TokenType::COLON, "" + mStream.get());
	} else if (mStream.peek() == '|') {
		return new Token(TokenType::BAR, "" + mStream.get());
	} else if (mStream.peek() == ';') {
		return new Token(TokenType::SEMICOLON, "" + mStream.get());
	} else if (mStream.peek() == '%') {
		std::string buf = "" + mStream.get();

		while (!eof() && std::isalpha(mStream.peek())) {
			buf += mStream.get();
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
	if (!std::isalpha(mStream.peek())) {
		return nullptr;
	}

	std::string buf = "" + mStream.get();

	while (!eof() && (std::isalnum(mStream.peek()) || mStream.peek() == '_')) {
		buf += mStream.get();
	}

	return new Token(TokenType::IDENTIFER, buf);
}


Token* Lexer::readToken() {
	if (eof()) return nullptr;

	// Ignore whitespace
	while (!eof() && isspace(mStream.peek())) {
		mStream.get();
	}

	// Consume comments
	consumeComment();

	auto pos = mStream.tellg();
	if (auto tok = readKeyword()) return tok;

	mStream.seekg(pos, mStream.beg);
	if (auto tok = readIdentifier()) return tok;

	mStream.seekg(pos, mStream.beg);
	if (auto tok = readConstant()) return tok;

	throw std::runtime_error("Unknown token " + mStream.peek());
}

bool Lexer::eof() const {
	return mStream.eof();
}
