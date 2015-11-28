/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __BOT_H_INCLUDED__
#define __BOT_H_INCLUDED__

#include <cmath>

#include "..\graphics\circle.h"
#include "..\utils\math.h"
#include "..\config\config.h"

class Player;

class Bot : public ::graphics::Circle
{
    friend class Town;
private:
    const int speed;
    Player *hoster;
    Town *aim, *home;
    int aim_x, aim_y;
public:
    Bot(Town*, Town*, Player*);
    void move();
    ~Bot();
};

#endif