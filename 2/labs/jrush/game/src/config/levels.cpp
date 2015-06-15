#include "levels.h"

void count_levels()
{
	std::ifstream in("levels.ini");
	int size = 300;
	char *buf = new char[size];
	char *command = new char[size];
	while(in) {
		in.getline(buf, size);
		sscanf(buf, "%s", command);
		if (strcmp(buf, "map") == 0)
			++::config::levels_count;
	}
	delete buf, command;
}

LPTSTR level(int _level, ::types::Towns& towns, TownMap& town_map, std::vector<Player*> players)
{
	if (players.size() != 2) throw "Bad bad bad";
	if (_level >= ::config::levels_count) throw "Bad bad bad";

	std::ifstream in("levels.ini");
	int size = 300;
	char *buf = new char[size];
	char *command = new char[size];
	char *path = new char[size];

	int map_num = -1;
	while(in) {
		in.getline(buf, size);
		sscanf(buf, "%s", command);
		if (strcmp(buf, "map") == 0)
			++map_num;
		if (map_num < _level) continue;
		if (map_num > _level) break;

		if (strcmp(command, "size") == 0) {
			int n, m;
			sscanf(buf, "%*s %d %d", &n, &m);
			town_map.assign(n,::types::Towns(m, 0));	
		}

		if (strcmp(command, "file") == 0) {
			int n, m;
			sscanf(buf, "%*s%s", command);
			strcpy(path, command);
		}

		if (strcmp(command, "town") == 0) {
			int n, m, px, py, capacity, size, cooldown, hoster;
			float bps;
			sscanf(buf, "%*s%d%d%d%d%d%d%f%d%d", &n, &m, &px, &py, &capacity, &size, &bps, &cooldown, &hoster);
			town_map[n][m] = new Town(px, py, capacity, bps, cooldown);
			Player* real_hoster = (hoster == 0 ? NULL : players[hoster - 1]);
			town_map[n][m]->init(real_hoster, size);
		} 
	}
	delete buf, command;

	towns.clear();
	for (TownMap::iterator it = town_map.begin(); it != town_map.end(); ++it) {
		for (Towns::iterator jt = it->begin(); jt != it->end(); ++jt) {
			if (*jt)
				towns.push_back(*jt);
		}
	}

	return path;
}