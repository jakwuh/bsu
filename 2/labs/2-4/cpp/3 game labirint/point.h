#ifndef __POINT_H_INCLUDED__
#define __POINT_H_INCLUDED__

#include <iostream>
#include <cmath>

class Error{
public:
	virtual const char* what() = 0;
};

class DifferentDimensions : public Error {
public:
	const char* what()
	{
		return "Размерности точек отличаются";
	}
};

class WrongSize : public Error {
public:
	const char* what()
	{
		return "Неверная размерность точки";
	}
};

class Point
{
private:
	const int size;
	double* c;
	double mod() const;
public:
	Point(int = 1);
	Point(double*, int = 1);
	Point(const Point&);
	Point& operator = (const Point&);
	Point& operator += (const Point&);
	Point& operator -= (const Point&);
	double& operator [] (int);
	friend double mod(const Point&);
	friend Point operator - (const Point&);
	friend Point operator + (const Point&);
	friend bool operator < (const Point&, const Point&);
	friend bool operator > (const Point&, const Point&);
	friend bool operator == (const Point&, const Point&);
	friend bool operator != (const Point&, const Point&);
	friend bool operator <= (const Point&, const Point&);
	friend bool operator >= (const Point&, const Point&);
	friend Point operator + (const Point&, const Point&);
	friend Point operator - (const Point&, const Point&);
	friend std::istream& operator >> (std::istream& in, Point&);
	friend std::ostream& operator << (std::ostream& out, const Point&);
};
	
#endif