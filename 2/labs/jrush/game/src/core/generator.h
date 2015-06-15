/**
 * @author RJ TM
 * @version 0.0.2
 * @date 13.03.2015
 */

#ifndef __GENERATOR_H_INCLUDED__
#define __GENERATOR_H_INCLUDED__

#include <stdexcept>
#include <ctime>
#include <cstdlib>
#include <assert.h>
#include "../config/config.h"
#include "../config/debug.h"
#include "../config/surface.h"
#include "../includes/list_dynamic.h"
#include "../includes/map.h"

#define List ListDynamic

/**
 * @brief generate all stuff for the level
 */
class Generator
{
private:
	int randomFill(int**, Cell&, int, int, int);
	int n, m;
public:
	Generator(){};
	Generator(int, int = 0);
	inline void setParameters(int, int = 0);
	int** generateMap(int, int, double);
	Map<Surface> generateSurface(int, int, double);
};


#endif