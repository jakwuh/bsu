#include "list.h"

List::List() {
	head = 0;
}

List::List(const List& _list) {
	List();
	Node *tmp = _list.head;
	while (tmp){
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

List::~List() {
	while(head)
		pop_back();
}

void List::insert(int pos, const int& n) {
	if (pos == 0)
		push_front(n);
	else if (pos > 0) {
		Node *tmp = head;
		while(tmp && --pos)
			tmp = tmp->next;
		if (tmp == 0) throw Overflow();
		Node *newNode = new Node(n, tmp->next);
		tmp->next = newNode;
	}
	else throw BadArguments();
}

void List::remove(int pos) {
	if (pos == 0)
		pop_front();
	else if (pos > 0) {
		Node *tmp = head;
		while(tmp && --pos)
			tmp = tmp->next;
		if (!tmp || !tmp->next) throw Overflow();
		Node *oldNode = tmp->next;
		tmp->next = oldNode->next;
		delete oldNode;
	}
	else throw BadArguments();
}

void List::remove(Node* ptr) {
	if (ptr == head)
		pop_front();
	else {
		Node *tmp = head;
		while(tmp && tmp->next != ptr)
			tmp = tmp->next;
		if (!tmp || !ptr) throw Overflow();
		tmp->next = ptr->next;
		delete ptr;
	}
}

bool List::isEmpty() {
	return !head;
}

const Node& List::front() {
	if (isEmpty()) throw Empty();
	return *head;
}

const Node& List::back() {
	if (isEmpty()) throw Empty();
	Node *tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return *tmp;
}

void List::push_front(int n) {
	Node *tmp = new Node(n, head);
	head = tmp;
}

void List::push_back(int n) {
	Node *newNode = new Node(n, 0);
	Node *tmp = head;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp) tmp->next = newNode;
	else head = newNode;
}

void List::pop_front() {
	if (isEmpty()) throw Empty();
	Node *tmp = head->next;
	delete head;
	head = tmp;
}

void List::pop_back() {
	if (isEmpty()) throw Empty();
	Node *tmp = head;
	while (tmp->next && tmp->next->next)
		tmp = tmp->next;
	if (tmp->next) {
		delete tmp->next;
		tmp->next = 0;
	}
	else {
		delete tmp;
		head = 0;
	}
}

void List::print() {
	Node *tmp = head;
	while(tmp) {
		std::cout << std::setw(3) << tmp->value;
		tmp = tmp->next;
	}
}

int List::min() {
	if (isEmpty()) throw Empty();
	Node *tmp = head;
	int min = tmp->value;
	while(tmp){
		if (tmp->value < min) min = tmp->value;
		tmp = tmp->next;
	}
	return min;
}

Node* List::search(bool (*condition)(const void* el)) {
	Node *tmp = head, *result = 0;
	while(tmp){
		if (condition(tmp)) {
			result = tmp;
			break;
		}
		tmp = tmp->next;
	}
	return result;
}

void List::remove(bool (*condition)(const void*)) {
	Node *tmp = head, *next = 0;
	while(tmp){
		next = tmp->next;
		if (condition(tmp))
			remove(tmp);
		tmp = next;
	}
}

int List::sum(int k) {
	int s = 0;
	Node *tmp = head;
	while (k--){
		if (!tmp) throw BadArguments();
		s += tmp->value;
		tmp = tmp->next;
	}
	return s;
}