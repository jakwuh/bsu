#include "item.h"

std::string Item::to_string() {
	switch (type) {
		case number_t: {
		std::string out = std::to_string(value);
		while (out.size() > 1 && out.find_last_of(".") != std::string::npos &&
				out.find_last_of("0.") == out.size() - 1)
			out = out.substr(0, out.size() - 1);
		return out;
		break;
		}
		case sign_t:
		case variable_t:
		return name;
		break;
		case left_bracket_t:
		return "(";
		break;
		case right_bracket_t:
		return ")";
		break;
	}
	return "";
}
short Item::getPriority() {
	return name == "(" ? 0 : name == "-" || name == "+" ? 1 : 2;
}