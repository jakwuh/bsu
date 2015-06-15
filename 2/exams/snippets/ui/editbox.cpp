#include "editbox.h"

EditBox::EditBox(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("EDIT", "Default text", 
        ES_MULTILINE | ES_WANTRETURN | WS_CHILD | WS_BORDER, 
        0, 0, 0, 0, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void EditBox::registerWindow()
{
	windows[handler] = (UI*)this;
}
