// Аквух Джеймс
// 16.02.2015
// Джеймс Аквух
// Задача 1.2
// Описать процедуру, которая подсчитывает количество элементов стека, у которых
// равные "соседи".

#include <iostream>
#include "item.h"

#include "stack.h"
// #include <stack>
// typedef std::stack<Item> Stack;


int countEqual(Stack&);

int main() {
  Stack stack;
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  float d;
  while (scanf("%f", &d) == 1) stack.push(*(new Item(d)));
	std::cout << countEqual(stack);
  return 0;
}

int countEqual(Stack& stack) {
  Stack tmp;
  Item prev;
  int count = 0;
  while (!stack.empty()) {
    if (!tmp.empty() && tmp.top().x == stack.top().x) count++;
    tmp.push(stack.top());
    stack.pop();
  }
  while (!tmp.empty()) {
    stack.push(tmp.top());
    tmp.pop();
  }
  return count;
}