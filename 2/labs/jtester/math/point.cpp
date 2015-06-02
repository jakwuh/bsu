#include "point.h"

using namespace Math;

Point::Point(double _x, double _y) : x(_x), y(_y) {};

Point::Point(Point const& p) : x(p.x), y(p.y) {};

bool ::Math::operator == (Point const& p1, Point const& p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}

bool ::Math::operator != (Point const& p1, Point const& p2)
{
//	return !(p1 == p2);
	return false;
}