#include "checkbox.h"

CheckBox::CheckBox(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("BUTTON", "Default text", 
        WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,
        0, 0, 0, 0, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void CheckBox::registerWindow()
{
	windows[handler] = (UI*)this;
}

bool CheckBox::getState()
{
	return SendMessage(handler, BM_GETCHECK, 0, 0L);
}

void CheckBox::setState(bool state)
{
	SendMessage(handler, BM_SETCHECK, state ? BST_CHECKED : BST_UNCHECKED, 0L);
}