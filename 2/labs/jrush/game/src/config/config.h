/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __CONFIG_H_INCLUDED__
#define __CONFIG_H_INCLUDED__

#include <Windows.h>
#include "..\core\interfaces.h"
#include <map>

using namespace types;

static KeySet generateKeySet(int number)
{
	KeySet keyset;
	if (2 == number)
	{
		keyset[37] = ::Action::left;
		keyset[38] = ::Action::up;
		keyset[39] = ::Action::right;
		keyset[40] = ::Action::down;
		keyset[13] = ::Action::enter;
	}
    else if (1 == number)
    {
        keyset[65] = ::Action::left;
        keyset[87] = ::Action::up;
        keyset[68] = ::Action::right;
        keyset[83] = ::Action::down;
        keyset[32] = ::Action::enter;   
    }
	return keyset;
}

namespace config {

    extern int milliseconds_per_tact;
    extern int level;
    extern int levels_count;

    extern const int pixels_per_cell;
    extern const int window_width;
    extern const int window_height;

    extern const double pixels_per_capacity;

    extern const int cursor_speed;
    extern const int bot_speed;
    extern const int view_speed;
    extern const int bar_height;
    extern const int bot_radius;
    extern const int min_town_radius;

    extern const KeySet keyset1;
    extern const KeySet keyset2 ;

}

#endif