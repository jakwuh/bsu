#ifndef __REGRESSION_H_INCLUDED__
#define __REGRESSION_H_INCLUDED__

#include "..\math\definitions.h"
#include "..\math\point.h"
#include <map>
#include <string>
#include <cmath>

namespace Math
{

	class Regression
	{
	protected:
		std::map<std::string, double> parameters;
		Points points;
		virtual	Point toLinear(Point const&) = 0;
		Points toLinear();
	public:
		double correlation;
	    Regression();
	    Regression(Regression const&);
	    Regression(Points const&);
	    Regression(std::map< double, double > const&);
	    Regression& add(Point const&);
	    Regression& remove(Point const&, int = 0);
	    unsigned int count();
	    Regression& set(Points const&);
	    double operator [] (std::string const&);
	    virtual void calculate();
	    virtual std::string toString() = 0;
	};

}

#endif