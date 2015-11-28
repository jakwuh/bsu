#ifndef __ITEM_H_INCLUDED__
#define __ITEM_H_INCLUDED__

typedef struct Item {
  Item() : x(), next(NULL){};
  Item(int x) : x(x), next(NULL){};
  int x;
  struct Item* next;
} Item;

#endif