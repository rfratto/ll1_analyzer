//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

///
/// lexer regex
///
/// token -> "%token"
/// identifier -> [A-Za-z][A-Za-z0-9_]*
/// colon -> ":"
/// bar -> "|"
/// epsilon -> "%epsilon"
/// constant -> \"(\\.|[^\\"])*\"
/// semicolon -> ";"
/// whitespace -> [\ \t\r\n]
/// comment -> "//"[^\r\n]*
/// block_comment -> "/*"   { consume until matching */ }
///

