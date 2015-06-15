#include "textbox.h"

TextBox::TextBox(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("STATIC", "Default text", 
        WS_CHILD | WS_VISIBLE | SS_LEFT | SS_SUNKEN, 
        0, 0, 1, 1, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void TextBox::registerWindow()
{
	windows[handler] = (UI*)this;
}
