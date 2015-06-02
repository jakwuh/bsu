/**
 * @author RJ TM
 * @version 0.0.0
 * @date 07.03.2015
 */

#ifndef __LIST_DYNAMIC_H_INCLUDED__
#define __LIST_DYNAMIC_H_INCLUDED__

#include <iostream>
#include <stdexcept>
#include <cstdarg>

template <typename T>
class ListDynamic {
private:
	struct Node {
		Node(T const& _value, Node* _next = nullptr, Node* _prev = nullptr) 
		: value(_value), next(_next), prev(_prev){};
		T value;
		Node* next;
		Node* prev;
	};
	Node* head, *tail;
	std::size_t count;
public:
	ListDynamic();
	ListDynamic(ListDynamic const&);
	~ListDynamic();
	void push_front(T const&);
	void push_back(T const&);
	void pop_front();
	void pop_back();
	void clear();
	const T& front();
	const T& back();
	bool empty();
	std::size_t size();
	void print(std::ostream&);
};

template <typename T>
ListDynamic<T>::ListDynamic() : head(nullptr), tail(nullptr), count(0){}

template <typename T>
ListDynamic<T>::ListDynamic(ListDynamic const& ListDynamic) : head(nullptr), tail(nullptr), count(0)
{
	Node* tmp = ListDynamic.head;
	while (tmp) {
		push_back(tmp->value);
		tmp = tmp->next;
	}
}

template <typename T>
ListDynamic<T>::~ListDynamic() {
	clear();
}

template <typename T>
void ListDynamic<T>::clear()
{
	while(head)
		pop_back();
	head = tail = nullptr;
}

template<typename T>
const T& ListDynamic<T>::front()
{
	if (!head)
		throw std::runtime_error("ListDynamic<T>::front: ListDynamic empty");
	return head->value;
}

template<typename T>
const T& ListDynamic<T>::back()
{
	if (!tail)
		throw std::runtime_error("ListDynamic<T>::back: ListDynamic empty");
	return tail->value;
}


template <typename T>
void ListDynamic<T>::push_front(T const& data){
	Node* tmp = new Node(data, head, 0);
	if (head) head->prev = tmp;
	else tail = tmp;
	head = tmp;
	count++;
}

template <typename T>
void ListDynamic<T>::push_back(T const& data) {
	Node* tmp = new Node(data, 0, tail);
	if (tail) tail->next = tmp;
	else head = tmp;
	tail = tmp;
	count++;
}

template <typename T>
void ListDynamic<T>::pop_front(){
	if (!head)
		throw std::runtime_error("ListDynamic<T>::pop_front: empty ListDynamic");
	Node *tmp = head->next;
	if (tmp) tmp->prev = nullptr;
	else tail = nullptr;
	delete head;
	head = tmp;
	count--;
}

template <typename T>
void ListDynamic<T>::pop_back(){
	if (!tail) 
		throw std::runtime_error("ListDynamic<T>::pop_front: empty ListDynamic");
	Node *tmp = tail->prev;
	if (tmp) tmp->next = 0;
	else head = 0;
	delete tail;
	tail = tmp;
	count--;
}

template <typename T>
bool ListDynamic<T>::empty() {
	return !head;
}

template <typename T>
void ListDynamic<T>::print(std::ostream& out) {
	Node tmp = head;
	while (tmp) {
		out << tmp->value << std::endl;
		tmp = tmp->next;
	}
}

template <typename T>
std::size_t ListDynamic<T>::size()
{
	return count;
}

#endif