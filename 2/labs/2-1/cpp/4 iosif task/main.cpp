// Аквух Джеймс
// 9.02.2015
// Задача Иосифа

#include <iostream>
#include <queue>
#include "item.h"
//#include "queue.h"

typedef std::queue<Item> Queue;

using namespace std;

int main() {
  int n = 0, m = 0, i = 0;

  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  scanf("%d %d", &n, &m);
  Queue q;

  for (int i = 1; i <= n; i++)
	q.push(Item(i));

  while (!q.empty()) {
	for (int i = 0; i < m - 1; i++) {
		q.push(q.front());
		q.pop();
	}
	n = q.front().x;
	cout << n << ' ';
	q.pop();
  }

  system("pause");
  return 0;
}