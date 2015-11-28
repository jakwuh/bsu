// y = a * x ^ b

#ifndef __POWER_REGRESSION_H_INCLUDED__
#define __POWER_REGRESSION_H_INCLUDED__

#include "..\math\regression.h"

namespace Math
{

	class PowerRegression : public Regression
	{
	private:
		double a, b;
	protected:
		Point toLinear(Point const&);
	public:
		PowerRegression() : Regression() {};
	    PowerRegression(Points const& ps) : Regression(ps) {};
	    PowerRegression(std::map< double, double > const& map) : Regression(map) {};
		void calculate();
		std::string toString();
	};

}

#endif

