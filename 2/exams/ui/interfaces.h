#ifndef __UI_INTERFACES_H_INCLUDED__
#define __UI_INTERFACES_H_INCLUDED__

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <Windows.h>


// Choices
enum class Action {resize, redraw, change, click, select, timer, focus};
enum class Position {left, hcenter, right, top, vcenter, bottom};


// Drawable strategies
class DrawableStrategy {
public: virtual int operator () (
	unsigned /*parent height or width*/,
	unsigned /*client height or width*/,
	int /*margin*/ = 0) {
		return 0;
	};
};
class DefaultDrawableStrategy : public DrawableStrategy{
public: int operator () (unsigned, unsigned, int = 0);
};
class CenterDrawableStrategy : public DrawableStrategy {
public: int operator () (unsigned, unsigned, int = 0);
};
class LeftDrawableStrategy : public DrawableStrategy {
public: int operator () (unsigned, unsigned, int = 0);
};
class RightDrawableStrategy : public DrawableStrategy {
public: int operator () (unsigned, unsigned, int = 0);
};

// Interfaces
class IDrawable
{
public:
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void draw() = 0;
	virtual void close() = 0;
	virtual void resize(unsigned, unsigned) = 0;
	virtual void setPosition(unsigned, unsigned) = 0;
	virtual void setPosition(unsigned, Position) = 0;
	virtual void setPosition(Position, unsigned) = 0;
	virtual void setPosition(Position, Position) = 0;
	virtual RECT getRect() = 0;
	virtual HWND getHandler() = 0;
	operator HWND() { return getHandler(); };
protected:
	unsigned left, top;
	DrawableStrategy *leftStrategy, *topStrategy;
	HINSTANCE hI;
	HWND handler;
};

class ITextable
{
public:
	virtual void setText(std::string const&) = 0;
	virtual std::string getText() = 0;
	virtual void setFont(HFONT) = 0;
};

class IEventable
{
public:
	virtual void trigger(Action) = 0;
	virtual void on(Action, void (*)()) = 0;
protected:
	std::multimap<Action, void (*)()> callbacks;
};

#endif