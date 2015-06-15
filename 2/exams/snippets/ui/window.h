#ifndef __UI_WINDOW_H_INCLUDED__
#define __UI_WINDOW_H_INCLUDED__

#include <string>
#include <map>
#include <Windows.h>
#include "../ui/ui.h"

class Window : public UI
{
public:
	Window(HINSTANCE hI);
	void setText(std::string const&);
	std::string getText();

	static LRESULT WINAPI wndProc(HWND, UINT, WPARAM, LPARAM);
	static void initialize();
protected:
	void registerWindow();
};

#endif