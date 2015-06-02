 // Аквух Джеймс
 // 11.02.2015
 // Проверка расстановки скобок

#include <iostream>
#include <cstring>
#include "stack.h"

using namespace std;

int main()
{
	char str[100], i = 0;
	char mask[] = "[{(]})";
	Stack * stack = new Stack();

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%s", str);

	while (i < strlen(str)) {
		if (strchr(mask, str[i])) 
			stack->push(str[i]);
		i++;
	}
	
	cout << (stack->pop() == 0 ? "right" : "wrong") << endl;
	return 0;
}