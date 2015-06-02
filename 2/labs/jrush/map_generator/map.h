/**
* @author RJ TM
* @version 0.0.1
* @date 13.03.2015
*/

#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__

class Cell	
{
public:
	Cell(int _i, int _j) : i(_i), j(_j){};
	int i, j;
};

template <typename T>
class Map
{
private:
	T** map;
public:
	Map(int = 0, int = 0, T** = 0);
	T* operator [](int) const;
	inline bool legal(int, int) const;
	int n, m;
};

template <typename T>
Map<T>::Map(int _n, int _m, T** _map) : n(_n), m(_m), map(_map){}

template <typename T>
T* Map<T>::operator [](int i) const
{
	return map[i];
}

template <typename T>
bool Map<T>::legal(int i, int j) const
{
	return !(i < 0 || j < 0 || i >= n || j >= m);
}

#endif