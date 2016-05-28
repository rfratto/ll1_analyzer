//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <ast/ast.h>
#include <ast/walker.h>
#include <ast/visitor.h>
#include <c++/5.3.0/stdexcept>

using namespace ast;

template <typename T>
static T* as(Symbol* obj) { return dynamic_cast<T*>(obj); }

template <typename T>
static bool isA(Symbol* obj) { return as<T>(obj) != nullptr; }

void Walker::WalkSymbol(Visitor *visitor, Symbol *symbol) {
	if (isA<Nonterminal>(symbol)) {
		WalkNonterminal(visitor, as<Nonterminal>(symbol));
	} else if (isA<Terminal>(symbol)) {
		WalkTerminal(visitor, as<Terminal>(symbol));
	} else if (isA<Epsilon>(symbol)) {
		WalkEpsilon(visitor, as<Epsilon>(symbol));
	} else {
		throw std::runtime_error("Unknown symbol class.");
	}
}

void Walker::WalkNonterminal(Visitor *visitor, Nonterminal *symbol) {
	visitor->VisitNonterminal(symbol);
}

void Walker::WalkTerminal(Visitor *visitor, Terminal *symbol) {
	visitor->VisitTerminal(symbol);
}

void Walker::WalkEpsilon(Visitor *visitor, Epsilon *symbol) {
	visitor->VisitEpsilon(symbol);
}

void Walker::WalkProduction(Visitor *visitor, Production *production) {
	visitor->VisitProduction(production);

	WalkNonterminal(visitor, production->nonterminal);

	for (auto symbol : production->symbols) {
		WalkSymbol(visitor, symbol);
	}
}

void Walker::WalkGrammar(Visitor *visitor, Grammar *grammar) {
	visitor->VisitGrammar(grammar);

	for (auto terminal : grammar->terminals) {
		WalkTerminal(visitor, terminal);
	}

	for (auto prod : grammar->productions) {
		WalkProduction(visitor, prod);
	}
}
