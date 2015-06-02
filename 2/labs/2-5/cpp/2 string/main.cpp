// Джеймс Аквух
// 28.02.2015
// Класс Строки

#include <iostream>
#include "string.h"

using namespace std;

int main()
{
	try{
		String s1 = "The";
		String s2 = "king";
		String s3 = "The king";
		String snum = 25600;
		cout << "\n0:\t" << s3.substr(s1);
		cout << "\n4:\t" << s3.substr(s2);
		cout << "\n-1:\t" << s2.substr(s1);
		cout << "\nThe king:\t" << (s1 + " " + s2);
		cout << "\n0:\t" << s3.substr(s1 + " " + s2);
		cout << "\nThe king:\t" << s1.strpst(" " + s2, 3);
		cout << "\nThe queen:\t" << s1.strrlc("queen", 4);
		cout << "\nh:\t" << s1[1];
		cout << "\nhe q:\t" << s1(1, 4);
		cout << "\n0:\t" << (s1 == s3);
		cout << "\n25600:\t" << snum;
		cout << "\n25600:\t" << String::stoi(snum);
	} catch(Error &e) {
		cout << '\n' << e.what();
	}
	cout << "\n";
	system("pause");
	return 0;
}