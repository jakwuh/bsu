// y = a * ln ( x ) + b

#ifndef __LOGARITHMIC_REGRESSION_H_INCLUDED__
#define __LOGARITHMIC_REGRESSION_H_INCLUDED__

#include "..\math\regression.h"

namespace Math
{

	class LogarithmicRegression : public Regression
	{
	private:
		double a, b;
	protected:
		Point toLinear(Point const&);
	public:
		LogarithmicRegression() : Regression() {};
	    LogarithmicRegression(Points const& ps) : Regression(ps) {};
	    LogarithmicRegression(std::map< double, double > const& map) : Regression(map) {};
		void calculate();
		std::string toString();
	};

}

#endif

