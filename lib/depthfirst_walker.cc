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

void DepthFirstWalk::WalkNonterminal(Visitor* visitor, Nonterminal* symbol) {
	visitor->VisitNonterminal(symbol);
}

void DepthFirstWalk::WalkTerminal(Visitor* visitor, Terminal* symbol) {
	visitor->VisitTerminal(symbol);
}

void DepthFirstWalk::WalkEpsilon(Visitor* visitor, Epsilon* symbol) {
	visitor->VisitEpsilon(symbol);
}

void DepthFirstWalk::WalkProduction(Visitor* visitor, Production* production) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitProduction(production);

	WalkNonterminal(visitor, production->nonterminal);
	for (auto sym : production->symbols) WalkSymbol(visitor, sym);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitProduction(production);
}

void DepthFirstWalk::WalkGrammar(Visitor* visitor, Grammar* grammar) {
	if (mOrder == TraversalOrder::PREORDER) visitor->VisitGrammar(grammar);

	for (auto term : grammar->terminals) WalkTerminal(visitor, term);
	for (auto prod : grammar->productions) WalkProduction(visitor, prod);

	if (mOrder == TraversalOrder::POSTORDER) visitor->VisitGrammar(grammar);
}
