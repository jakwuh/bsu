#include "bot.h"
#include "../core/town.h"

Bot::Bot(Town *_home, Town *_aim, Player* _hoster) 
	: speed(::config::bot_speed), home(_home), aim(_aim), 
    hoster(_hoster), Circle(_home->px_x, _home->px_y, ::config::bot_radius)
{
    aim_x = aim->px_x;
    aim_y = aim->px_y;
};

Bot::~Bot(){}

void Bot::move()
{
    int rr = std::sqr(px_x - aim_x) + std::sqr(px_y - aim_y);
    if (rr < std::sqr(speed)) {
        aim->comeIn(this);
        delete this;
        return;
    } else {
        px_x += (int) ( (aim_x - px_x) / std::sqrt(rr) * speed );
        px_y += (int) ( (aim_y - px_y) / std::sqrt(rr) * speed );
    }
}