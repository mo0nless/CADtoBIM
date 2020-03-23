#include "../headers/CurvesTypeEnum.h"

namespace CurvesTypeEnum
{
	CurvesTypeEnum getCurvesTypeEnumByClassName(std::string className)
	{
		std::map<CurvesTypeEnum, std::string> mappedValues =
		{
			{ CurvesTypeEnum::AKIMA_CURVE,"Akima Curve" },
			{ CurvesTypeEnum::ARC,"Arc" },
			{ CurvesTypeEnum::BSPLINE,"Bspline Curve" },
			{ CurvesTypeEnum::CURVE_VECTOR,"Curve Vector" },
			{ CurvesTypeEnum::INTERPOLATION_CURVE,"Interpolation Curve" },
			{ CurvesTypeEnum::LINE,"Line" },
			{ CurvesTypeEnum::LINE_STRING,"Line String" },
			{ CurvesTypeEnum::PARTIAL_CURVE,"Partial Curve" },
			{ CurvesTypeEnum::POINT_STRING,"Point String" },
			{ CurvesTypeEnum::SPIRAL,"Spiral" },

		};

		for (auto const& element : mappedValues) {
			if (element.second == className) {
				return element.first;
			}
		}
	}
}