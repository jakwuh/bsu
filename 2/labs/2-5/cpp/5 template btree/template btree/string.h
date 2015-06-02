#ifndef __STRING_H_INCLUDED__
#define __STRING_H_INCLUDED__

#include <cstring>
#include <malloc.h>
#include <algorithm>
#include <iostream>
#include "error.h"

class String
{
private:
	char* ptr;
public:
	String();
	String(const char*);
	String(int);
	String(const String&);
	static int stoi(const String&);
	int substr(const String&, int  = 0); // str find
	String& strpst(const String&, int = 0);	// str paste
	String& strrlc(const String&, int = 0); // str replace
	String& operator = (const String&);
	String& operator += (const String&);
	char& operator [] (int);
	String operator()(int = 0, int = 0);
	bool operator !();
	friend String operator + (const String&, const String&);
	friend bool operator == (const String&, const String&);
	friend bool operator != (const String&, const String&);
	friend bool operator < (const String&, const String&);
	friend bool operator > (const String&, const String&);
	friend bool operator <= (const String&, const String&);
	friend bool operator >= (const String&, const String&);
	friend int strlen(const String&);
	friend std::istream& operator >> (std::istream&, String&);
	friend std::ostream& operator << (std::ostream&, String&);
};

#endif