#ifndef __UI_EDIT_H_INCLUDED__
#define __UI_EDIT_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Edit : public UI
{
public:
	Edit(HINSTANCE hI, UI* ui);
protected:
	void registerWindow();
};

#endif