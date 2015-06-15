#include "ui.h"

WindowMap UI::windows = WindowMap();

UI::UI(HINSTANCE hI_, UI* ui)
{
	parent = ui;
	if (parent) {
		id = parent->getUniqueId();
		parent->addChild(this);
	}
	hI = hI_;
	left = 0;
	top = 0;
	leftStrategy = new DefaultDrawableStrategy();
	topStrategy = new DefaultDrawableStrategy();
};

UI::~UI()
{
	if (parent) parent->removeChild(this);
	windows.erase(handler);
	DestroyWindow(handler);
}

void UI::show()
{
	ShowWindow(handler, SW_SHOW);
}

void UI::hide()
{
	ShowWindow(handler, SW_HIDE);
}

void UI::close()
{
	delete this;
}

void UI::enable()
{
	EnableWindow(handler, true);
}

void UI::disable()
{
	EnableWindow(handler, false);
}

void UI::resize(unsigned width, unsigned height)
{
	RECT rp = getRect();
	int pleft = rp.left + (*leftStrategy)(rp.right - rp.left, width, left);
	int ptop = rp.top + (*topStrategy)(rp.bottom - rp.top, height, top);

	SetWindowPos(handler, HWND_TOP, pleft, ptop, width, height, 
		SWP_NOZORDER | SWP_NOACTIVATE);
	draw();
}

RECT UI::getRect()
{
	if (parent) {
		RECT rp;
		GetClientRect(*parent, &rp);
		return rp;
	} else {
		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = GetSystemMetrics(SM_CXSCREEN);
		r.bottom = GetSystemMetrics(SM_CYSCREEN);
		return r;
	}
}

HWND UI::getHandler()
{
	return handler;
}

void UI::draw()
{
	RECT rp = getRect();
	RECT r;
	GetWindowRect(handler, &r);
	int pleft = rp.left + (*leftStrategy)(rp.right - rp.left, r.right - r.left, left);
	int ptop = rp.top + (*topStrategy)(rp.bottom - rp.top, r.bottom - r.top, top);
	
	SetWindowPos(handler, HWND_TOP, pleft, ptop, r.right - r.left, 
		r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);

	for (auto it : kids) it->draw();
};

void UI::setText(std::string const& text)
{
	SendMessage(handler, WM_SETTEXT, NULL, (LPARAM)text.c_str());
}

std::string UI::getText()
{
	LPSTR tmp = new CHAR[1000];
	SendMessage(handler, WM_GETTEXT, 1000, (LPARAM)tmp);
	return tmp;
}

void UI::setFont(HFONT hfont)
{
	SendMessage(handler, WM_SETFONT, (WPARAM)hfont, MAKELPARAM(TRUE, 0));
}

void UI::addChild(UI* child)
{
	kids.push_back(child);
}

void UI::removeChild(UI* child)
{
	kids.erase(std::remove(kids.begin(), kids.end(), child), kids.end());
}

unsigned UI::getUniqueId()
{
	std::vector<unsigned> ids;
	unsigned uid;
	for (auto it : kids) ids.push_back(it->id);
	do {
		uid = rand() + 1;
	} while (uid == id || std::find(ids.begin(), ids.end(), uid) != ids.end());
	return uid;
}

void UI::setPosition(unsigned left_, unsigned top_)
{
	leftStrategy = new DefaultDrawableStrategy();
	left = left_;
	topStrategy = new DefaultDrawableStrategy();
	top = top_;
	draw();
}

void UI::setPosition(unsigned left_, Position p_top)
{
	leftStrategy = new DefaultDrawableStrategy();
	left = left_;
	if (p_top == Position::top) topStrategy = new LeftDrawableStrategy();
	if (p_top == Position::vcenter) topStrategy = new CenterDrawableStrategy();
	if (p_top == Position::bottom) topStrategy = new RightDrawableStrategy();
	draw();
}

void UI::setPosition(Position p_left, unsigned top_)
{
	topStrategy = new DefaultDrawableStrategy();
	top = top_;
	if (p_left == Position::left) leftStrategy = new LeftDrawableStrategy();
	if (p_left == Position::hcenter) leftStrategy = new CenterDrawableStrategy();
	if (p_left == Position::right) leftStrategy = new RightDrawableStrategy();
	draw();
}

void UI::setPosition(Position p_left, Position p_top)
{
	if (p_left == Position::left) leftStrategy = new LeftDrawableStrategy();
	if (p_left == Position::hcenter) leftStrategy = new CenterDrawableStrategy();
	if (p_left == Position::right) leftStrategy = new RightDrawableStrategy();
	if (p_top == Position::top) topStrategy = new LeftDrawableStrategy();
	if (p_top == Position::vcenter) topStrategy = new CenterDrawableStrategy();
	if (p_top == Position::bottom) topStrategy = new RightDrawableStrategy();
	draw();
}

void UI::on(Action action, void(*fn)())
{
	callbacks.insert(std::pair<Action, void (*)()>(action, fn));
}

void UI::trigger(Action action)
{
	for (auto pair : callbacks) {
		if (pair.first == action) pair.second();
	}
	switch (action)
	{
	case Action::redraw:
		draw();
		break;
	case Action::change:
		break;
	case Action::select:
		break;
	}
}