#ifndef __EXCEPTION_H_INCLUDED__
#define __EXCEPTION_H_INCLUDED__

class Exception {
	public: virtual char* what() = 0;
};

#endif

#ifndef __UI_EXCEPTION_H_INCLUDED__
#define __UI_EXCEPTION_H_INCLUDED__

class WindowCreateException : public Exception {
	public: char* what() { return "Error occured while creating the window"; }
};

#endif