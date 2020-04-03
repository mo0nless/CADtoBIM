#pragma once

#include <map>
#include <string>
#include "../../enums/headers/CurvesTypeEnum.h"

class CurvesTypeEnumUtils
{
public:	
	static CurvesContainerTypeEnum getCurvesContainerTypeEnumByDescriptor(std::string elementDescriptor);
	static CurvesTypeEnum getCurvesTypeEnumByInt(int curvebentleyInt);
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt);

private:
	static std::map<CurvesContainerTypeEnum, std::string> mappedValuesDescriptor;
	CurvesTypeEnumUtils() {};

};

