// Аквух Джеймс
// 11.02.2015
// Программирование в теоремах и задачах - структуры и числа - Задача 6.2.5
//
// Напечатать в  порядке  возрастания  первые  n  нату-
// ральных  чисел, в разложение которых на простые множители входят
// только числа 2, 3, 5 и так далее.(Заданы массивом)

#include <iostream>
#include <iomanip>
#include "List.h"

List * minList(List ** lists, int n)
{
	List ** iterator = lists;
	int i = 0;
	List * minList = *lists;
	while (++i < n) {
		if ((*(iterator + i))->peek() != 0 && (*(iterator + i))->peek() < minList->peek()) 
			minList = *(iterator + i);
	}
	return minList;
}

int main()
{
	List * lists[] = {new List(2), new List(3), new List(5), new List(7)};
	List * min;
	__int64 n = 0, k = 1, j = 0, count = sizeof(lists)/sizeof(List *);
	
	std::cout << "Enter n:" << std::endl;
	std::cin >> n;
	while(n--)
	{
		min = minList(lists, count);
		while (min->peek() == k) {
			min->pop();
			min = minList(lists, count);
		}
		k = min->pop();
		std::cout << std::setw(4) << k;
		j++;
		for (int i = 0; i < count; ++i)
			(*(lists + i))->push(k);
	}
	
	std::cout << std::endl;
	system("pause");
	return 0;
}