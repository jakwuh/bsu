#include "grid.h"

Grid::Grid(HINSTANCE hI, UI* ui) : UI(hI, ui) 
{
	handler = CreateWindow(WC_LISTVIEW, "Default text", 
        WS_CHILD | WS_VISIBLE | LVS_REPORT | WS_BORDER, 
        0, 0, 1, 1, *parent, (HMENU)id, 
        hI, NULL);
	
	ListView_SetExtendedListViewStyleEx(handler, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	if (!handler) throw WindowCreateException();
	registerWindow();

};

void Grid::registerWindow()
{
	windows[handler] = (UI*)this;
}

void Grid::addColumn(std::string const& name, unsigned id, unsigned width)
{
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cx = width;
	lvc.cchTextMax = name.length() + 1;
	lvc.pszText = (char*)malloc(name.length() + 1);
	strcpy_s(lvc.pszText, name.length() + 1, name.c_str());
	ListView_InsertColumn(handler, id, &lvc);
	delete lvc.pszText;
}

unsigned Grid::rowCount()
{
	return ListView_GetItemCount(handler);
}

unsigned Grid::columnCount()
{
	LVCOLUMN lvc;
	lvc.mask = LVCF_TEXT | LVCF_WIDTH;
	lvc.cchTextMax = 1000;
	lvc.pszText = (char*)malloc(1000);
	int count = -1;
	while (ListView_GetColumn(handler, ++count, &lvc));
	delete lvc.pszText;
	return count;
}

void Grid::addRow(std::vector<std::string> const& values)
{
    LVITEM lvi;
    lvi.mask = LVIF_TEXT;

    int column = 0, row = rowCount();
    for (auto value : values) {
		if (column == 0) {
			lvi.cchTextMax = value.length() + 1;
			lvi.iItem = row;
			lvi.iSubItem = column;
			lvi.pszText = (char*)malloc(value.length() + 1);
			strcpy_s(lvi.pszText, value.length() + 1, value.c_str());
			ListView_InsertItem(handler, &lvi);
			delete lvi.pszText;
		} else {
			char* text = (char*)malloc(value.length() + 1);
			strcpy_s(text, value.length() + 1, value.c_str());
			ListView_SetItemText(handler, row, column, text);
			delete text;
		}
	    ++column;
    }
}

std::vector<std::string> Grid::getRow(unsigned i)
{
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = i;
	
	lvi.cchTextMax = 1000;
	lvi.pszText = (char*)malloc(1000);
	auto out = std::vector<std::string>();
	for (unsigned i = 0; i < columnCount(); ++i) {
		lvi.iSubItem = i;
		ListView_GetItem(handler, &lvi);
		out.push_back(lvi.pszText);
	}
	return out;
}

void Grid::deleteRow(unsigned i)
{
	ListView_DeleteItem(handler, i);
}

void Grid::clear()
{
	ListView_DeleteAllItems(handler);
}

int Grid::getSelectedId()
{
	int iPos = ListView_GetNextItem(handler, -1, LVNI_SELECTED);
	return iPos;
}