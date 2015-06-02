#ifndef __ITEM_H_INCLUDED__
#define __ITEM_H_INCLUDED__

#include <string>

typedef enum {
  null_t,
  number_t,
  variable_t,
  left_bracket_t,
  sign_t,
  right_bracket_t,
} type_t;

typedef long double number;

struct Item {
  Item(){};
  Item(type_t type) : type(type){};
  Item(type_t type, number value) : type(type), value(value){};
  Item(type_t type, std::string name, number value = 0)
      : type(type), name(name), value(value){};
  type_t type;
  number value;
  std::string name;
  Item* prev, *next;
  std::string to_string();
  short getPriority();
};

#endif