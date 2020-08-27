#pragma once


#include "../../enums/headers/ShapesTypeEnum.h"

struct ShapesTypeEnumUtils
{
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
	{
		return CurvesBoundaryTypeEnum(boundaryBentleyInt);
	};
};



