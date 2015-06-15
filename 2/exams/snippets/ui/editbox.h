#ifndef __UI_EDITBOX_H_INCLUDED__
#define __UI_EDITBOX_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class EditBox : public UI
{
public:
	EditBox(HINSTANCE hI, UI* ui);
protected:
	void registerWindow();
};

#endif