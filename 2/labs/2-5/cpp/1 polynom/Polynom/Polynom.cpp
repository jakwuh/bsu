#include "Polynom.h"

Polynom::Polynom(int _n) : n(_n)
{
	if (n < 0) throw NegativeDegree();
	co = (double*) calloc(n + 1, sizeof(double));
}

void Polynom::init(int _n, ...)
{
	va_list vl;
	va_start(vl, _n);
	for (int i = 0; i <= _n; i++)
		co[i] = va_arg(vl, double);
	va_end(vl);
}

Polynom::Polynom(const Polynom &p)
{
	n = p.n;
	co = (double*)std::memcpy(malloc(sizeof(double) * (n + 1)), p.co, sizeof(double) * (n + 1));
}

Polynom::~Polynom()
{
	delete co;
}

void Polynom::optimize()
{
	int _n = n;
	while (!co[_n] && _n) --_n;
	n = _n;
	double* oldCo = co;
	co = (double*) realloc(co, sizeof(double) * (n + 1));
}

double Polynom::calculate(double x) const
{
	double result = 0, _x = 1;
	for (int i = 0; i <= n; i++, _x *=x)
		result += co[i] * _x;
	return result;
}

Polynom& Polynom::operator = (const Polynom &p)
{
	n = p.n;
	co = (double*) std::memcpy(malloc(sizeof(double) * (n + 1)), p.co, sizeof(double) * (n + 1));
	return *this;
}

double& Polynom::operator [](int i) const
{
	if (i > n) throw AccessError();
	return co[i];
}

Polynom& Polynom::operator += (const Polynom &p)
{
	Polynom cp(*this);
	n = std::max(n, p.n);
	co = (double*) std::memcpy(calloc(n + 1, sizeof(double)), cp.co, sizeof(double) * (cp.n + 1));
	for (int i = 0; i <= p.n; i++) co[i] += p[i];
	optimize();
	return *this;
}

Polynom& Polynom::operator -= (const Polynom &p)
{
	*this += -p;
	return *this;
}

Polynom& Polynom::operator *= (const Polynom &p)
{
	const Polynom p1(*this);
	const Polynom &p2 = (this == &p ? Polynom(p) : p);
	n += p.n;
	co = (double*) calloc(n + 1, sizeof(double));
	for (int i = 0; i <= p1.n; ++i)
		for (int j = 0; j <= p2.n; ++j)
			co[i + j] += p1[i] * p2[j];
	optimize();
	return *this;
}

Polynom& Polynom::operator /= (const Polynom &p)
{
	if (p[p.n] == 0) throw UnoptimizedPolynom();
	Polynom d = (n - p.n < 0 ? Polynom(0) : Polynom(n - p.n));
	if (n - p.n >= 0) 
		for (int i = d.n; i >= 0; --i)
			d[i] = (*this - d * p)[i + p.n];
	n = d.n;
	double* oldCo = co;
	co = (double*) std::memcpy(calloc(d.n + 1, sizeof(double)), d.co, sizeof(double) * (d.n + 1));
	optimize();
	return *this;
}

Polynom Polynom::operator - () const
{
	Polynom p(*this);
	for (int i = 0; i <= p.n; ++i)
		p[i] *= -1;
	return p;
}

Polynom Polynom::operator + () const
{
	Polynom p(*this);
	return p;
}

Polynom operator + (const Polynom &p1, const Polynom &p2)
{
	Polynom p(p1);
	p += p2;
	return p;
}

Polynom operator - (const Polynom &p1, const Polynom &p2)
{
	Polynom p(p1);
	p -= p2;
	return p;
}

Polynom operator * (const Polynom &p1, const Polynom &p2)
{
	Polynom p(p1);
	p *= p2;
	return p;
}

Polynom operator / (const Polynom &p1, const Polynom &p2)
{
	Polynom p(p1);
	p /= p2;
	return p;
}

std::istream& operator >> (std::istream& in, Polynom &p){
	for (int i = 0; i <= p.n; ++i)in >> p[i];return in;
}

std::ostream& operator << (std::ostream& out, const Polynom &p)
{
	bool trigger = false;
	for (int i = p.n; i >= 0; --i) {
		if (!p[i]) continue;
		if (trigger) out << (p[i] < 0 ? " - " : " + ");
		else trigger = true;
		if (i == 0) out << std::abs(p[i]);
		else if(std::abs(p[i]) != 1) out << std::abs(p[i]);
		if (i == 0) continue;
		if (i == 1) out << "x";
		else out << "x^" << i;
	}
	if (!trigger) out << 0;
	return out;
}