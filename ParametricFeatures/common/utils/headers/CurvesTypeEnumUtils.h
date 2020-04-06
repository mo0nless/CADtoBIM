#pragma once

#include <map>
#include <string>
#include "../../enums/headers/CurvesTypeEnum.h"

class CurvesTypeEnumUtils
{
public:	
	static CurvesShapeTypeEnum getCurvesContainerTypeEnumByDescriptor(std::string elementDescriptor);
	static CurvesPrimitivesTypeEnum getCurvesTypeEnumByInt(int curvebentleyInt);
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt);

private:
	static std::map<CurvesShapeTypeEnum, std::string> mappedValuesDescriptor;
	CurvesTypeEnumUtils() {};

};

