#ifndef UI_CHECKBOX_H_INCLUDED__
#define UI_CHECKBOX_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class CheckBox : public UI
{
public:
	CheckBox(HINSTANCE hI, UI* ui);
	bool getState();
	void setState(bool);
protected:
	void registerWindow();
};

#endif