#include "power_regression.h"

using namespace Math;

Point PowerRegression::toLinear(Point const& p)
{
	return Point(log(p.x), log(p.y));
}

void PowerRegression::calculate()
{
	Regression::calculate();
	b = parameters["a"];
	a = parameters["b"];
}

std::string PowerRegression::toString()
{
	int size = 500;
	char* buf = new char[size];
	sprintf_s(buf, size, "PowerRegression:\ncorrelation = %.8f\ny = %.4f * ( x ^ %.4f )", correlation, a, b);
	return buf;
}