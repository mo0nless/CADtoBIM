#include "../headers/CurvesTypeEnumUtils.h"

std::map<CurvesContainerTypeEnum, std::string> CurvesTypeEnumUtils::mappedValuesDescriptor =
{	
	{ CurvesContainerTypeEnum::COMPLEX_CHAIN,"Complex Chain" },
	{ CurvesContainerTypeEnum::CIRCLE,"Circle" },
	{ CurvesContainerTypeEnum::ELLIPSE,"Ellipse" },
	{ CurvesContainerTypeEnum::SHAPE,"Shape" },
	{ CurvesContainerTypeEnum::NONE_CONTAINER,"" },
};

CurvesContainerTypeEnum CurvesTypeEnumUtils::getCurvesContainerTypeEnumByDescriptor(std::string elementDescriptor)
{

	for (auto const& element : mappedValuesDescriptor) {
		if (element.second == elementDescriptor) {
			return element.first;
		}
	}

	return CurvesContainerTypeEnum::NONE_CONTAINER;
}

CurvesTypeEnum CurvesTypeEnumUtils::getCurvesTypeEnumByInt(int curvebentleyInt)
{
	return CurvesTypeEnum(curvebentleyInt);
}

CurvesBoundaryTypeEnum CurvesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
{
	return CurvesBoundaryTypeEnum(boundaryBentleyInt);
}

