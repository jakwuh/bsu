#ifndef __UI_LABEL_H_INCLUDED__
#define __UI_LABEL_H_INCLUDED__

#include <string>
#include <Windows.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Label : public UI
{
public:
	Label(HINSTANCE hI, UI* ui);
protected:
	void registerWindow();
};

#endif