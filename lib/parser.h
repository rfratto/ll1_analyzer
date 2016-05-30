//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

///
/// grammar
///
/// start: statements
/// statements: statement statements | %epsilon
/// statement: terminals | production
///
/// terminals: TOKEN terminal_list
/// terminal_list: IDENTIFIER terminal_list | %epsilon
///
/// production: IDENTIFIER COLON derivation chain_or_finish
/// chain_or_finish: BAR derivation chain_or_finish | SEMICOLON
///
/// derivation: component_derivation | EPSILON
/// component_derivation: component component_derivation'
/// component_derivation': component_derivation | %epsilon
///
/// component: IDENTIFER | CONSTANT
///
