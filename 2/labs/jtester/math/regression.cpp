#include "regression.h"

using namespace Math;

namespace std
{
	
	template <typename T>
	T sqr(T t)
	{
		return t * t;
	}

}

Regression::Regression(){}

Regression::Regression(Regression const& r)
{
	points = r.points;
}

Regression::Regression(Points const& p)
{
	points = p;
}

Regression::Regression(std::map< double, double > const& points)
{
	for (auto it : points) {
		add(Point(it.first, it.second));
	}
}


Points Regression::toLinear()
{
	Points ps = points;
	for (auto &it : ps) {
		it = toLinear(it);
	}
	return ps;
}

Regression& Regression::add(Point const& p)
{
	points.push_back(p);
	return *this;
}

/**
 * @brief remove point from points
 * 
 * @param count number of points to delete. If count = 0 then 
 * all points will be deleted. Otherway not greater than count 
 * points will be deleted
 */
Regression& Regression::remove(Point const& p, int count)
{
	if (count == 0) count = points.size();
	Points::iterator it = points.begin();
	while (it != points.end() && count > 0)
	{
		if (*it == p) {
			it = points.erase(it);
		} else {
			++it;
		}
	}
	return *this;
}

unsigned int Regression::count()
{
	return points.size();
}

Regression& Regression::set(Points const& ps)
{
	points = ps;
	return *this;
}

void Regression::calculate()
{
	Points ps = toLinear();
	unsigned int count = ps.size();
	double sum_x = 0, sum_y = 0, sum_xy = 0;
	double sum_xx = 0, sum_yy = 0;
	double average_x = 0, average_y = 0, average_xy = 0;
	double average_xx = 0, average_yy = 0;
	double dispersion_xy = 0, covariation_x = 0, covariation_y = 0;
	correlation = 0;
	double a = 0, delta_a = 0, b = 0, delta_b = 0;
	double epsilon_a = 0, epsilon_b = 0;

	if (count <= 2) throw gcnew ::Exception::TooFewPointsException();

	for (auto it : ps) {
		sum_x += it.x;
		sum_y += it.y;
		sum_xy += it.x * it.y;
		sum_xx += std::sqr(it.x);
		sum_yy += std::sqr(it.y);
	}

	average_x = sum_x / count;
	average_y = sum_y / count;
	average_xy = sum_xy / count;
	average_xx = sum_xx / count;
	average_yy = sum_yy / count;

	dispersion_xy = average_xy - average_x * average_y;
	covariation_x = std::sqrt(average_xx - average_x * average_x);
	covariation_y = std::sqrt(average_yy - average_y * average_y);
	correlation = dispersion_xy / (covariation_x * covariation_y);
	a = dispersion_xy / (covariation_x * covariation_x);
	b = average_y - a * average_x;
	delta_a = 2 * std::sqrt((std::sqr(covariation_y) / std::sqr(covariation_x) - std::sqr(a)) / (count - 2));
	delta_b = delta_a * std::sqrt(std::sqr(covariation_x) - std::sqr(average_x));
	epsilon_a = delta_a / a;
	epsilon_b = delta_b / b;

	parameters["count"] = count;
	parameters["sum_x"] = sum_x;
	parameters["sum_y"] = sum_y;
	parameters["sum_xy"] = sum_xy;
	parameters["sum_xx"] = sum_xx;
	parameters["sum_yy"] = sum_yy;
	parameters["average_x"] = average_x;
	parameters["average_y"] = average_y;
	parameters["average_xy"] = average_xy;
	parameters["average_xx"] = average_xx;
	parameters["average_yy"] = average_yy;
	parameters["dispersion_xy"] = dispersion_xy;
	parameters["covariation_x"] = covariation_x;
	parameters["covariation_y"] = covariation_y;
	parameters["correlation"] = correlation;
	parameters["a"] = a;
	parameters["b"] = b;
	parameters["delta_a"] = delta_a;
	parameters["delta_b"] = delta_b;
	parameters["epsilon_a"] = epsilon_a;
	parameters["epsilon_b"] = epsilon_b;
}

double Regression::operator [] (std::string const& name)
{
	return parameters[name];
}
