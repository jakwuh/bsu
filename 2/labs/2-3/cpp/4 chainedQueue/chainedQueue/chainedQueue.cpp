#include "chainedQueue.h"

ChainedQueue::ChainedQueue(int _size = 100) : size(_size) {
	p = new int[size];
	head = n = 0;
}

ChainedQueue::ChainedQueue(const ChainedQueue& q) {
	ChainedQueue(q.size);
	int i = q.head, n = size;
	while(n--){
		push(q.p[i]);
		i++;
		if (i >= q.size) i-=size;
	}
}

ChainedQueue::~ChainedQueue() {
	delete[] p;
}

const int& ChainedQueue::peek() {
	if (isEmpty()) throw Empty();
	return p[head];
}

void ChainedQueue::push(int x) {
	if (isFull()) throw Full();
	p[head + n >= size ? head + n - size : head + n] = x;
	n++;
}

void ChainedQueue::pop() {
	if (isEmpty()) throw Empty();
	head++;
	n--;
	if (head >= size) head -= size;
}

bool ChainedQueue::isEmpty() {
	return n == 0;
}

bool ChainedQueue::isFull() {
	return n == size;
}