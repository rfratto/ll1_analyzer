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
		/// Dispatches into the correct walk method, does not call
		/// anything on visitor directly.
		void WalkSymbol(Visitor* visitor, Symbol* symbol);

		void WalkNonterminal(Visitor* visitor, Nonterminal* symbol);
		void WalkTerminal(Visitor* visitor, Terminal* symbol);
		void WalkEpsilon(Visitor* visitor, Epsilon* symbol);
		void WalkProduction(Visitor* visitor, Production* production);
		void WalkGrammar(Visitor* visitor, Grammar* grammar);
	};
}