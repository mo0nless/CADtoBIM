#pragma once

#include <map>
#include <string>
#include "../../enums/headers/ShapesTypeEnum.h"

class ShapesTypeEnumUtils
{
public:	
	static ShapesTypeEnum getShapesTypeEnumByDescriptor(std::string elementDescriptor);
	static CurvesPrimitivesTypeEnum getCurvesTypeEnumByInt(int curvebentleyInt);
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt);

private:
	static std::map<ShapesTypeEnum, std::string> mappedValuesDescriptor;
	ShapesTypeEnumUtils() {};

};

