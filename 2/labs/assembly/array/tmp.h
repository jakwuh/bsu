#ifndef _FUNCTIONS_
#define _FUNCTIONS_

struct Point
{
	int x, y;
};

// Транспонирует матрицу
+++ extern "C" void __cdecl transpose(int**, int, int);

// Возвращает длину наибольшой последовательности одинаковых элементов
---extern "C" int __cdecl find_max_sequence(int*, int);

// Исключает из массива повторяющиеся элементы
+++extern "C" void __cdecl unique_array(int*, int, int*, int&);

// Находит пересечение двух множеств, заданных массивами
+++extern "C" void __cdecl  array_conjuction(int*, int, int*, int, int*, int&);

// Находит количество уникальных элементов
--- extern "C" int __cdecl count_unique(int*, int);

// Сортирует два массива и сливает их в один
+++extern "C" int* __cdecl merge(int*, int, int*, int, int*, int&);

// Сортирует массив
+++ extern "C" void __cdecl sort_array(int*, int);

#endif