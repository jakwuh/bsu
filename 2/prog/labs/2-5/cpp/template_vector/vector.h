#ifndef __VECTOR_H_INCLUDED__
#define __VECTOR_H_INCLUDED__

#include <iostream>
#include <malloc.h>
#include "error.h"

template <typename T>
class Vector
{
private:
	int n;
	T* ptr;
public:
	Vector(int = 0);
	Vector(int, T);
	Vector(const Vector&);
	~Vector(){ delete ptr; }
	Vector& operator = (const Vector&);
	T& operator [] (int);
	int size() { return n; }
	void resize(int _n);
	template <typename T>
	friend std::istream& operator >> (std::istream&, Vector&);
	template <typename T>
	friend std::ostream& operator << (std::ostream&, const Vector&);
	template <typename T>
	friend Vector operator + (Vector&, Vector&);
	template <typename T>
	friend bool operator == (Vector&, Vector&);
	template <typename T>
	friend bool operator != (Vector&, Vector&){ return !(v1 == v2); }
	class Iterator;
	Iterator begin(){ return Iterator(ptr); }
	Iterator end(){ return Iterator(ptr + n); }
	static void fill(Iterator first, Iterator last, const T& value);
	void erase(Iterator first, Iterator last);
	void erase(Iterator position){ erase(position, ++position); }
	void clear(){ erase(begin(), end()); }
	class Iterator {
	private:
		T* ptr;
	public:
		Iterator() : ptr(0){};
		Iterator(T* _ptr) : ptr(_ptr){};
		Iterator(const Iterator& it) : ptr(it.ptr){};
		~Iterator(){ ptr = 0; };
		Iterator& operator = (const Iterator& it){ ptr = it.ptr; return *this; };
		Iterator& operator ++ (){ ++ptr; return *this; };
		Iterator operator ++ (int) { Iterator it(ptr); ptr++; return it; }
		Iterator operator + (int i){ Iterator it(ptr); while (i--) it++; return it; }
		T& operator*() const { return *ptr; };
		T* operator->() const { return ptr; };
		bool operator == (const Iterator& it) { return ptr == it.ptr; }
		bool operator != (const Iterator& it) { return ptr != it.ptr; }
	};
};

template <typename T>
Vector<T>::Vector(int _n) : n(_n)
{
	if (n < 0) throw BadDimension();
	ptr = (T*) calloc(n, sizeof(T));
	fill(this->begin(), this->end(), T());
}

template <typename T>
Vector<T>::Vector(int _n, T t) : n(_n)
{
	if (n < 0) throw BadDimension();
	ptr = (T*) calloc(n, sizeof(T));
	fill(this->begin(), this->end(), T(t));
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v)
{
	(*this).operator = (v);
}

template <typename T>
void Vector<T>::resize(int _n)
{
	if (_n < 0) throw BadIndex();
	int oldN = n;
	n = _n;
	ptr = (T*) realloc(ptr, sizeof(T) * n);
	if (oldN < n)
		fill(this->begin() + oldN, this->end(), T());
}

template <typename T>
Vector<T>& Vector<T>::operator = (const Vector<T>& v)
{
	n = v.n;
	ptr = (T*) std::memcpy(calloc(n, sizeof(T)), v.ptr, sizeof(T) * n);
	return *this;
}

template <typename T>
T& Vector<T>::operator [] (int i)
{
	if (i < 0 || i >= n) throw BadIndex();
	return ptr[i];
}

template <typename T>
std::istream& operator >> (std::istream &in, Vector<T> &v)
{
	for (int i = 0; i < v.n; i++)
		in >> v[i];
	return in;
}

template <typename T>
std::ostream& operator << (std::ostream &out, const Vector<T> &v)
{
	out << '\n';
	for (int i = 0; i < v.n; i++)
		out << '\t' << v.ptr[i];
	return out;
}

template <typename T>
Vector<T> operator + (Vector<T>& v1, Vector<T>& v2)
{
	if (v1.n != v2.n) throw BadDimension();
	Vector<T> tmp(v1.n);
	for (int i = 0; i < v1.n; ++i)
		tmp[i] = v1[i] + v2[i];
	return tmp;
}

template <typename T>
bool operator == (Vector<T> &v1, Vector<T> &v2)
{
	if (v1.n != v2.n) return false;
	for (int i = 0; i < v1.n; ++i)
		if (v1[i] != v2[i])
			return false;
	return true;
}

template <typename T>
void Vector<T>::fill(Iterator first, Iterator last, const T& value)
{
	while (first != last)
		*first++ = value;
}

template <typename T>
void Vector<T>::erase(Iterator first, Iterator last)
{
	int _n = n;
	Iterator check(first);
	while(check++ != last)
		_n--;
	while (last != end())
		*first++ = *last++;
	n = _n;
}

#endif