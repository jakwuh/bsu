#ifndef __UI_GRID_H_INCLUDED__
#define __UI_GRID_H_INCLUDED__

#include <string>
#include <vector>
#include <Windows.h>
#include <CommCtrl.h>
#include "../ui/ui.h"
#include "../ui/window.h"
#include "../ui/exception.h"

class Grid : public UI
{
public:
	Grid(HINSTANCE hI, UI* ui);
	void addColumn(std::string const&, unsigned, unsigned);
	void addRow(std::vector<std::string> const&);
	std::vector<std::string> getRow();
	void deleteRow(unsigned);
	void clear();
	unsigned count();
protected:
	void registerWindow();
};

#endif