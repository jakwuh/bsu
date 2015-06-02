#ifndef __QUEUE_H_INCLUDED__
#define __QUEUE_H_INCLUDED__

#include <iostream>
#include <string>
#include "item.h"

class Queue {
 private:
  struct Item* head, *tail;

 public:
  Queue();
  ~Queue();
  void push(Item&);
  void pop();
  struct Item& front();
  bool empty();
};

#endif