//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <stdexcept>
#include <ast/walker.h>

using namespace ast;

template <typename T>
static T* as(Symbol* s) { return dynamic_cast<T*>(s); }

template <typename T>
static bool isA(Symbol* s) { return as<T>(s) != nullptr; }

void Walker::WalkSymbol(Visitor* visitor, Symbol* symbol) {
	if (isA<Nonterminal>(symbol)) {
		WalkNonterminal(visitor, as<Nonterminal>(symbol));
	} else if (isA<Terminal>(symbol)) {
		WalkTerminal(visitor, as<Terminal>(symbol));
	} else if (isA<Epsilon>(symbol)) {
		WalkEpsilon(visitor, as<Epsilon>(symbol));
	} else {
		throw std::runtime_error("Unknown concrete symbol class");
	}
}



