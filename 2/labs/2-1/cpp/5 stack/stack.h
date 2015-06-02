#ifndef __STACK_H_INCLUDED__
#define __STACK_H_INCLUDED__

#include "item.h"

class Stack {
private:
  Item* head;

public:
  Stack();
  ~Stack();
  void push(Item&);
  void pop();
  Item& top();
  bool empty();
};

#endif