#ifndef __FRACTION_H_INCLUDED__
#define __FRACTION_H_INCLUDED__

#include <iostream>
#include "error.h"

class Fraction
{
private:
	long a, b;
	void reduce();
public:
	Fraction(long = 0, long = 1);
	Fraction(const Fraction&);
	Fraction& operator = (const Fraction&);
	Fraction& operator += (const Fraction&);
	Fraction& operator -= (const Fraction&);
	Fraction& operator *= (const Fraction&);
	Fraction& operator /= (const Fraction&);
	// explicit operator double() const; // will work only in C++11
	operator double() const; 
	friend Fraction operator - (const Fraction&);
	friend Fraction operator + (const Fraction&);
	friend bool operator < (const Fraction&, const Fraction&);
	friend bool operator > (const Fraction&, const Fraction&);
	friend bool operator == (const Fraction&, const Fraction&);
	friend bool operator != (const Fraction&, const Fraction&);
	friend bool operator <= (const Fraction&, const Fraction&);
	friend bool operator >= (const Fraction&, const Fraction&);
	friend Fraction operator + (const Fraction&, const Fraction&);
	friend Fraction operator - (const Fraction&, const Fraction&);
	friend Fraction operator * (const Fraction&, const Fraction&);
	friend Fraction operator / (const Fraction&, const Fraction&);
	friend std::istream& operator >> (std::istream& in, Fraction&);
	friend std::ostream& operator << (std::ostream& out, const Fraction&);
};
	
#endif