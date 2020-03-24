#include "../headers/CurvesTypeEnum.h"

namespace CurvesTypeEnum
{
	const std::map<CurvesTypeEnum, std::string> mappedValues =
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
		{ CurvesTypeEnum::NONE,"" },
	};

	CurvesTypeEnum getCurvesTypeEnumByClassName(std::string elementDescriptor)
	{

		for (auto const& element : mappedValues) {
			if (element.second == elementDescriptor) {
				return element.first;
			}
		}

		return CurvesTypeEnum::NONE;
	}
}