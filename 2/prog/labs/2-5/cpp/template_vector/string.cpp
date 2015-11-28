#include"string.h"

int countDigits(int i)
{
	int c = 0;
	while (i > 9) {
		i /= 10;
		c++;
	}
	return ++c;
}

int nextDigit(int &i)
{
	int k = i % 10;
	i /= 10;
	return k;
}

String::String() : ptr((char*) calloc(1, sizeof(char))){};

String::String(const char* s)
{
	ptr = (char*) std::memcpy(calloc(strlen(s) + 1, sizeof(char)), s, sizeof(char) * strlen(s));
}

String::String(int i)
{
	ptr = (char*) calloc(countDigits(i) + 1, sizeof(char));
	for (int j = countDigits(i) - 1; j >= 0; j--)
		ptr[j] = nextDigit(i) + '0';
}

String::String(const String &s)
{
	ptr = (char*) std::memcpy(calloc(strlen(s) + 1, sizeof(char)), s.ptr, sizeof(char) * strlen(s));
}

int String::stoi(const String &s)
{
	bool sign = true;
	int i = 0, digit, q = 1;
	bool trigger = false;
	for (int j = 0; j < strlen(s); j++)
	{
		if (s.ptr[i] == ' ') continue;
		if (!trigger) {
			trigger = true;
			if (s.ptr[i] == '-') {
				sign = false;
				continue;
			}
		}
		digit = s.ptr[j] - '0';
		if (digit >= 0 && digit < 10)
			i = i * 10 + digit;
		else break;
	}
	return (sign * 2 - 1) * i;
}

int String::substr(const String &s, int i)
{
	if (strlen(s) > strlen(*this)) return -1;
	for (int i = 0; i < strlen(*this); ++i)
	if (memcmp(ptr + i, s.ptr, sizeof(char) * strlen(s)) == 0)
			return i;
	return -1;
}

String& String::strpst(const String &s, int i)
{
	if (i < 0 || i > strlen(*this)) throw BadIndex();
	if (strlen(s) == 0) return *this;
	int n = strlen(ptr) + strlen(s);
	ptr = (char*) realloc(ptr, sizeof(char) * (strlen(*this) + strlen(s) + 1));
	std::memcpy(ptr + i + strlen(s), ptr + i, sizeof(char) * strlen(s));
	std::memcpy(ptr + i, s.ptr, sizeof(char) * strlen(s));
	ptr[n] = '\0';
	return *this;
}

String& String::strrlc(const String &s, int i)
{
	if (i < 0 || i >= strlen(s)) throw BadIndex();
	if (i + strlen(s) > strlen(*this))
		ptr = (char*) realloc(ptr, i + strlen(s) + 1);
	std::memcpy(ptr + i, s.ptr, sizeof(char) * (strlen(s) + 1));
	return *this;
}

String& String::operator = (const String &s)
{
	ptr = (char*) std::memcpy(calloc(strlen(s) + 1, sizeof(char)), s.ptr, strlen(s) * sizeof(char));
	return *this;
}

String& String::operator += (const String &s)
{
	int n = strlen(*this);
	ptr = (char*) realloc(ptr, strlen(*this) + strlen(s) + 1);
	std::memcpy(ptr + n, s.ptr, strlen(s) * sizeof(char));
	ptr[n + strlen(s)] = '\0';
	return *this;
}

char& String::operator [] (int i)
{
	if (i >= strlen(*this)) throw BadIndex();
	return (*this).ptr[i];
}

String String::operator()(int i, int count)
{
	if (i < 0 || count <= 0 || i >= strlen(*this) || i + count > strlen(*this))
		throw BadIndex();
	String tmp;
	tmp.ptr = (char*) std::memcpy(calloc(count + 1, sizeof(char)), this->ptr + i, count * sizeof(char));
	return tmp;
}

bool String::operator !()
{
	return !strlen(*this);
}

String operator + (const String &s1, const String &s2)
{
	String tmp(s1);
	tmp += s2;
	return tmp;
}

bool operator == (const String &s1, const String &s2)
{
	if (strlen(s1) != strlen(s2)) return false;
	return !memcmp(s1.ptr, s2.ptr, (strlen(s1) + 1) * sizeof(char));
}

bool operator != (const String &s1, const String &s2)
{
	if (strlen(s1) != strlen(s2)) return true;
	return memcmp(s1.ptr, s2.ptr, (strlen(s1) + 1) * sizeof(char)) != 0;
}

bool operator < (const String &s1, const String &s2)
{
	return memcmp(s1.ptr, s2.ptr, sizeof(char) * (std::min(strlen(s1), strlen(s2)) + 1)) < 0;
}

bool operator > (const String &s1, const String &s2)
{
	return memcmp(s1.ptr, s2.ptr, sizeof(char) * (std::min(strlen(s1), strlen(s2)) + 1)) > 0;
}

bool operator <= (const String &s1, const String &s2)
{
	return !(s1 > s2);
}

bool operator >= (const String &s1, const String &s2)
{
	return !(s1 < s2);
}

int strlen(const String& s)
{
	int i = 0;
	while (s.ptr[i]) i++;
	return i;
}

std::istream& operator >> (std::istream& in, String &s)
{
	in >> s.ptr;
	return in;
}

std::ostream& operator << (std::ostream& out, String &s)
{
	out << s.ptr;
	return out;
}