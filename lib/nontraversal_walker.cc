//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <ast/walker.h>
#include <ast/visitor.h>

using namespace ast;

void NonTraversalWalk::WalkNonterminal(Visitor* visitor, Nonterminal* symbol) {
	visitor->VisitNonterminal(symbol);
}

void NonTraversalWalk::WalkTerminal(Visitor* visitor, Terminal* symbol) {
	visitor->VisitTerminal(symbol);
}

void NonTraversalWalk::WalkEpsilon(Visitor* visitor, Epsilon* symbol) {
	visitor->VisitEpsilon(symbol);
}

void NonTraversalWalk::WalkProduction(Visitor* visitor, Production* production) {
	visitor->VisitProduction(production);
}

void NonTraversalWalk::WalkGrammar(Visitor* visitor, Grammar* grammar) {
	visitor->VisitGrammar(grammar);
}

