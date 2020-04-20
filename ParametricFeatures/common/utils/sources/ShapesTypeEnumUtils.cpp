#include "../headers/ShapesTypeEnumUtils.h"

std::map<ShapesTypeEnum, std::string> ShapesTypeEnumUtils::mappedValuesDescriptor =
{	
	{ ShapesTypeEnum::COMPLEX_CHAIN,"Complex Chain" },
	{ ShapesTypeEnum::CIRCLE,"Circle" },
	{ ShapesTypeEnum::ELLIPSE,"Ellipse" },
	{ ShapesTypeEnum::SHAPE,"Shape" },
	{ ShapesTypeEnum::NONE_CONTAINER,"" },
};

ShapesTypeEnum ShapesTypeEnumUtils::getShapesTypeEnumByDescriptor(std::string elementDescriptor)
{

	for (auto const& element : mappedValuesDescriptor) {
		if (element.second == elementDescriptor) {
			return element.first;
		}
	}

	return ShapesTypeEnum::CURVE;
}

CurvesPrimitivesTypeEnum ShapesTypeEnumUtils::getCurvesTypeEnumByInt(int curvebentleyInt)
{
	return CurvesPrimitivesTypeEnum(curvebentleyInt);
}

CurvesBoundaryTypeEnum ShapesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
{
	return CurvesBoundaryTypeEnum(boundaryBentleyInt);
}

