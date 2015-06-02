// Джеймс Аквух
// 25.02.2015
// Просто динамический дек

#include <iostream>
#include "deque.h"

using namespace std;

int main() {
	try{
		Deque d;
		d.push_front(1);
		cout << d.back().value << endl;
		d.pop_back();
		d.push_back(2);
		cout << d.front().value << endl;
		cout << d.back().value << endl;
		d.pop_front();
		d.pop_front();
	} catch (...) {
		cout << "Error caught";
	}
	system("pause");
	return 0;
}