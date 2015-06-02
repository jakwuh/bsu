#include "functions.h"

bool string::isPalindrom(char const* word) {
	for (int i = strlen(word) / 2; i < (int)strlen(word); i++)
		if (word[i] != word[strlen(word) - 1 - i]) return false;
	return true;
}

int string::findWord(char* const needle, char* const heap, unsigned int sP) { // sP - startingPoint
	unsigned int k;
	bool equal;
	if (strlen(needle) == 0) return -1;
	for (int i = sP; i < (int)strlen(heap); i++)
		if (heap[i] == needle[0]) {
			k = 0;
			equal = true;
			while(++k < strlen(needle))
				if (i + k >= strlen(heap) || heap[i + k] != needle[k]) 
					equal = false;
			if (equal) return i;
		}
	return -1;
}

int string::findNumber(char* const string, unsigned int sP) {
	for (int i = sP; i < (int)strlen(string); i++)
		if (strchr("0123456789", string[i]) != NULL)
			return i;
	return -1;
}

bool string::deleteWord(char* string, char* const word, unsigned int sP) {
	if (string::findWord(word, string, sP) == -1) return false;
	for (int i = string::findWord(word, string); i < (int)strlen(string) - (int)strlen(word) + 1; i++)
		string[i] = string[i + strlen(word)];
	return true;
}

char* string::paste(char* string, char* const appendAfter, char* const word, unsigned int sP) {
	if (string::findWord(appendAfter, string, sP) == -1) return string;
	char* str = new char[strlen(string) + strlen(word) + 1];
	int k = string::findWord(appendAfter, string, sP);
	char *left = new char[k + strlen(appendAfter)], *right = new char[strlen(string) - k - strlen(appendAfter)];
	strncpy(left, string, k + strlen(appendAfter));
	strncpy(right, &string[k + strlen(appendAfter)], strlen(string) - k - strlen(appendAfter)); 
	str[0] = 0;
	strncat(str, left, k + strlen(appendAfter));
	strncat(str, word, strlen(word));
	strncat(str, right, strlen(string) - k - strlen(appendAfter));
	return str;
}

char* string::swap(char* string, int pos1, int length1, int pos2, int length2) {
	char 
		*left = new char[pos1],
		*middle = new char[pos2 - pos1 - length1], 
		*right = new char[strlen(string) - pos2 - length2], 
		*word1 = new char[length1], 
		*word2 = new char[length2];
	if (pos2 < pos1) {
		std::swap(pos2, pos1);
		std::swap(length2, length1);
	}
	strncpy(left, string, pos1);
	strncpy(word1, &string[pos1], length1);
	strncpy(middle, &string[pos1 + length1], pos2 - pos1 - length1);
	strncpy(word2, &string[pos2], length2);
	strncpy(right, &string[pos2 + length2], strlen(string) - pos2 - length2);
	char* str = new char[strlen(string) + 1];
	str[0] = 0;
	strncpy(str, left, pos1);
	str = strncat(str, word2, length2);
	str = strncat(str, middle, pos2 - pos1 - length1);
	str = strncat(str, word1, length1);
	str = strncat(str, right, strlen(string) - pos2 - length2);
	return str;
}

char* string::replace(char* string, char* const replaceWord, char* const word, unsigned int sP) {
	if (string::findWord(replaceWord, string, sP) == -1) return string;
	char* str = new char[strlen(string) + strlen(word) - strlen(replaceWord) + 1];
	int k = string::findWord(replaceWord, string, sP);
	char *left = new char[k], *right = new char[strlen(string) - k - strlen(replaceWord)];
	strncpy(left, string, k);
	strncpy(right, &string[k + strlen(replaceWord)], strlen(string) - k - strlen(replaceWord)); 
	str[0] = 0;
	strncat(str, left, k);
	strncat(str, word, strlen(word));
	strncat(str, right, strlen(string) - k - strlen(replaceWord));
	return str;
}
