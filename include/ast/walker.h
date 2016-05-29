//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include "ast.h"


namespace ast {
	class Visitor;

	class Walker {
	public:
		/// Dispatches into the concrete walk method.
		void WalkSymbol(Visitor* visitor, Symbol* symbol);

		virtual void WalkNonterminal(Visitor* visitor, Nonterminal* symbol) = 0;
		virtual void WalkTerminal(Visitor* visitor, Terminal* symbol) = 0;
		virtual void WalkEpsilon(Visitor* visitor, Epsilon* symbol) = 0;
		virtual void WalkProduction(Visitor* visitor, Production* production) = 0;
		virtual void WalkGrammar(Visitor* visitor, Grammar* grammar) = 0;
	};

	/// NonTraversalWalk will visit each concrete element, but not walk any members.
	/// Further traversal is up to the visitor.
	class NonTraversalWalk : public Walker {
	public:
		virtual void WalkNonterminal(Visitor* visitor, Nonterminal* symbol) override;
		virtual void WalkTerminal(Visitor* visitor, Terminal* symbol) override;
		virtual void WalkEpsilon(Visitor* visitor, Epsilon* symbol) override;
		virtual void WalkProduction(Visitor* visitor, Production* production) override;
		virtual void WalkGrammar(Visitor* visitor, Grammar* grammar) override;
	};

	enum TraversalOrder {
		PREORDER,
		POSTORDER
	};

	class DepthFirstWalk : public Walker {
	private:
		TraversalOrder mOrder;
	public:
		virtual void WalkNonterminal(Visitor* visitor, Nonterminal* symbol) override;
		virtual void WalkTerminal(Visitor* visitor, Terminal* symbol) override;
		virtual void WalkEpsilon(Visitor* visitor, Epsilon* symbol) override;
		virtual void WalkProduction(Visitor* visitor, Production* production) override;
		virtual void WalkGrammar(Visitor* visitor, Grammar* grammar) override;

		DepthFirstWalk(TraversalOrder o) : mOrder(o) { }
	};
}