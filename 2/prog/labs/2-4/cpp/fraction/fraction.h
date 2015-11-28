#ifndef __FRACTION_H_INCLUDED__
#define __FRACTION_H_INCLUDED__

#include <iostream>

class Error{
public:
	virtual const char* what() = 0;
};

class ZeroDivision : public Error {
public:
	const char* what()
	{
		return "Деление на ноль";
	}
};

class Fraction
{
private:
	long a, b;
	void reduce();
public:
	Fraction(long, long = 1);
	Fraction(const Fraction&);
	Fraction& operator = (const Fraction&);
	Fraction& operator += (const Fraction&);
	Fraction& operator -= (const Fraction&);
	Fraction& operator *= (const Fraction&);
	Fraction& operator /= (const Fraction&);
	explicit operator double() const; 
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