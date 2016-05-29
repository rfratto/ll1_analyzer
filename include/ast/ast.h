//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <string>
#include <vector>

namespace ast {
	struct Symbol {
		virtual ~Symbol() { }
	};

	struct Nonterminal : Symbol {
		std::string name;
	};

	struct Terminal : Symbol {
		std::string name;
	};

	struct Epsilon : Symbol { };

	struct Production {
		Nonterminal* nonterminal;
		std::vector<Symbol*> symbols;
	};

	struct Grammar {
		// Note: terminals can be declared at any point in the grammar file and can be forward-used.
		// Parsers will have to defer parsing productions until all terminals have been found.
		// This can be done by keeping a buffer of the lexical tokens up to and including the grammar end.

		std::vector<Terminal*> terminals;
		std::vector<Production*> productions;
	};
}

