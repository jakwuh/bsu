#ifndef __FUNCTIONS_H_INCLUDED__
#define __FUNCTION_H_INCLUDED__
#define MAX_WORDS 100500
#define DELIMITERS "\0,.|\r\n\t"


#include <iostream>
#include <cstring>
#include <algorithm>

namespace string {
	bool isPalindrom(char const*);
	int findWord(char* const, char* const, unsigned int = 0);
	int findNumber(char* const string, unsigned int = 0);
	bool deleteWord(char*, char* const, unsigned int = 0); // returns number of deleted words
	char* paste(char*, char* const, char* const, unsigned int = 0); // pastes 1 word;
	char* swap(char*, int, int, int, int);
	char* replace(char*, char* const, char* const, unsigned int = 0);
	void sort(char*);
	void qsort(char*);
}

#endif