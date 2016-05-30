//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <gtest/gtest.h>
#include <lexer.h>

template <typename T>
bool tokensEq(ast::Token* tok, T to);

template <typename T>
void expectToken(ast::Lexer& l, T val);

#define TEST_TOKEN(test_case_name, test_name, input, ty) \
    TEST(test_case_name, test_name) {\
        std::stringstream ss(input); ast::Lexer l(ss);\
        EXPECT_FALSE(l.eof()); expectToken(l, ty);\
    }

#define TEST_TOKEN_VAL(test_case_name, test_name, input, ty) \
    TEST(test_case_name, test_name) {\
        std::stringstream ss(input); ast::Lexer l(ss);\
        EXPECT_FALSE(l.eof()); expectToken(l, ty);\
    }