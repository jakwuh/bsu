#include "stack.h"

Stack::Stack() { head = 0; }

Stack::~Stack() {
  struct Item prev;
  while (head) {
    prev = *head->prev;
    delete head;
    head = &prev;
  }
}

bool Stack::empty() { return !head; }

Item& Stack::top() { 
  if (!head) throw ::utils::BaseException("Empty stack");
  return *head; 
}

void Stack::push(Item& item) {
  Item *i = new Item(item);
  i->next = i->prev = 0;
  i->prev = head;
  head = i;
}

void Stack::pop() {
  if (!head) throw ::utils::BaseException("Empty stack");
  Item* tmp = head;
  head = head->prev;
  delete tmp;
}