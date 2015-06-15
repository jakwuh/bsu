#ifndef __UI_BUTTON_H_INCLUDED__
#define __UI_BUTTON_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Button : public UI
{
public:
	Button(HINSTANCE hI, UI* ui);
protected:
	void registerWindow();
};

#endif