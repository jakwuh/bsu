// static array stack
// example of usage:
// ::StackStatic<std::string> as;
// if (!as.full()) as.push("text_here");
// if (!as.empty()) as.top();
// as.pop();

#ifndef __STACK_STATIC_H_INCLUDED__
#define __STACK_STATIC_H_INCLUDED__

#define DEFAULT_SIZE 100000

#include <stdexcept>

template <typename T>
class StackStatic
{
private:
	int size, top;
	T* ptr;
public:
	StackStatic(int /*size*/ = DEFAULT_SIZE); 
	StackStatic(const StackStatic& /*stack*/);
	~StackStatic();
	void push(T const& /*el*/);
	const T& top() const;
	void pop();
	bool empty() const;
	bool full() const;
};

template <typename T>
StackStatic<T>::StackStatic(int _size) : size(_size) 
{
	ptr = new T[size];
	top = -1;
}

template <typename T>
StackStatic<T>::StackStatic(const StackStatic& s)
{
	size = s.size
	ptr = new T[size];
	top = s.top;
	for (int i = 0; i <= top; ++i)
		ptr[i] = s.ptr[i];
}

template <typename T>
StackStatic<T>::~StackStatic() 
{
	delete[] ptr;
}

template <typename T>
bool StackStatic<T>::empty() const
{
	return top == -1;
}

template <typename T>
bool StackStatic<T>::full() const
{
	assert(top < size);
	return top == size - 1;
}

template <typename T>
void StackStatic<T>::pop() 
{
	if (top == -1)
		throw std::runtime_exception("StackStatic<T>::pop: empty stack");
	--top;
}

template <typename T>
const T& StackStatic<T>::top() const
{
	if (top == -1)
		throw std::runtime_exception("StackStatic<T>::top: empty stack");
	return ptr[top];
}

template <typename T>
void StackStatic<T>::push(T const& el) 
{
	if (top == size - 1)
		throw std::runtime_exception("StackStatic<T>::push: full stack");
	ptr[++top] = el;
}


#endif


