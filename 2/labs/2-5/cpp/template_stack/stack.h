#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

#include <stdexcept>

template <typename T>
class Stack
{
private:
	struct Node
	{
		Node(T const& _value, Node* next = nullptr) : value(_value), next(next){};
		T value;
		Node* next;
	};
	Node* head;
	std::size_t count;
public:
	Stack() : head(nullptr), count(0){};
	Stack(Stack const&);
	void push(T const&);
	void pop();
	const T& top() const; // const T& -  i promise i'll not change the top value
	bool empty() const;
	std::size_t size() const;
};

template <typename T>
Stack<T>::Stack(Stack<T> const& s)
{
	Node* tmp = s.head;
	count = s.count;
	while (tmp) {
		push(tmp);
		tmp = tmp->next;
	}
}

template <typename T>
void Stack<T>::push(T const& t)
{
	if (!head)
		head = new Node(t);
	else
		head = new Node(t, head);
	++count;
}

template <typename T>
void Stack<T>::pop()
{
	if (!head) {
		throw std::runtime_error("Stack<T>::pop: empty stack");
	} else {
		Node* tmp = head->next;
		head->next = nullptr;
		delete head;
		head = tmp;
		--count;
	}
}

template <typename T>
const T& Stack<T>::top() const
{
	if (!head)
		throw std::runtime_error("Stack<T>::top: empty stack");
	else
		return head->value;
}

template <typename T>
bool Stack<T>::empty() const
{
	return !count;
}

template <typename T>
std::size_t Stack<T>::size() const
{
	return count;
}

#endif