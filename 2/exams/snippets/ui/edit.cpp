#include "edit.h"

Edit::Edit(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("EDIT", "Default text", 
        WS_CHILD | WS_VISIBLE, 
        0, 0, 0, 0, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void Edit::registerWindow()
{
	windows[handler] = (UI*)this;
}
