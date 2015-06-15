/**
* @author James
* @version 0.0.1
* @date 13.03.2015
*/

#ifndef __ERRORS_H_INCLUDED__
#define __ERRORS_H_INCLUDED__

#include <Windows.h>

namespace errors {
	
	class Error
	{
	public:
		virtual char* what() = 0;
	};

	class WindowCreateFail : public Error
	{
	public:
		char* what(){ return "Cannot create window"; }
	};

}


#endif