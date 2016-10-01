/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include <Windows.h>
#include <string>
#include "../graphics/cursor.h"
#include "../core/interfaces.h"
#include "../core/town.h"
#include "../config/config.h"
#include "../core/interfaces.h"

using namespace types;

class Player
{
    friend class Town;
private:
    TownMap map;
    KeySet keyset;
    COLORREF color;
    Town *aim, *selected;
    ::graphics::Cursor *active, *passive;
public:
    Player(KeySet const&, COLORREF);
    ~Player();
    void keyPress(UINT);
    void setMap(TownMap);
    void draw(HDC&, int, int);
    int getX();
    int getY();
    std::string getDescription();
    COLORREF getColor();
};


#endif