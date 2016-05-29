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
	class Visitor {
	public:
		virtual void VisitNonterminal(Nonterminal* symbol) = 0;
		virtual void VisitTerminal(Terminal* symbol) = 0;
		virtual void VisitEpsilon(Epsilon* symbol) = 0;
		virtual void VisitProduction(Production* production) = 0;
		virtual void VisitGrammar(Grammar* grammar) = 0;
	};

	/// EmptyVisitor is a Visitor that does nothing. It can
	/// be used as a base class if you don't need to implement visit
	/// methods for each class.
	class EmptyVisitor : public Visitor {
	public:
		virtual void VisitNonterminal(Nonterminal* symbol) override { };

		virtual void VisitTerminal(Terminal* symbol) override { };

		virtual void VisitEpsilon(Epsilon* symbol) override { };

		virtual void VisitProduction(Production* production) override { };

		virtual void VisitGrammar(Grammar* grammar) override { };
	};
}
