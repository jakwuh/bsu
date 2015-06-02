#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__

#include <iostream>
#include <iomanip>

class Error{};
class Overflow : public Error{};
class BadArguments : public Error{};
class Empty : public Error{};

struct Node
{
	Node(int _value = 0, Node *_next = 0) : value(_value), next(_next) {};
	int value;
	struct Node* next;
};

class List
{
private:
	Node *head;
public:
	List();
	List(const List&);
	~List();
	void insert(int, const int&);
	void remove(int);
	void remove(Node*);
	void remove(bool (*condition)(const void*));	
	Node* search(bool (*condition)(const void*));
	const Node& front();
	const Node& back();
	void push_front(int);
	void push_back(int);
	void pop_front();
	void pop_back();
	bool isEmpty();
	void print();
	int min();
	int sum(int);
};

#endif