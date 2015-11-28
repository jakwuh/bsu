#include "queue.h"

Queue::Queue()
{
    head = tail = 0;
}

Queue::~Queue()
{
    struct Item* next;
    while (head) {
        next = head->next;
        delete head;
        head = next;
    }
}

bool Queue::isEmpty()
{
	return !head;
}

void Queue::push(int x, int y)
{
	struct Item * i = new Item;
    i->x = x;
    i->y = y;

    if (tail) {
        tail->next = i;
        tail = i;
    } else {
    	head = tail = i;
    }
}

void Queue::peek(int& x, int& y)
{
	if (head) {
		x = head->x;
		y = head->y;
	}
}

void Queue::pop(int& x, int& y)
{
	struct Item * tmp;
	peek(x, y);
	if (head != tail){
		tmp = head;
		if (head->next) head = head->next;
		delete tmp;
	} else if (head) {
		delete head;
		head = tail = 0;
	}
}