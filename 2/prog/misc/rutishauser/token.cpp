#include "stdafx.h"
#include "token.h"

Number::Number(char*& token, int level_) : type(Type::undefined), Token(++level_)
{
	if (strspn(token, "0123456789") != 0) {
		type = Type::number;
		int x;
		sscanf_s(token, "%d", &x);
		value = x;
		token += strspn(token, "0123456789");
	}
}

Number::Number(double val, int level_) : type(Type::number), value(val), Token(level_){}

Operation::Operation(char*& token, int level_) : Token(--level_), type(Type::undefined)
{
	if (strspn(token, "+")) type = Type::plus;
	else if (strspn(token, "-")) type = Type::minus;
	else if (strspn(token, "*")) type = Type::multiply;
	else if (strspn(token, "/")) type = Type::divide;
	else --token;
	++token;
}

Bracket::Bracket(char*& token, int lvl) : type(Type::undefined)
{
	if (strspn(token, "{[(")) {
		type = Type::open;
		Token::setLevel(++lvl);
		++token;
	}
	else if (strspn(token, ")]}")) {
		type = Type::close;
		Token::setLevel(--lvl);
		++token;
	}
}

double Operation::operate(Number const& a, Number const& b)
{
	switch (type) {
	case Type::minus:
		return a.value - b.value;
		break;
	case Type::plus:
		return a.value + b.value;
		break;
	case Type::divide:
		return a.value / b.value;
		break;
	case Type::multiply:
		return a.value * b.value;
		break;
	default:
		throw "Wrong operation";
		break;
	}
}