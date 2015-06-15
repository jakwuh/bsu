#ifndef __IDRAWABLE_H_INCLUDED__
#define __IDRAWABLE_H_INCLUDED__

#include <Windows.h>
#include <map>
#include <string>
#include <vector>

class IDrawable
{
public:
    virtual void draw(){};
    virtual void draw(HDC&, int, int){};
    virtual void resize(){};
    virtual ~IDrawable(){};
};

class IMovable
{
public:
    virtual void move(int, int) = 0;
    virtual void move(){};
    virtual ~IMovable(){};
};



class Town;
class Player;
class Bot;

namespace types
{
    typedef std::vector< ::Town* > Towns;
    typedef std::vector< Towns > TownMap;
    typedef std::map< int, Town* > Aims;
    typedef std::vector<::IDrawable*> Views;
    typedef std::vector<::Player*> Players;
    typedef std::map<int, ::Bot*> Bots;

    enum class Action{ default = 0, up, right, down, left, enter };
    typedef std::map<UINT, Action> KeySet;

    enum class Position{ left, right };

    typedef std::map<std::string, HWND> UI;

    typedef std::map<COLORREF, HBRUSH> BrushMap;  
    
    typedef std::map<std::string, HPEN> PenMap;  
}


#endif