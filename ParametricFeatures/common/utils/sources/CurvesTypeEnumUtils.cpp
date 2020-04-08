#include "../headers/CurvesTypeEnumUtils.h"

std::map<CurvesShapeTypeEnum, std::string> CurvesTypeEnumUtils::mappedValuesDescriptor =
{	
	{ CurvesShapeTypeEnum::COMPLEX_CHAIN,"Complex Chain" },
	{ CurvesShapeTypeEnum::CIRCLE,"Circle" },
	{ CurvesShapeTypeEnum::ELLIPSE,"Ellipse" },
	{ CurvesShapeTypeEnum::SHAPE,"Shape" },
	{ CurvesShapeTypeEnum::NONE_CONTAINER,"" },
};

CurvesShapeTypeEnum CurvesTypeEnumUtils::getCurvesContainerTypeEnumByDescriptor(std::string elementDescriptor)
{

	for (auto const& element : mappedValuesDescriptor) {
		if (element.second == elementDescriptor) {
			return element.first;
		}
	}

	return CurvesShapeTypeEnum::CURVE;
}

CurvesPrimitivesTypeEnum CurvesTypeEnumUtils::getCurvesTypeEnumByInt(int curvebentleyInt)
{
	return CurvesPrimitivesTypeEnum(curvebentleyInt);
}

CurvesBoundaryTypeEnum CurvesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
{
	return CurvesBoundaryTypeEnum(boundaryBentleyInt);
}

