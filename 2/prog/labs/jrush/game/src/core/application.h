/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __APPLICATION_H_INCLUDED__
#define __APPLICATION_H_INCLUDED__

#include <Windows.h>
#include <string>
#include <cstring>

#include "..\config\errors.h"
#include "..\config\levels.h"
#include "..\config\config.h"
#include "..\core\interfaces.h"
#include "..\core\town.h"
#include "..\controllers\player.h"
#include "..\graphics\view.h"
#include "..\graphics\menu.h"
#include "..\graphics\settings.h"
#include "..\utils\styles.h"

class Application
{
	friend class View;
private:
	LPTSTR map_path;
	HWND main_window;
	WNDPROC window_proc;
	HINSTANCE h_instance;
	LPCSTR window_classname;

	Towns towns;
	Views views;
	Players players;

	void reset();
	void registerWindows();
	
public:
	Application(HINSTANCE, WNDPROC);
	~Application();
	void play();
	void menu();
	void settings();
	void setSettings(int, int);
	void go(int);
	void resize();
	void keyPress(UINT);
};

#endif