#ifndef __BINARY_TEMPLATE_H_INCLUDED__
#define __BINARY_TEMPLATE_H_INCLUDED__

#include <iostream>
#include <fstream>
#include <sstream>
#include <type_traits>

class BinaryTemplate
{
public:

	template <typename K>
	friend std::ios& operator << (std::ios&, K const&);

	template <typename K>
	friend std::ios& operator >> (std::ios&, K&);

};

template <typename Stream, typename K>
Stream& operator << (Stream& out, K const& c)
{
	static_assert(
		std::is_same<Stream, std::ofstream>::value 
		|| std::is_same<Stream, std::fstream>::value
		|| std::is_same<Stream, std::stringstream>::value
		|| std::is_same<Stream, std::ostringstream>::value,
		"BinaryTemplate::operator <<: Only fstream & sstream are allowed");
	out.write(reinterpret_cast<const char*>(&c), sizeof(K));
	out.flush();
	return out;
}

template <typename Stream, typename K>
Stream& operator >> (Stream& in, K& c)
{
	static_assert(
		std::is_same<Stream, std::ifstream>::value
		|| std::is_same<Stream, std::fstream>::value
		|| std::is_same<Stream, std::stringstream>::value
		|| std::is_same<Stream, std::istringstream>::value,
		"BinaryTemplate::operator <<: Only fstream & sstream are allowed");
	in.read(reinterpret_cast<char*>(&c), sizeof(K));
	return in;
}

#endif