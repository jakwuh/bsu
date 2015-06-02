#include "quasilog_regression.h"

using namespace Math;

Point QuasilogRegression::toLinear(Point const& p)
{
	return Point(p.x * log(p.x), p.y);
}

void QuasilogRegression::calculate()
{
	Regression::calculate();
	a = parameters["a"]; 
	b = parameters["b"];
}

std::string QuasilogRegression::toString()
{
	int size = 500;
	char* buf = new char[size];
	sprintf_s(buf, size, "QuasilogRegression:\ncorrelation = %.8f\ny = %.4f * x * log(x) + %.4f", correlation, a, b);
	return buf;
}