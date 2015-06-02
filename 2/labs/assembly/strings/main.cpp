// Джеймс Аквух
// 20.03.2015
// Ассемблер. Работа со строками. Цепочечные команды. Внешние подпрограммы

#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
	char s1[10] = "string";
	char s2[10] = "string";
	char s3[10] = "mom";
	char s4[100] = "Hello world, show must go on!";
	char s5[100] = "I do (()not) like studying (hard)";
	cout << "String:\t" << s4;
	cout << "\nLength(\"" << s4 << "\"):\t" << len(s4);
	cout << "\nComparing \"" << s1 << "\" and \"" << s2 << "\":\t" << cmp(s1, s2);
	replace(s4, 'o', 'a');
	cout << "\nAfter replacing 't' to 'r':\t" << s4;
	remove_char(s4, 'a');
	cout << "\nAfter removing 'r':\t" << s4;
	cout << "\nCount words in \"" << s4 << "\":\t" << count_words(s4);
	cout << "\nComparing \"" << s1 << "\" and \"" << s2 << "\":\t" << cmp(s1, s2);
	cout << "\nDoes \"" << s1 << "\" palindrom:\t" << palindrom(s1);
	cout << "\nDoes \"" << s3 << "\" palindrom:\t" << palindrom(s3);
	cout << "\nString:\t" << s5;
	clear_brackets(s5);
	cout << "\nAfter clearing text in brackets:\t" << s5;
	cout << "\nShortest word in \"" << s4 << "\":\t" << shortest_word(s4);

	cout << endl;
	system("pause");
	return 0;
}