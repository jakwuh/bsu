#ifndef __UI_TEXTBOX_H_INCLUDED__
#define __UI_TEXTBOX_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class TextBox : public UI
{
public:
	TextBox(HINSTANCE hI, UI* ui);
protected:
	void registerWindow();
};

#endif