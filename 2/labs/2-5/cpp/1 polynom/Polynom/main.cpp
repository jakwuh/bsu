// Джеймс Аквух
// 27.02.2015
// Класс Полином (сложение/вычитание, умножение/деление) перегружены большинство операций, обработка исключений присутствует

#include <iostream>
#include "Polynom.h"

using namespace std;

int main()
{
	try{
		Polynom p1(2);
		p1.init(2, 1., 2., 1.);
		Polynom p2(3);
		p2.init(3, 1., 3., 3., 1.);

		cout << p1 << "\n";
		cout << p2 << "\n";
		cout << p1 + p2 << "\n";
		cout << p2 * p2 << "\n";
		cout << p2 * p2 / p1 << "\n";
		cout << p1 / p1 << "\n";
	} catch (Error &e) {
		cout << "\nError:\t" << e.what();
	}
	cout << "\n";
	system("pause");
	return 0;
}