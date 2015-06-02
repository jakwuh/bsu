#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#define MATH_PI 3.14159265358
#define MATH_E 2.71828482846
#define LETTERS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define DIGIT_LETTERS "0123456789,."
#define SIGNS "-+/*^"

#include <cmath>
#include <algorithm>
#include <string>
#include "item.h"

namespace utils {

class BaseException {
 private:
  std::string desc;
 public:
  BaseException(std::string desc) : desc(desc){};
  std::string getDescription() { return desc; }
};

class ArithmeticException : public BaseException {
 public:
  ArithmeticException(std::string desc) : BaseException("Wrong arithmetic operation:\t" + desc){};
};

bool checkArithmeticDomain(const std::string&, number);

bool functionExists(const std::string&);

number calculateFunction(const std::string&, number);

char* mergeSigns(std::string, std::string);

} // namespace utils

#endif