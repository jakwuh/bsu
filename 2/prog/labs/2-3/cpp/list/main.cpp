// Джеймс Аквух
// 25.02.2015
// С любовью написанный список (вставка на n-ую позицию, удаление с n-ой позиции, поиск с передачей callback - функции и другие функции)

#include <iostream>
#include "list.h"
#include <typeinfo>

bool condition(const void* el) {
	return *(int*)el % 2 == 0;
}

using namespace std;

int main() {
	try {
		List l;
		l.push_back(1);
		l.push_back(2);
		l.push_back(3);
		l.push_back(4);
		l.push_back(5);
		l.push_back(7);
		l.remove(condition);
		l.print();
		cout << "\n" << l.sum(1);
	} catch (BadArguments& e) {
		cout << "\nError catched:\t" << typeid(e).name();
	} catch (Empty& e) {
		cout << "\nError catched:\t" << typeid(e).name();
	} catch (Overflow& e) {
		cout << "\nError catched:\t" << typeid(e).name();
	}
	cout << "\n";
	system("pause");
	return 0;
}