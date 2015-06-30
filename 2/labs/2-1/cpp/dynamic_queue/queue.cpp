#include "queue.h"

Queue::Queue() { head = tail = 0; }

Queue::~Queue() {
  struct Item* next;
  while (head) {
    next = head->next;
    delete head;
    head = next;
  }
}

bool Queue::empty() { return !head; }

void Queue::push(Item& item) {
  struct Item* i = new Item(item);
  i->next = 0;

  if (tail) {
    tail->next = i;
    tail = i;
  } else {
    head = tail = i;
  }
}

struct Item& Queue::front() {
  return *head;
}

void Queue::pop() {
  if (head != tail) {
    struct Item* tmp = head;
    head = head->next;
    delete tmp;
  } else {
    delete head;
    head = tail = 0;
  }
}