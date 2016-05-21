/*
** Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <iostream>
#include <Grammar.h>

void yyerror(Grammar* grammar, const char* err)
{
	std::cerr << err << std::endl;
}
