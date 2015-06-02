#include <iostream>
#include "stack.h"
//Выполнил Яскевич Сергей
ArrayStack::ArrayStack(const int& _size)
{
	size=_size;
	p=new int[size];
	top=0;
}
ArrayStack::~ArrayStack()
{
	size=0;
	top=0;
	delete[] p;
	p=NULL;
}


bool ArrayStack::isFull()
{
	if(top==(size))
		return true;
	return false;
}

bool ArrayStack::isEmpty()
{
	if(top==0)
		return true;
	return false;
}

void ArrayStack::push(const int& n)
{
	if(!isFull())
	{
		p[top]=n;
		top++;
	}
}

int ArrayStack::pop()
{
	if(!isEmpty())
	{
		int n;
		top--;
		n=p[top];
		return n;
	}
	return 0;
}

ArrayStack::ArrayStack(const ArrayStack& s)
{
	size=s.size;
	top=s.top;
	p=new int[size];
	for(int i=0; i<top; i++)
	{
		p[i]=s.p[i];
	}
}