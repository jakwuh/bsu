// Вычисление полного скобочного выражения методом Рутисхаузера
// Джеймс Аквух, 30.04.2015

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "token.h"

using namespace std;
typedef vector<Token*> Tokens;

int findMaxLevel(Tokens& tokens)
{
	int max = 0;
	for (auto it : tokens) max = std::max(max, it->level);
	return max;
}

bool levelDown(Tokens& tokens)
{
	if (tokens.size() == 0) throw "Empty tokens array!";
	int level = findMaxLevel(tokens);
	Tokens::iterator from = tokens.begin(), to = --tokens.end(), op;
	while ((*from)->level != level) ++from;
	while ((*to)->level != level) --to;
	Token* token_ptr = new Number(((Operation*)*(from + 1))->operate(*(Number*)*from, *(Number*)*to), --level);
	tokens.insert(tokens.erase(--from, ++++to), token_ptr);
	return tokens.size() > 1;
}

Tokens parseInput(char* buf)
{
	Tokens tokens;
	Token* token_ptr;
	int level = 0;
	while (strlen(buf)) {
 		token_ptr = new Number(buf, level);
		if (((Number*)token_ptr)->type == Number::Type::undefined) token_ptr = new Bracket(buf, level);
		if (((Bracket*)token_ptr)->type == Bracket::Type::undefined) token_ptr = new Operation(buf, level);
		if (((Operation*)token_ptr)->type == Operation::Type::undefined) throw "Wrong input equation";
		tokens.push_back(token_ptr);
		level = token_ptr->level;
	}
	return tokens;
}

int main()
{
	try {
		char* buf = new char[500];
		cout << "Enter string for calculations:\n";
		cin >> buf;

		Tokens tokens = parseInput(buf);
		
		while (levelDown(tokens));
		cout << static_cast<Number*>(tokens.at(0))->value;
	}
	catch (char* error) {
		cerr << error;
	}
	catch (...) {
		cerr << "Unhandled error";
	}

	cout << "\n\n";
	system("pause");
	return 0;
}

