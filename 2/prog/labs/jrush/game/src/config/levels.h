/**
* @author James
* @version 0.0.1
* @date 24.03.2015
*/

#ifndef __LEVELS_H_INCLUDED__
#define __LEVELS_H_INCLUDED__

#include "../config/config.h"
#include "../controllers/player.h"
#include "../core/town.h"
#include "../core/interfaces.h"
#include <vector>
#include <fstream>
#include <cstring>
#include <Windows.h>

using namespace types;

void count_levels();
LPTSTR level(int, Towns&, TownMap&, Players);

#endif