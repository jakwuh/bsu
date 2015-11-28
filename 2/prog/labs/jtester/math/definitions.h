#ifndef __DEFINITIONS_H_INCLUDED__
#define __DEFINITIONS_H_INCLUDED__

#include <vector>
#include <map>
#include <string>
#include "..\math\point.h"
#include "..\core\config.h"

namespace Exception
{
	
	ref class TooFewPointsException : public Exception
	{
	public:
		TooFewPointsException() : Exception("Too few points were provided") {};
	};

}

namespace Math
{

	typedef ::std::vector<::Math::Point> Points;
	typedef ::std::map<double, double> PointsMap;

}

#endif

