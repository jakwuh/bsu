#ifndef __UI_POPUP_H_INCLUDED__
#define __UI_POPUP_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/styles.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Popup
{
public:
	static void show(HINSTANCE, HWND, std::string const&);
	static VOID CALLBACK move();
protected:
	static HWND handler;
	static bool toBottom;
	static int height, top;
	static int wait;
};

#endif