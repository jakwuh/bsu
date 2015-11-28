#include "deque.h"

Deque::Deque() {
	head = tail = 0;
}

Deque::Deque(const Deque& _deque) {
	Deque();
	Node *tmp = _deque.head;
	while (tmp){
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

Deque::~Deque() {
	while(head)
		pop_back();
}

bool Deque::isEmpty() {
	return !head;
}

const Node& Deque::front() {
	if (isEmpty()) throw Empty();
	return *head;
}

const Node& Deque::back() {
	if (isEmpty()) throw Empty();
	return *tail;
}

void Deque::push_front(int n) {
	Node *tmp = new Node(n, head, 0);
	if (head) head->prev = tmp;
	else tail = tmp;
	head = tmp;
}

void Deque::push_back(int n) {
	Node *tmp = new Node(n, 0, tail);
	if (tail) tail->next = tmp;
	else head = tmp;
	tail = tmp;
}

void Deque::pop_front() {
	if (isEmpty()) throw Empty();
	Node *tmp = head->next;
	if (tmp) tmp->prev = 0;
	else tail = 0;
	delete head;
	head = tmp;
}

void Deque::pop_back() {
	if (isEmpty()) throw Empty();
	Node *tmp = tail->prev;
	if (tmp) tmp->next = 0;
	else head = 0;
	delete tail;
	tail = tmp;
}