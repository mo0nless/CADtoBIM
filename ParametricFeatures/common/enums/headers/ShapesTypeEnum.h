#pragma once


namespace Common
{
	namespace Enums
	{
		//ORDER matters for mapping functions
		//The ShapesTypeEnum & CurvesBoundaryTypeEnum enumeration classes order represent the same as the one in Bentley OpenPlant Environment

		enum class CurvesPrimitivesTypeEnum
		{
			NONE = 0,
			LINE = 1,
			LINE_STRING = 2,
			ARC = 3,
			BSPLINE = 4,
			INTERPOLATION_CURVE = 5,
			AKIMA_CURVE = 6,
			POINT_STRING = 7,
			CURVE_VECTOR = 8,
			SPIRAL = 9,
			PARTIAL_CURVE = 10,
		};

		enum class CurvesBoundaryTypeEnum
		{
			NONE_BOUNDARY = 0,
			OPEN = 1,
			OUTER = 2,
			INNER = 3,
			PARITY_REGION = 4,
			UNION_REGION = 5,

		};

		enum class ShapesTypeEnum
		{
			NONE_CONTAINER = 0,
			COMPLEX_CHAIN = 1,
			CIRCLE = 2,
			ELLIPSE = 3,
			SHAPE = 4,
			CURVE = 5,
		};
	}
}