#ifndef __ERROR_H_INCLUDED__
#define __ERROR_H_INCLUDED__

class Error
{
public:
	virtual char* what() = 0;
};
class BadDimension : public Error
{
	char* what(){ return "Bad dimension"; }
};
class BadIndex : public Error
{
	char* what(){ return "Bad index"; }
};
class ZeroDivision : public Error {
public:
	char* what()
	{
		return "Division on zero";
	}
};

#endif