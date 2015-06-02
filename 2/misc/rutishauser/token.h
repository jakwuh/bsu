#ifndef __TOKEN_H_INCLUDED__
#define __TOKEN_H_INCLUDED__

#include <cstring>
#include <cstdlib>
#include <sstream>

class Token {
public:
	Token(int level_ = 0) : level(level_) {};
	void setLevel(int level_) { level = level_; };
	int level;
};

class Number : public Token {
public:
	enum Type { number, undefined } type;
	Number(char*&, int); // использовать char*& это плохая практика. В этом состоит минус проектирования структуры кода
	Number(double, int);
	double value;
};

class Operation : public Token {
public:
	enum Type { plus, minus, multiply, divide, undefined } type;
	Operation(char*&, int);
	double operate(Number const& a, Number const& b);
};

class Bracket : public Token {
public:
	enum Type { open, close, undefined } type;
	Bracket(char*&, int);
};

#endif