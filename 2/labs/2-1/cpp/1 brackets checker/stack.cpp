#include <iostream>
#include "stack.h"

Stack::Stack()
{
	head = NULL;
}

Stack::~Stack()
{
	struct Item * prev;
	while(head){
		prev = head->prev;
		delete	 head;
		head = prev;
	}
}

char Stack::peek()
{
	return head ? head->value : 0;
}

void Stack::push(char value)
{
	char prevValue = head ? head->value : 0;
	if (value == ')' && prevValue == '(' || value == '}' && prevValue == '{' || value == ']' && prevValue == '[')
		pop();
	else {
		Item * i = new Item();
		i->value = value;
		i->prev = head;
		head = i;
	}
}

char Stack::pop()
{
	if (!head) return 0;
	Item * tmp = head;
	char value = head->value;
	head = head->prev;
	delete tmp;
	return value;
}