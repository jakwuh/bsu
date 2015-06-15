#include "town.h"
#include "..\controllers\bot.h"
#include "..\controllers\player.h"
#undef max

Town::Town(int _px_x, int _px_y, int _capacity, double _bps, double _cooldown)
	: capacity(_capacity), bps(_bps), cooldown(_cooldown), 
    Circle(_px_x, _px_y, std::max(::config::min_town_radius, (int) (_capacity * ::config::pixels_per_capacity)))
{
	hoster = 0;
    count = 0;
}

Town::~Town()
{
    for (Bots::iterator it = bots.begin(); it != bots.end(); ++it)
        delete (it->second);
    bots.clear();
}

void Town::init(Player* _hoster, double _count)
{
    hoster = _hoster;
    count = _count;
}

void Town::triggerAim(Player* player, Town* _aim)
{
    if (hoster != player) return;
    if (_aim == this) {
        aims.clear();
    } else {
        if (aims[(int)_aim])
            aims.erase((int)_aim);
        else aims[(int)_aim] = _aim;        
    }
}

void Town::draw(HDC& hdc, int xd, int yd)
{
    ::graphics::Circle::draw(hdc, xd, yd);
    RECT rect;
    rect.left = xd + px_x - r;
    rect.right = xd + px_x + r;
    rect.top = yd + px_y - r;
    rect.bottom = yd + px_y + r;
    char* tmp = new char[25]{0};
    _itoa_s((int)count, tmp, 25, 10);
    DrawText(hdc, tmp, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    delete tmp;

	std::vector<Bot*> tmp_bots;
	for (Bots::iterator it = bots.begin(); it != bots.end(); ++it)
		tmp_bots.push_back(it->second);
	for (unsigned i = 0; i < tmp_bots.size(); ++i) {
        SelectObject(hdc, ::brushes::map[tmp_bots[i]->hoster->getColor()]);
		tmp_bots[i]->draw(hdc, xd, yd);
    }
}

void Town::grow()
{
    count = count < capacity - bps ? count + bps : capacity;
}

void Town::remove(Bot* bot)
{
	int k = (int)bot;
    bots.erase((int)bot);
}

void Town::comeOut()
{
    std::vector<Bot*> tmp_bots;
    for (Bots::iterator it = bots.begin(); it != bots.end(); ++it)
        tmp_bots.push_back(it->second);
    for (unsigned i = 0; i < tmp_bots.size(); ++i)
        tmp_bots[i]->move();

    _cool -= ::config::milliseconds_per_tact;
    if (_cool > 0 || !aims.size() || count < 1) return;
    _cool = cooldown;
    Aims::iterator it = aims.begin();
    while(count > 0 && it != aims.end()) {
        --count;
        Bot* bot_ptr = new Bot(this, it->second, hoster);
        bots[(int)bot_ptr] = bot_ptr;
        ++it; 
    }
}

void Town::comeIn(Bot* bot)
{
    if (bot->hoster == hoster) {
        if (count + 1 <= capacity) {
            ++count;
        }
    }
    else {
        --count;
        if (count < 0) {
            count *= -1;
            hoster = bot->hoster;
        }
    }
    bot->home->remove(bot);
}

Player* Town::getHoster()
{
    return hoster;
}