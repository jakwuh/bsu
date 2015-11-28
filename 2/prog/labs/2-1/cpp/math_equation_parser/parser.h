#ifndef __PARSER_H_INCLUDED__
#define __PARSER_H_INCLUDED__

#include <string>
#include <cstring>
#include <iostream>


#include "utils.h"
#include "stack.h"
#include "queue.h"

//#include <stack>
//#include <queue>
//typedef std::stack<Item> Stack;
//typedef std::queue<Item> Queue;

class Parser {
 private:
  Queue* out, *in, *variables;

 public:
  Parser();
  ~Parser();
  void generatePolishNotation();
  number calculate();
  static std::string queueToString(Queue*);
  std::string getEquation();
  std::string getPolishNotation();
  void setVariables(Queue*);
  void parse(std::string);
  void parseBracket(std::string&);
  void parseSign(std::string&);
  void parseNumber(std::string&);
  void parseVariable(std::string&);
  void parseFunction(std::string&);
  number requestVariable(const std::string&);
  Item* find(Queue*, std::string);
};

#endif