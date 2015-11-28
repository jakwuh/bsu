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
  i->next = i->prev = 0;

  if (tail) {
    tail->next = i;
    tail = i;
  } else {
    head = tail = i;
  }
}

struct Item& Queue::front() {
  if (!head) throw ::utils::BaseException("Empty queue");
  return *head;
}

struct Item& Queue::back() {
  if (!tail) throw ::utils::BaseException("Empty queue");
  return *tail;
}

void Queue::pop() {
  if (!head) throw ::utils::BaseException("Empty queue");
  if (head != tail) {
    struct Item* tmp = head;
    head = head->next;
    delete tmp;
  } else {
    delete head;
    head = tail = 0;
  }
}

bool Queue::operator = (Queue& queue) {
  Item* head = queue.empty() ? NULL : &queue.front();
  while (head) {
    push(*head);
    head = head->next;
  }
  return true;
}