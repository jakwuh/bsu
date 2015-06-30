#include "stack.h"

Stack::Stack() { head = 0; }

Stack::~Stack() {
  Item* prev;
  while (head) {
    prev = head->prev;
    delete head;
    head = prev;
  }
}

bool Stack::empty() { return !head; }

Item& Stack::top() { 
  return *head; 
}

void Stack::push(Item& item) {
  Item *i = new Item(item);
  i->prev = head;
  head = i;
}

void Stack::pop() {
  Item* tmp = head;
  head = head->prev;
  delete tmp;
}