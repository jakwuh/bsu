// Джеймс Аквух
// 26.05.2015
// Консольная игра лабиринт

#include <iostream>
#include <Windows.h>
#include "controller.h"
#include <conio.h>

int main()
{
	try{
		char* name = new char[100];
		std::cout << "Enter your name:\n";
		std::cin >> name;
		Controller C;
		C.setName(name);

		int ch = 0;
		while (ch != 13 && ch != 10)
		{
			ch = _getch();
			if (ch == 75) C.moveMe(d_up);
			if (ch == 80) C.moveMe(d_right);
			if (ch == 77) C.moveMe(d_down);
			if (ch == 72) C.moveMe(d_left);
		}
	} catch (...) {
		std::cout << "\nUnknown exception caught";
		std::cout << "\n";
		system("pause");
	}
	return 0;
}