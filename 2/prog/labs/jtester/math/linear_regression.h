// y = a * x + b

#ifndef __LINEAR_REGRESSION_H_INCLUDED__
#define __LINEAR_REGRESSION_H_INCLUDED__

#include "..\math\regression.h"

namespace Math
{

	class LinearRegression : public Regression
	{
	private:
		double a, b;
	protected:
		Point toLinear(Point const&);
	public:
		LinearRegression() : Regression() {};
	    LinearRegression(Points const& ps) : Regression(ps) {};
	    LinearRegression(std::map< double, double > const& map) : Regression(map) {};
		void calculate();
		std::string toString();
	};

}

#endif

