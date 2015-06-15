#include "label.h"

Label::Label(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("STATIC", "Default text", 
        WS_CHILD | WS_VISIBLE | SS_LEFT, 
        0, 0, 1, 1, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void Label::registerWindow()
{
	windows[handler] = (UI*)this;
}
