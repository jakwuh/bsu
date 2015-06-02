#ifndef __BINARY_FILES_H_INCLUDED__
#define __BINARY_FILES_H_INCLUDED__

#include <fstream>

class BinaryTemplate
{
public:
	template <typename K>
	friend std::ofstream& operator << (std::ofstream& out, K const& c)
	{
		out.write(reinterpret_cast<const char*>(&c), sizeof(K));
		out.flush();
		return out;
	}
	template <typename K>
	friend std::ifstream& operator >> (std::ifstream& in, K& c)
	{
		in.read(reinterpret_cast<char*>(&c), sizeof(K));
		return in;
	}
	
};

#endif