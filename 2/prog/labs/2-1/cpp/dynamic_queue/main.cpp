// Аквух Джеймс
// 12.02.2015
// Использование динамической очереди.
//
// Задан текстовый файл Input.txt, в котором есть некоторые числа, каждое число
// в отдельной строке.
// Создать  две очереди,  в первой – простые числа, во второй - палиндромы.
// Построить новую очередь, включив в нее по одному  разу элементы,
// которые входят хотя бы в одну из очередей Queue1 или Queue2.
// Результат записать в текстовый  файл.

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "item.h"

//#include <queue>
//typedef std::queue<Item> Queue;
#include "queue.h"

inline bool isPrime(int);
inline bool isPalindrom(int);
void print(Queue*, std::string);
Item* find(Queue&, int);

int main() {
  int n = 0, i;
  Queue* palindroms = new Queue,
	  *primes = new Queue,
	  *mergedQueue = new Queue;

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  while (scanf("%d", &i) == 1) {
    if (isPalindrom(i)) {
      palindroms->push(Item(i));
      if (!find(*mergedQueue, i)) mergedQueue->push(Item(i));
    }
    if (isPrime(i)) {
      primes->push(Item(i));
      if (!find(*mergedQueue, i)) mergedQueue->push(Item(i));
    }
  }

  print(primes, "Primes");
  print(palindroms, "Palindroms");
  print(mergedQueue, "Merged queue");

  return 0;
}

inline bool isPrime(int n) {
	int i = 2;
	bool isPrime = true;
	while (i * i <= n)
		if (n % i++ == 0)  isPrime = false;
	return isPrime;
}

inline bool isPalindrom(int n) {
  int k = 0, d = n;
  while (d > 0) {
    k = k * 10 + d % 10;
    d /= 10;
  }
  return n == k;
}

Item* find(Queue& queue, int i) {
  Item* iterator = queue.empty() ? NULL : &queue.front();
  while (iterator) {
    if (iterator->x == i) return iterator;
    iterator = iterator->next;
  }
  return NULL;
}

void print(Queue* queue, std::string caption) {
  std::cout << ("\n" + caption + ":\t");
  while (!queue->empty()) {
	std::cout << std::setw(3) << queue->front().x;
	queue->pop();
  }
}