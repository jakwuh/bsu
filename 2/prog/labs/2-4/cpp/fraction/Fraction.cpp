#include "fraction.h"

long gcd(long a, long b)
{
	if (a < 0) a *= -1;
	if (b < 0) b *= -1;
	if ( a==0 ) return b;
	return gcd ( b % a, a );
}

void Fraction::reduce() {
	long gcdn = gcd(a, b);
	a /= gcdn; 
	b /= gcdn;
}

Fraction::Fraction(long _a, long _b) 
{
	if (!_b) throw ZeroDivision();
	a = _a;
	b = _b;
	reduce();
}

Fraction::Fraction(const Fraction& f)
{
	a = f.a;
	b = f.b;
	reduce();
}

Fraction& Fraction::operator = (const Fraction& f)
{
	a = f.a;
	b = f.b;
	reduce();
	return *this;
}

Fraction& Fraction::operator += (const Fraction& f)
{
	a = a * f.b + b * f.a;
	b = b * f.b;
	reduce();
	return *this;
}

Fraction& Fraction::operator -= (const Fraction& f)
{
	a = a * f.b - b * f.a;
	b = b * f.b;
	reduce();
	return *this;
}
Fraction& Fraction::operator *= (const Fraction& f)
{
	a *= f.a;
	b *= f.b;
	reduce();
	return *this;
}


Fraction& Fraction::operator /= (const Fraction& f)
{
	a *= f.b;
	b *= f.a;
	reduce();
	return *this;
}

Fraction::operator double() const 
{
	return double(a) / double(b);
}

Fraction operator - (const Fraction& f)
{
	return Fraction(-f.a, f.b);
}

Fraction operator + (const Fraction& f)
{
	return f;
}

bool operator < (const Fraction& f1, const Fraction& f2)
{
	return f1.a * f2.b - f1.b * f2.a < 0;
}

bool operator > (const Fraction& f1, const Fraction& f2)
{
	return f1.a * f2.b - f1.b * f2.a > 0;
}

bool operator == (const Fraction& f1, const Fraction& f2)
{
	return f1.a * f2.b - f1.b * f2.a == 0;
}

bool operator != (const Fraction& f1, const Fraction& f2) 
{
	return f1.a * f2.b - f1.b * f2.a != 0;
}

bool operator <= (const Fraction& f1, const Fraction& f2)
{
	return f1.a * f2.b - f1.b * f2.a <= 0;
}

bool operator >= (const Fraction& f1, const Fraction& f2)
{
	return f1.a * f2.b - f1.b * f2.a >= 0;
}

Fraction operator + (const Fraction& f1, const Fraction& f2)
{
	return Fraction(f1.a * f2.b + f1.b * f2.a, f1.b * f2.b);
}

Fraction operator - (const Fraction& f1, const Fraction& f2)
{
	return Fraction(f1.a * f2.b - f1.b * f2.a, f1.b * f2.b);
}

Fraction operator * (const Fraction& f1, const Fraction& f2)
{
	return Fraction(f1.a * f2.a, f1.b * f2.b);
}

Fraction operator / (const Fraction& f1, const Fraction& f2)
{
	return Fraction(f1.a * f2.b, f1.b * f2.a);
}

std::istream& operator >> (std::istream& in, Fraction& f)
{
	in >> f.a >> f.b;
	if (f.b == 0) throw ZeroDivision();
	f.reduce();
	return in;
}

std::ostream& operator << (std::ostream& out, const Fraction& f)
{
	if (f.b != 1)
		out << f.a << "/" << f.b;
	else 
		out << f.a;
	return out;
}