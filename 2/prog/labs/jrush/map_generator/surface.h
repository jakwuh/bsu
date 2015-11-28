/**
* @author RJ TM
* @version 0.0.1
* @date 13.03.2015
*/

#ifndef __SURFACE_H_INCLUDED__
#define __SURFACE_H_INCLUDED__

#include <Windows.h>

class Surface
{
public:
	Surface(COLORREF _color = 0) : color(_color)
	{
	};
	COLORREF color;
};

#endif