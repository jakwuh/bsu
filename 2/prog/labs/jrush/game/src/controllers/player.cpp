#include "player.h"

Player::Player(KeySet const& _keyset, COLORREF _color) 
    : keyset(_keyset)
{
	passive = 0;
    selected = 0;
    color = _color;
};

COLORREF Player::getColor()
{
    return color;
}

void Player::keyPress(UINT key)
{
    int i = 0, j = 0, _i, _j, k;
    int n = map.size();
    int m = map[0].size();
    while(aim != map[i][j]) {
        ++j;
        if (j == m) {
            j = 0;
            ++i;
        }
        if (i == n) i = 0;
    }

    Action action = keyset[key];
    switch (action) {
    case Action::up:
        _i = (i > 0 ? i - 1 : i);
        _j = j;
        k = 0;
        while(!map[_i][_j] && (_j >= 0 && _j < m))
        {
            --_i;

            if (_i < 0) {
                _i = i - 1;
                
                k *= -1;
                if (k >= 0) ++k;

                _j = j + k;
                if (_j < 0 || _j > m - 1) _j = j - k;
            }

        }
        aim = map[_i][_j];
        break;
	case Action::down:
		_i = (i < n - 1 ? i + 1 : i);
        _j = j;
        k = 0;
        while(!map[_i][_j] && (_j >= 0 && _j < m))
        {
            ++_i;

            if (_i == n) {
                _i = i + 1;
                
                k *= -1;
                if (k >= 0) ++k;

                _j = j + k;
                if (_j < 0 || _j > m - 1) _j = j - k;
            }

        }
        aim = map[_i][_j];
		break;
    case Action::left:
        _i = i;
        _j = (j > 0 ? j - 1 : j);
        k = 0;
        while(!map[_i][_j] && (_i >= 0 && _i < n))
        {
            --_j;

            if (_j < 0) {
                _j = j - 1;
                
                k *= -1;
                if (k >= 0) ++k;

                _i = i + k;
                if (_i < 0 || _i > n - 1) _i = i - k;
            }

        }
        aim = map[_i][_j];
        break;
    case Action::right:
        _i = i;
        _j = (j < m - 1 ? j + 1 : j);
        k = 0;
        while(!map[_i][_j] && (_i >= 0 && _i < n))
        {
            ++_j;

            if (_j == m) {
                _j = j + 1;
                
                k *= -1;
                if (k >= 0) ++k;

                _i = i + k;
                if (_i < 0 || _i > n - 1) _i = i - k;
            }

        }
        aim = map[_i][_j];
        break;
    case Action::enter:
        if (selected) {
            selected->triggerAim(this, aim);
            delete passive;
            passive = 0;
            selected = 0;
        } else {
            selected = aim;	
            passive = new ::graphics::Cursor(aim->px_x, aim->px_y, aim->r);
        }
        break;
    case ::Action::default:
        break;
    }
}

void Player::draw(HDC& hdc, int xd, int yd)
{
    active->move(aim->px_x, aim->px_y);
	SelectObject(hdc, ::pens::map["cursor"]);
    active->draw(hdc, xd, yd, aim->r);
	SelectObject(hdc, ::pens::map["cursor_passive"]);
    if (passive) passive->draw(hdc, xd, yd, selected->r);
}

void Player::setMap(TownMap _map)
{
    map = _map;
	for (TownMap::iterator it = map.begin(); it != map.end(); ++it) {
		for (Towns::iterator jt = it->begin(); jt != it->end(); ++jt) {
			if (*jt && (*jt)->hoster == this) aim = *jt;
		}
	}
	active = new ::graphics::Cursor(aim->px_x, aim->px_y, aim->r);
}

int Player::getX()
{
    return active->getX();
}

int Player::getY()
{
    return active->getY();
}

std::string Player::getDescription()
{
    if (!aim) return "Ничего не выбрано";
    char *buf = new char[500];
    sprintf(buf, "Емкость: %d зарядов | Перезарядка: %.0f мс | Восстановление: %.2f зарядов/с", aim->capacity, aim->cooldown, aim->bps);
    std::string tmp(buf);
    delete buf;
    return tmp;
}