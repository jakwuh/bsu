#ifndef __EXCEPTION_H_INCLUDED__
#define __EXCEPTION_H_INCLUDED__

class Exception
{
public:
	virtual char* what() = 0;
};

#endif

#ifndef __COLLECTION_ERROR_H_INCLUDED__
#define __COLLECTION_ERROR_H_INCLUDED__

class BadAccessException : public Exception
{
public:
	char* what() { return "Bad access"; };
};

#endif