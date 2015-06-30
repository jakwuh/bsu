// Джеймс Аквух
// 25.02.2015
// Шаблонный стек на массивах

#include <iostream>
#include "stack_static.h"

typedef StackStatic<int> Stack;

using namespace std;

int main() {
	setlocale(LC_ALL, "");
	try{
		Stack s(100);
		s.push(1);
		cout << s.top() << endl;
		s.pop();
		s.push(2);
		s.push(3);
		cout << s.peek() << endl;
		s.pop();
		cout << s.peek() << endl;
		s.pop();
		cout << s.peek() << endl;
		s.pop();
	} catch (Empty) {
		cout << "\nОшибка: Стек пуст";
	} catch (Full) {
		cout << "\nОшибка: Стек полон";
	}
	cout << endl;
	system("pause");
	return 0;
}