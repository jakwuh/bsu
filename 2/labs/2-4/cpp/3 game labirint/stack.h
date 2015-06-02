#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

struct Empty{};
struct Full{};

template <class T>
class ArrayStack
{
private:
	int size, top;
	T* p;
public:
	ArrayStack(int); 
	ArrayStack(const ArrayStack&);
	~ArrayStack();
	void push(const T&);
	T& peek();
	void pop();
	bool isEmpty();
	bool isFull();
};

template <class T>
ArrayStack<T>::ArrayStack(int _size) : size(_size) {
	p = new T[size];
	top = -1;
}

template <class T>
ArrayStack<T>::ArrayStack(const ArrayStack& s) {
	ArrayStack(s.size);
	for (int i = 0; i <= top; ++i)
		push(s.p[i]);
}

template <class T>
ArrayStack<T>::~ArrayStack() {
	delete[] p;
}

template <class T>
bool ArrayStack<T>::isEmpty() {
	return top == -1;
}

template <class T>
bool ArrayStack<T>::isFull() {
	return top == size - 1;
}

template <class T>
void ArrayStack<T>::pop() {
	if (isEmpty())
		throw Empty();
	top--;
}

template <class T>
T& ArrayStack<T>::peek() {
	if (isEmpty())
		throw Empty();
	return p[top];
}

template <class T>
void ArrayStack<T>::push(const T& n) {
	if (isFull())
		throw Full();
	p[++top] = n;
}

#endif


