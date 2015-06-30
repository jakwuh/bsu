#ifndef __POLYNOM_H_INCLUDED__
#define __POLYNOM_H_INCLUDED__

#include <cstring>
#include <algorithm>
#include <iostream>
#include <cstdarg>

class Error
{
public:
	virtual char* what() = 0;
};
class ZeroDivision : public Error
{
public:
	char* what(){ return "Division on zero"; }
};
class AccessError : public Error
{
	char* what(){ return "Trying to access wrong index"; }
};
class DifferentDegrees : public Error
{
public:
	char* what(){ return "Polynoms have different degrees"; }
};
class NegativeDegree : public Error
{
public:
	char* what(){ return "Wrong polynom degree"; };
};
class UnoptimizedPolynom : public Error
{
	char* what(){ return "Unoptimized polynom"; }
};

class Polynom
{
	int n;
	double*	co;
	Polynom();
	void optimize();
public:
	Polynom(int);
	Polynom(const Polynom&);
	~Polynom();
	void init(int...);
	double calculate(double) const;
	Polynom& operator = (const Polynom&);
	double& operator [](int) const;
	Polynom& operator += (const Polynom&);
	Polynom& operator -= (const Polynom&);
	Polynom& operator *= (const Polynom&);
	Polynom& operator /= (const Polynom&);
	Polynom operator - () const;
	Polynom operator + () const;
	friend Polynom operator + (const Polynom&, const Polynom&);
	friend Polynom operator - (const Polynom&, const Polynom&);
	friend Polynom operator * (const Polynom&, const Polynom&);
	friend Polynom operator / (const Polynom&, const Polynom&);
	friend std::istream& operator >> (std::istream&, Polynom&);
	friend std::ostream& operator << (std::ostream&, const Polynom&);
};
	
#endif