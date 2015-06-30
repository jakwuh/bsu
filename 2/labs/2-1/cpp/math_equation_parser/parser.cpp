#include "parser.h"

Parser::Parser() : in(new Queue), out(new Queue), variables(new Queue) {
  variables->push(Item(variable_t, "pi", MATH_PI));
  variables->push(Item(variable_t, "e", MATH_E));
}

Parser::~Parser() {
  delete out;
  delete in;
  delete variables;
}

void Parser::setVariables(Queue* vars) { variables = vars; }

void Parser::parse(std::string str) {
  while (str.find_first_of(" \n\r\t\0") != std::string::npos)
    str.erase(str.find_first_of(" \n\r\t\0"), 1);
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  while (str.size()) {
    int i = str.size();
    this->parseBracket(str);
    this->parseNumber(str);
    this->parseSign(str);
    this->parseVariable(str);
    this->parseFunction(str);
    if (i == str.size())
      throw ::utils::BaseException(
          "Cannot parse equation due to unknown symbols");
  }
  this->generatePolishNotation();
}

void Parser::parseBracket(std::string& str) {
  char* c = new char();
  strcpy(c, str.substr(0, 1).c_str());
  if (strspn(c, "[("))
    in->push(Item(left_bracket_t));
  else if (strspn(c, "])"))
    in->push(Item(right_bracket_t));
  else
    return;
  str.erase(0, 1);
}

void Parser::parseNumber(std::string& str) {
  std::string tmp = str.substr(0, str.find_first_not_of(DIGIT_LETTERS));
  while (tmp.find_first_of(",") != std::string::npos)
    tmp.at(tmp.find_first_of(",")) = '.';	
  if (tmp.size() == 0) return;
  number value = std::stold(tmp);
  in->push(Item(number_t, value));
  str.erase(0, str.find_first_not_of(DIGIT_LETTERS));
}

void Parser::parseSign(std::string& str) {
  char* sign = new char();
  strcpy(sign, str.substr(0, 1).c_str());
  if (strspn(sign, SIGNS)) {
    if (!in->empty() && in->back().type == sign_t) {
      sign = ::utils::mergeSigns(in->back().name, sign);
      in->back().name = sign;
    } else
      in->push(Item(sign_t, sign));
    str.erase(0, 1);
  }
}

void Parser::parseVariable(std::string& str) {
  std::string tmp = str.substr(0, str.find_first_not_of(LETTERS));
  if (tmp.size() == 0 || ::utils::functionExists(tmp)) return;
  str.erase(0, str.find_first_not_of(LETTERS));
  Item* variable = find(variables, tmp);
  if (variable)
    in->push(*variable);
  else {
    variable = new Item(variable_t, tmp, this->requestVariable(tmp));
    in->push(*variable);
    variables->push(*variable);
  }
}

void Parser::parseFunction(std::string& str) {
  std::string tmp = str.substr(0, str.find_first_not_of(LETTERS));
  if (!::utils::functionExists(tmp)) return;
  str.erase(0, str.find_first_not_of(LETTERS) + 1);
  int i = 0, openCount = 1, closeCount = 0;
  while (openCount != closeCount) {
    if (str.substr(i, 1).find_first_of("[(") != std::string::npos) openCount++;
    if (str.substr(i, 1).find_first_of(")]") != std::string::npos) closeCount++;
    i++;
    if (i >= str.size() && openCount != closeCount)
      throw ::utils::BaseException(
          "Cannot parse arithmetic function due to wrong equation");
  }
  std::string equation = str.substr(0, i - 1);
  str.erase(0, i);
  Parser* tmpParser = new Parser;
  tmpParser->setVariables(variables);
  tmpParser->parse(equation);
  in->push(Item(variable_t, tmp + "( " + tmpParser->getEquation() + ")",
            ::utils::calculateFunction(tmp, tmpParser->calculate())));
}

number Parser::requestVariable(const std::string& name) {
  char buffer[1024];
  printf("Please, provide value for \"%s\":\t", name.c_str());
  gets(buffer);
   while (strstr(buffer, ","))
	   *strstr(buffer, ",") = '.';
  std::string tmp = buffer;
  return std::stold(tmp);
}

void Parser::generatePolishNotation() {
  bool minusForTheNumber = false;
  type_t prev_type = null_t;
  Queue *inCopy = new Queue;
  *inCopy = *in;
  Item* i;
  Stack *tmp = new Stack;
  out = new Queue();
  while (!inCopy->empty()) {
    i = &inCopy->front();
    switch (i->type) {
      case number_t:
      case variable_t:
        i->value = i->value * (1 - 2 * minusForTheNumber);
        minusForTheNumber = false;
        out->push(*i);
        break;
      case left_bracket_t:
        tmp->push(*i);
        break;
      case right_bracket_t:
        while (!tmp->empty() && tmp->top().type != left_bracket_t) {
          out->push(tmp->top());
          tmp->pop();
        }
        if (tmp->empty())
          throw ::utils::BaseException(
              "Cannot parse equation due to wrong brackets");
        tmp->pop();
        break;
      case sign_t:
        if (i->name.find_first_of("+-") != std::string::npos && (prev_type == null_t || prev_type == left_bracket_t))
          minusForTheNumber = (minusForTheNumber != (i->name == "-"));
        else {
          while (!tmp->empty() && tmp->top().type == sign_t &&
            tmp->top().getPriority() >= i->getPriority()) {
            out->push(tmp->top());
            tmp->pop();
          }
          tmp->push(*i);
        }
        break;
    }
    prev_type = i->type;
    inCopy->pop();
  }
  while (!tmp->empty()) {
    if (tmp->top().type != sign_t)
      throw ::utils::BaseException("Cannot parse due to errors in equation");
    out->push(tmp->top());
    tmp->pop();
  }
  delete tmp;
}

number Parser::calculate() {
  Stack *tmp = new Stack;
  Queue * queueCopy = new Queue;
  *queueCopy = *out;
  Item* i;
  number a, b, res = 0;

  while (!queueCopy->empty()) {
    i = &queueCopy->front();
    if (i->type == number_t || i->type == variable_t) {
      tmp->push(*i);
    } else {
      if (tmp->empty())
        throw ::utils::BaseException("Cannot calculate wrong equation");
      b = tmp->top().value;
      tmp->pop();
      if (tmp->empty())
        throw ::utils::BaseException("Cannot calculate wrong equation");
      a = tmp->top().value;
      tmp->pop();
      if (i->name == "+")
        res = a + b;
      else if (i->name == "-")
        res = a - b;
      else if (i->name == "*")
        res = a * b;
      else if (i->name == "/")
        res = a / b;
      else if (i->name == "^")
        res = pow(a, b);
      else
        throw ::utils::BaseException("Cannot calculate wrong equation");
      tmp->push(Item(number_t, res));
    }
    queueCopy->pop();
  }
  if (tmp->empty())
    throw ::utils::BaseException("Cannot calculate wrong equation");
  struct Item result = tmp->top();
  tmp->pop();
  if (!tmp->empty())
    throw ::utils::BaseException("Cannot calculate wrong equation");
  return result.value;
}

std::string Parser::queueToString(Queue* queue) {
  Queue* queueCopy = new Queue;
  *queueCopy = *queue;
  std::string str = "";
  while (!queueCopy->empty()) {
    str += queueCopy->front().to_string() += " ";
    queueCopy->pop();
  }
  return str;
}

std::string Parser::getEquation() { return queueToString(in); }

std::string Parser::getPolishNotation() { return queueToString(out); }

Item* Parser::find(Queue* queue, std::string name) {
  Item* i = queue->empty() ? NULL : &queue->front();
  if (!i) return NULL;
  std::string firstName = i->name;
  do{
	queue->push(queue->front());
	queue->pop();
	i = &queue->front();
    if (i->name == name) return i;
  } while (i->name != firstName);
  return NULL;
}