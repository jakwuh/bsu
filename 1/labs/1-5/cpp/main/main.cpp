#include <iostream>
#include <cstring>
#include "functions.h"
#include <typeinfo>


int main() {
	char* str = new char[12];
	str = "abc jim cba";
	std::cout << "\nif jajaj is Palindrom:\t" << string::isPalindrom("jajaj");
	std::cout << "\nfind jim in abcjimabc\t" << string::findWord("jim", str);
	std::cout << "\nfind number in abcd12\t" << string::findNumber("abcd12 ");
	str = string::swap(str,0,3,8,3);
	std::cout << "\nSwaps abc with cba\t" << str;
	string::deleteWord(str, "jim");
	std::cout << "\nDeletes jim from cba jim abc\t" << str;
	str = string::paste(str, "abc", "123456");
	std::cout << "\nPastes 123456 after abc\t" << str;
	str = string::replace(str, "abc", "HHH");
	std::cout << "\nReplaces abc with HHH\t" << str;
	std::cout << std::endl;
	system("pause");
	return 0;
}