// Джеймс Аквух
// 28.02.2015
// Шаблонный вектор с перегруженными операциями и Однонаправленным итератором
// Возможно использование в качестве безопасной n-мерной матрицы

#include <iostream>
#include "vector.h"
#include "string.h"

using namespace std;

int main()
{
	try{ 
		Vector< Vector<int> > v(3, Vector<int> (2, 0));
		cout << "\nMatrix of ints:" << v;
		v[1].resize(4);
		Vector<int>::fill(v[1].begin(), v[1].end(), 1);
		std::swap(v[1], v[0]);
		cout << "\nMatrix of ints:" << v;
		v[1].clear();
		cout << "\nMatrix of ints:" << v;
		Vector<String> v1(3);
		Vector<String> v2(3);
		cout << "\nEnter String vector (3):\t";
		cin >> v1;
		cout << "\nEnter String vector (3):\t";
		cin >> v2;
		cout << "\nOut vector v1 + v2:\t";
		cout << v1 + v2;
		cout << "\nDoes vector v1 == v2:\t";
		cout << (v1 == v2);
		cout << "\nDoes vector v2 == v2:\t";
		cout << (v2 == v2);
		cout << "\nVector 1 iteration:\t";
		for (Vector<String>::Iterator it = v1.begin(); it != v1.end(); ++it)
			cout << *it << "\t";
	} catch (Error &e) {
		cout << '\n' << e.what();
	}
	cout << "\n";
	system("pause");
	return 0;
}