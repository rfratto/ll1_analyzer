/*
** Copyright 2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <string>
#include <exception>

class Component;

class base_error : public std::exception
{
protected:
	std::string m_error;
public:
	virtual const char* what() const noexcept override;
};

class left_recursion_error : public base_error
{
public:
	left_recursion_error(Component* component);
};

class undefined_error : public base_error
{
public:
	undefined_error(Component* component);
};
