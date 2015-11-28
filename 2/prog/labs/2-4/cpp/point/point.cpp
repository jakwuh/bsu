#include "point.h"	

Point::Point(int _size) : size(_size)
{
	if (size < 1) throw WrongSize();
	c = new double[size];
};


Point::Point(double* _c, int _size) : size(_size)
{
	if (size < 1) throw WrongSize();
	c = new double[size];
	for (int i = 0; i < size; i++)
		c[i] = _c[i];
}

Point::Point(const Point& p) : size(p.size)
{
	c = new double[size];
	for (int i = 0; i < size; i++)
		c[i] = p.c[i];
}

double& Point::operator [] (int i)
{
	if (i > size) throw DifferentDimensions();
	return c[i];
}

double Point::mod() const
{
	double l2 = 0;
	for (int i = 0; i < size; i++)
		l2 += c[i] * c[i];
	return sqrt(l2);
}

Point& Point::operator = (const Point& p)
{
	if (size != p.size) throw DifferentDimensions();
	for (int i = 0; i < size; i++)
		c[i] = p.c[i];
	return *this;
}

Point& Point::operator += (const Point& p)
{
	if (size != p.size) throw DifferentDimensions();
	for (int i = 0; i < size; i++)
		c[i] += p.c[i];
	return *this;
}

Point& Point::operator -= (const Point& p)
{
	if (size != p.size) throw DifferentDimensions();
	for (int i = 0; i < size; i++)
		c[i] -= p.c[i];
	return *this;
}

double mod(const Point& p)
{
	return p.mod();
}

Point operator - (const Point& p)
{
	Point tmp(p.c, p.size);
	for (int i = 0; i < tmp.size; i++)
		tmp.c[i] *= -1;
	return tmp;
}

Point operator + (const Point& p)
{
	return p;
}

bool operator < (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) < mod(p2);
}

bool operator > (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) > mod(p2);
}

bool operator == (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) == mod(p2);
}

bool operator != (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) != mod(p2);
}

bool operator <= (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) <= mod(p2);
}

bool operator >= (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	return mod(p1) >= mod(p2);
}

Point operator + (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	Point tmp(p1.c, p1.size);
	for (int i = 0; i < p1.size; i++)
		tmp.c[i] += p2.c[i];
	return tmp;
}

Point operator - (const Point& p1, const Point& p2)
{
	if (p1.size != p2.size) throw DifferentDimensions();
	Point tmp(p1.c, p1.size);
	for (int i = 0; i < p1.size; i++)
		tmp.c[i] -= p2.c[i];
	return tmp;
}

std::istream& operator >> (std::istream& in, Point& p)
{
	for (int i = 0; i < p.size; i++)
		in >> p.c[i];
	return in;
}
std::ostream& operator << (std::ostream& out, const Point& p)
{
	out << p.size << ": ";
	for (int i = 0; i < p.size; i++)
		out << p.c[i] << ' ';
	return out;
}