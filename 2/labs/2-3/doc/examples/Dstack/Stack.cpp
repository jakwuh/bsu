#include <iostream>
//#include <stdafx.h>
using namespace std;

#include "Stack.h"

void Stack::push( int item )
{
	stack *tmp;
	tmp = new stack;
	tmp->pred = NULL;
	tmp->c = item;

	if ( top != NULL ) {
		tmp->pred = top;
		top = tmp;
	}
	else
		top = tmp;
}

int Stack::pop()
{
	int value;
		stack *tmp;
		tmp = top;
		value = top->c;
		top = top->pred;
		delete [] tmp;
	return value;
}

bool Stack::empty()
{return(top==NULL);}