#include "combobox.h"

ComboBox::ComboBox(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow("COMBOBOX", "Default text", 
        CBS_DROPDOWNLIST | WS_VSCROLL | WS_CHILD, 
        0, 0, 0, 0, *parent, (HMENU)id, 
        hI, NULL);
	
	if (!handler) throw WindowCreateException();
	registerWindow();
};

void ComboBox::registerWindow()
{
	windows[handler] = (UI*)this;
}

void ComboBox::addItem(std::string const& text)
{
	SendMessage(handler, CB_ADDSTRING, 0, (LPARAM)text.c_str());
}

void ComboBox::deleteItem(int n)
{
	SendMessage(handler, CB_DELETESTRING, (WPARAM)n, 0);
}

unsigned ComboBox::getCount()
{
	unsigned count = SendMessage(handler, CB_GETCOUNT, 0, 0);
	return count;
}