#include "button.h"

Button::Button(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("BUTTON", "Default text", 
        WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 
        0, 0, 0, 0, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void Button::registerWindow()
{
	windows[handler] = (UI*)this;
}
