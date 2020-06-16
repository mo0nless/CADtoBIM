#pragma once

#include <map>
#include <string>
#include "../../enums/headers/ShapesTypeEnum.h"

struct ShapesTypeEnumUtils
{
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
	{
		return CurvesBoundaryTypeEnum(boundaryBentleyInt);
	};
};



