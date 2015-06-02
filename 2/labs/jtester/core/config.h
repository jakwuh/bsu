#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

namespace Exception
{

	using namespace System;

	ref class Exception : public System::Exception
	{
	public:
		Exception() : System::Exception("Base exception") {};
		Exception(String^ _message) : System::Exception(_message) {};
	};
	
	ref class ExecutionException : public Exception
	{
	public:
		ExecutionException() : Exception("Cannot execute provided file") {};
		ExecutionException(String^ _message) : Exception(_message) {};
	};

	ref class InputException : public Exception
	{
	public:
		InputException() : Exception("Can't parse input data. Please, check the data you have entered") {};
		InputException(String^ _message) : Exception(_message) {};
	};
}

#endif

