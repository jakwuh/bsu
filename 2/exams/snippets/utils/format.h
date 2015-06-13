#ifndef __UTILS_FORMAT_H_INCLUDED__
#define __UTILS_FORMAT_H_INCLUDED__

#include <Windows.h>
#include <string>
#include <cstring>
#include <tchar.h>

class Format
{
public:
	static std::wstring s2ws(std::string const&);
};

#endif