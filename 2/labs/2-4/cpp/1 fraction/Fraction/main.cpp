// Джеймс Аквух
// 26.02.2015
// Класс Дробь

#include <iostream>
#include "fraction.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	try{
		Fraction f1(1);
		Fraction f2(1);
		cout << "Введите числитель и знаменатель дроби:\n";
		cin >> f1;
		cout << "Введите числитель и знаменатель дроби:\n";
		cin >> f2;
		cout << "Сумма дробей:\t" << f1 + f2;
		cout << "\nРазность дробей:\t" << f1 - f2;
		cout << "\nПроизведение дробей:\t" << f1 * f2;
		cout << "\nЧастное дробей:\t" << f1 / f2;
		cout << "\nПервая дробь больше второй:\t" << (f1 > f2);
		cout << "\nДроби равны:\t" << (f1 == f2);
		cout << "\nПротивоположное первой дроби:\t" << (-f1);
		cout << "\nПеревод первой дроби в тип double:\t" << (double)f1;
		// f1 = f1 + 2 - f1 * (f1 + 3);
	} catch (Error& e) {
		cout << "\nОшибка:\t" << e.what() << "\n";
	}
	cout << endl;
	system("pause");
	return 0;
}