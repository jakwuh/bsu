// y = a * x * log( x ) + b

#ifndef __QUASILOG_REGRESSION_H_INCLUDED__
#define __QUASILOG_REGRESSION_H_INCLUDED__

#include "..\math\regression.h"

namespace Math
{

	class QuasilogRegression : public Regression
	{
	private:
		double a, b;
	protected:
		Point toLinear(Point const&);
	public:
		QuasilogRegression() : Regression() {};
	    QuasilogRegression(Points const& ps) : Regression(ps) {};
	    QuasilogRegression(std::map< double, double > const& map) : Regression(map) {};
		void calculate();
		std::string toString();
	};

}

#endif

