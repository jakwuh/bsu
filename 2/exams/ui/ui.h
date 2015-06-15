#ifndef __UI_H_INCLUDED__
#define __UI_H_INCLUDED__

#include <map>
#include <Windows.h>
#include "interfaces.h"
#include "exception.h"

class UI : public IDrawable, public IEventable, public ITextable
{
public:
	UI(HINSTANCE = NULL, UI* = NULL);
	virtual ~UI();
	virtual void show();
	virtual void hide();
	virtual void draw();
	virtual void close();
	virtual void enable();
	virtual void disable();
	virtual void resize(unsigned, unsigned);
	virtual RECT getRect();
	virtual HWND getHandler();
	virtual void setText(std::string const&);
	virtual std::string getText();
	virtual void setFont(HFONT);
	virtual void trigger(Action);
	virtual void on(Action, void (*)());
	virtual void setPosition(unsigned, unsigned);
	virtual void setPosition(unsigned, Position);
	virtual void setPosition(Position, unsigned);
	virtual void setPosition(Position, Position);
	unsigned getUniqueId();
protected:
	virtual void registerWindow() = 0;
	void addChild(UI*);
	void removeChild(UI*);
	std::vector<UI*> kids;
	unsigned id;
	UI* parent;
	static std::map<HWND, UI*> windows;
};

typedef std::map<HWND, UI*> WindowMap;

#endif