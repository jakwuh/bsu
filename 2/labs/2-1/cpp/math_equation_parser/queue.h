#ifndef __QUEUE_H_INCLUDED__
#define __QUEUE_H_INCLUDED__

#include "utils.h"

class Queue {
private:
  struct Item* head, *tail;

public:
  Queue();
  ~Queue();
  void push(Item&);
  void pop();
  bool operator =(Queue& queue);
  struct Item& front();
  struct Item& back();
  bool empty();
};

#endif