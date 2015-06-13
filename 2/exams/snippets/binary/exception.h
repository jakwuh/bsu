#ifndef __EXCEPTION_H_INCLUDED__
#define __EXCEPTION_H_INCLUDED__

class Exception
{
public:
	virtual char* what() = 0;
};

#endif