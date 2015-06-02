// Джеймс Аквух
// 20.03.2015
// Ассемблер. Работа с внешними подпрограммами. Работа с массивами. Использование функций. Использование цепочечных команд

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <malloc.h>
#include "functions.h"

using namespace std;

void* generateArray(int, int = 0, int = 100);
void printArray(void*, int, int = 0);

int main()
{
	srand((int)time(0));
	int* a, *a1, **b;
	
	b = (int**)generateArray(3, 3, 20);
	cout << "Matrix A:\t";
	printArray(b, 3, 3);
	cout << "\nTransposed matrix A:\t";
	transpose(b, 3, 3);
	printArray(b, 3, 3);

	a = (int*)generateArray(10, 0, 5);
	a1 = (int*)generateArray(10, 0, 5);
	int *u = new int[10];
	int *am = new int[20];
	int k, km;
	unique_array(a, 10, u, k);

	cout << "\nArray A:\t";
	printArray(a, 10);
    cout << "Array B:\t";
    printArray(a1, 10);
	cout << "Sorted array A:\t";
	sort_array(a, 10);
	printArray(a, 10);
	cout << "Sorted array B:\t";
	sort_array(a1, 10);
	printArray(a1, 10);
	cout << "\nNumber of unique elements in A:\t" << count_unique(a, 10);
	cout << endl << endl;
	cout << "Unique array A:\t";
	printArray(u, k);
	merge(a, 10, a1, 10, am, km);
	cout << "Merge arrays A & B:\t";
	printArray(am, km);
	array_conjuction(a, 10, a1, 10, am, km);
	cout << "Conjucted arrays A & B:\t";
	printArray(am, km);

	a = (int*)generateArray(10, 0, 1);
	cout << "\nArray A:\t";
	printArray(a, 10); \
	cout << "Max sequence in A consists of elements:\t" << find_max_sequence(a, 10);
	cout << endl;

	system("pause");
	return 0;
}

void printArray(void* a, int n, int m)
{
	if (m == 0) {
		int* res = (int*)a;
		cout << endl;
		for (int i = 0; i < n; ++i) {
			cout << setw(3) << res[i];
		}
		cout << endl;
	}
	else {
		int** res = (int**)a;
		for (int i = 0; i < n; ++i) {
			cout << endl;
			for (int j = 0; j < m; ++j)
				cout << setw(3) << res[i][j];
		}
		cout << endl;
	}
}

void* generateArray(int n, int m, int z)
{
	if (m == 0) {
		int* res = new int[n];
		for (int i = 0; i < n; ++i)
			res[i] = rand() % (2 * z) - z;
		return res;
	}
	else {
		int** res = new int*[n];
		for (int i = 0; i < n; ++i) {
			res[i] = new int[m];
			for (int j = 0; j < m; ++j)
				res[i][j] = rand() % z - z;
		}
		return res;
	}
}