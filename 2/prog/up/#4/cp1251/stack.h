#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

#include <list>
#include <iostream>

template <class T, class Container = std::list<T>>
class Stack
{
public:
	Stack(){ c = Container(); }
	Stack(Container const& xc){ c = xc };
	~Stack(){};
	bool empty(){ return size() == 0; };
	unsigned size(){ return c.size(); };
	T& top(){ return c.back(); };
	void push(T const& t){ c.push_back(t); };
	void pop(){ c.pop_back(); };
	void swap(Stack& s){ c.swap(s.c); };
	void clear(){ c.erase(c.begin(), c.end()); };
	friend std::ostream& operator << (std::ostream& out, Stack s) {
		for (auto it : s.c) out << s.c;
		return out;
	};
	friend std::istream& operator >> (std::istream& in, Stack s) {
		T tmp;
		while (in >> tmp) s.push(tmp);
		return in;
	}
	T production(){
		if (empty()) return 0;
		auto it = c.begin;
		T tmp = *it;
		for (++it != c.end()) tmp *= *it;
		return tmp;
	}
protected:
	Container c;
};

#endif