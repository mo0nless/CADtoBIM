#pragma once

#include <map>
#include <string>

namespace CurvesTypeEnum
{
	enum CurvesTypeEnum
	{
		LINE,
		ARC,
		LINE_STRING,
		BSPLINE,
		AKIMA_CURVE,
		CURVE_VECTOR,
		INTERPOLATION_CURVE,
		PARTIAL_CURVE,
		POINT_STRING,
		SPIRAL,
		NONE
	};

	CurvesTypeEnum getCurvesTypeEnumByClassName(std::string className);
}
