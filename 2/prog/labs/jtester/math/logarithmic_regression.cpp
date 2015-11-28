#include "logarithmic_regression.h"

using namespace Math;

Point LogarithmicRegression::toLinear(Point const& p)
{
	return Point(log(p.x), p.y);
}

void LogarithmicRegression::calculate()
{
	Regression::calculate();
	a = parameters["a"]; 
	b = parameters["b"];
}

std::string LogarithmicRegression::toString()
{
	int size = 500;
	char* buf = new char[size];
	sprintf_s(buf, size, "LogarithmicRegression:\ncorrelation = %.8f\ny = %.4f * log(x) + %.4f", correlation, a, b);
	return buf;
}