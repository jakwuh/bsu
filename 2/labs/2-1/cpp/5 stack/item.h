#ifndef __ITEM_H_INCLUDED__
#define __ITEM_H_INCLUDED__

struct Item {
  Item() : x(), prev(0){};
  Item(double x) : x(x), prev(0){};
  double x;
  struct Item* prev;
};

#endif