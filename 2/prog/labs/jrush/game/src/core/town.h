/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __TOWN_H_INCLUDED__
#define __TOWN_H_INCLUDED__

#include <Windows.h>
#include <algorithm>

#include "..\core\interfaces.h"
#include "..\config\config.h"
#include "..\graphics\circle.h"
#include "..\utils\styles.h"

class Bot;

class Town : public ::graphics::Circle
{
    friend class Bot;
    friend class Player;
private:
    int capacity;
    double count, bps, cooldown, _cool;

    Aims aims;
    Player* hoster;
    Bots bots;

public:
    Town(int, int, int, double, double);
    ~Town();
    void init(Player*, double);
    void triggerAim(Player*, Town*);
    void comeIn(Bot*);
    void remove(Bot*);
    Player* getHoster();
    void grow();
    void draw(HDC&, int, int);
    void comeOut();
};

#endif