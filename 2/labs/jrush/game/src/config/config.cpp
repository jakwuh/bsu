#include "config.h"

namespace config
{

extern int milliseconds_per_tact = 40;
extern int level = 0;
extern int levels_count = 0;

extern const int pixels_per_cell = 1;
extern const int window_width = 800;
extern const int window_height = 600;

extern const double pixels_per_capacity = 0.4;

extern const int cursor_speed = 100; //  pixels
extern const int bot_speed = 30; //  pixels
extern const int view_speed = 90; // pixels
extern const int bar_height = 20;
extern const int bot_radius = 6;
extern const int min_town_radius = 20;


extern const KeySet keyset1 = ::generateKeySet(1);
extern const KeySet keyset2 = ::generateKeySet(2);
    
}
