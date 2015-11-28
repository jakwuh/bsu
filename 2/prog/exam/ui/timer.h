#ifndef __UI_TIMER_H_INCLUDED__
#define __UI_TIMER_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Timer : public UI
{
public:
	Timer(HINSTANCE hI, UI* ui);
	~Timer();
	void begin(int);
protected:
	void registerWindow();
};

#endif