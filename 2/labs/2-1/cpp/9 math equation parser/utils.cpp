#include "utils.h"

using namespace utils;

bool ::utils::checkArithmeticDomain(const std::string& name, number x) {
  if (name == "asin" && x < -MATH_PI / 2 && x > MATH_PI / 2) return false;
  if (name == "acos" && x < 0 / 2 && x > MATH_PI) return false;
  if ((name == "log" || name == "ln" || name == "log10") && x <= 0) return false;
  if (name == "sqrt" && x < 0) return false;
  return true;
}

bool ::utils::functionExists(const std::string& name) {
  if (name.size() == 0) return false;
  if (name == "sin") return true;
  if (name == "cos") return true;
  if (name == "tan") return true;
  if (name == "asin") return true;
  if (name == "acos") return true;
  if (name == "atan") return true;
  if (name == "log") return true;
  if (name == "ln") return true;
  if (name == "log10") return true;
  if (name == "sqrt") return true;
  if (name == "exp") return true;
  return false;
}

number utils::calculateFunction(const std::string& name, number x) {
  if (!functionExists(name))
  	throw BaseException("Uknown arithmetic function call: " + name);
  if (!checkArithmeticDomain(name, x))
    throw ArithmeticException(name + "(" + std::to_string(x) + ")");
  if (name == "sin") return sin(x);
  if (name == "cos") return cos(x);
  if (name == "tan") return tan(x);
  if (name == "asin") return asin(x);
  if (name == "acos") return acos(x);
  if (name == "atan") return atan(x);
  if (name == "ln" || name == "log") return log(x);
  if (name == "log10") return log10(x);
  if (name == "sqrt") return sqrt(x);
  if (name == "exp") return sqrt(x);
  return 0;
}

char* ::utils::mergeSigns(std::string name1, std::string name2) {
	std::string str = name1 + name2;
	if (str == "++" || str == "--") return "+";
	if (str == "+-" || str == "-+") return "-";
	throw ::utils::BaseException("Cannot parse equation due to wrong signs sequence");
}