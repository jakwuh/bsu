#ifndef __POINT_H_INCLUDED__
#define __POINT_H_INCLUDED__

namespace Math
{

	class Point
	{
	public:
		Point(double = 0, double = 0);
		Point(Point const&);
		double x, y;
		friend bool operator == (Point const &, Point const&);
		friend bool operator != (Point const &, Point const&);
	};

}

#endif

