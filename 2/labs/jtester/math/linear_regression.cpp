#include "linear_regression.h"

using namespace Math;

Point LinearRegression::toLinear(Point const& p)
{
	return p;
}

void LinearRegression::calculate()
{
	Regression::calculate();
	a = parameters["a"];
	b = parameters["b"];
}

std::string LinearRegression::toString()
{
	int size = 500;
	char* buf = new char[size];
	sprintf_s(buf, size, "LinearRegression:\ncorrelation = %.8f\ny = %.4f * x + %.4f", correlation, a, b);
	return buf;
}