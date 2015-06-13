#ifndef __BINARY_UTILS_H_INCLUDED__
#define __BINARY_UTILS_H_INCLUDED__

#include <iostream>

namespace Binary
{
	template <typename T>
	unsigned count(std::istream& in)
	{
		in.seekg(0, ios::end);
		unsigned length = in.tellg();
		in.seekg(0, ios::beg);
		unsigned count = length / sizeof(T);
		return count;
	}

}


#endif