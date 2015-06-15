#ifndef __UI_COMBOBOX_H_INCLUDED__
#define __UI_COMBOBOX_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class ComboBox : public UI
{
public:
	ComboBox(HINSTANCE hI, UI* ui);
	void addItem(std::string const&);
	void deleteItem(int);
	unsigned getCount();
protected:
	void registerWindow();
};

#endif