//
// Copyright 2015-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <sstream>
#include <gtest/gtest.h>
#include <lexer.h>

TEST(Lexer, EmptyInputTest) {
	std::stringstream ss("");
	ast::Lexer l(ss);

	EXPECT_TRUE(l.eof());
	EXPECT_EQ(l.readToken(), nullptr);
}

