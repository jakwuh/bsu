#ifndef __UI_WINDOW_H_INCLUDED__
#define __UI_WINDOW_H_INCLUDED__

#include <string>
#include <map>
#include <Windows.h>
#include "../ui/interfaces.h"
#include "../utils/format.h"
#include "../ui/exception.h"

class Window;
typedef std::map<HWND, Window*> WindowMap;

class Window
{
public:
	Window(HINSTANCE);
	~Window();
	void show();
	void hide();
	void close();
	void resize(unsigned, unsigned);
	void add(IDrawable const&);
	void remove(IDrawable const&);
	void trigger(Action){MessageBox(NULL, "Unknown error", "ERROR", MB_OK);};
	void setCaption(std::string const&);
	std::string getCaption();
	static LRESULT WINAPI wndProc(HWND, UINT, WPARAM, LPARAM);
	static void initializeThread();
private:
	HINSTANCE hI;
	std::string name;
	HWND handler;
	static WindowMap windows;
	void initialize();
	void create();
};

#endif