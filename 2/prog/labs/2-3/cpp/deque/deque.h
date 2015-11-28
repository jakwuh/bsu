#ifndef __DEQUE_H_INCLUDED__
#define __DEQUE_H_INCLUDED__

class Empty{};
class Overflow{};

struct Node
{
	Node(int _value = 0, Node* _next = 0, Node* _prev = 0) : value(_value), next(_next), prev(_prev){};
	int value;
	Node *next, *prev;
};

class Deque
{
private:
	Node *head, *tail;
public:
	Deque();
	Deque(const Deque&);
	~Deque();
	const Node& front();
	const Node& back();
	void push_front(int);
	void push_back(int);
	void pop_front();
	void pop_back();
	bool isEmpty();
};

#endif