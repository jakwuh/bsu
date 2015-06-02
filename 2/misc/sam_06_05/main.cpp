// 5 вариант
// Джеймс Аквух
// Самостоятельная работа 06.05

#include <iostream>
#include <fstream>
#include "vector.h"
#include "fraction.h"

using namespace std;

int main()
{
	try {
		ifstream in("input.txt");
		ofstream out("output.txt");
		int n, m, k;
		in >> n >> m;
 		Vector < Vector < Fraction > > v(n, Vector< Fraction >(m, 0));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				in >> k;
				v[i][j] = k;
			}
		}
		out << "Input matrix:" << v;
		cout << "Enter k:\t";
		cin >> k;
		v[k].sort();

		out << "\n\nMatrix with row k sorted:" << v << "\n\nLast row plus row k sorted:" << (v[n - 1] + v[k]);
	}
	catch (Error& e) {
		cout << e.what();
	}
	catch (...) {
		cout << "Error!";
	}
	
	system("pause");
	return 0;
}