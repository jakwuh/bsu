#ifndef __UI_INTERFACES_H_INCLUDED__
#define __UI_INTERFACES_H_INCLUDED__

#include <string>
#include <Windows.h>

// Drawable strategies
class DrawableStrategy {
public: virtual unsigned operator () (unsigned /*parent height or width*/, 
	unsigned /*client height or width*/, unsigned /*margin*/ = 0) = 0;
}

class DefaultDrawableStrategy : public DrawableStrategy{}
class CenterDrawableStrategy : public DrawableStrategy {}
class LeftDrawableStrategy : public DrawableStrategy {}
class RightDrawableStrategy : public DrawableStrategy {}

// Interfaces
class IDrawable
{
public:
	virtual void draw() = 0;
	virtual void resize(unsigned, unsigned) = 0;
	virtual RECT getRect() = 0;
protected:
	DrawableStrategy leftStrategy, topStrategy;
};

class ITextable
{
public:
	virtual void setText(std::string const&) = 0;
	virtual void getText(std::string const&) = 0;
	virtual void setFont(HFONT) = 0;
}

// Choices
enum Action {redraw};
enum HPosition {left, center, right};
enum VPosition {top, center, bottom};

#endif