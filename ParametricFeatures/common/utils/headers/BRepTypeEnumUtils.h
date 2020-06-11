#pragma once

#include "../../enums/headers/BRepTypeEnum.h"

struct BRepTypeEnumUtils
{
	static BRepTypeEnum BRepTypeEnumUtils::getBRepTypeEnumByInt(int boundaryBentleyInt)
	{
		return BRepTypeEnum(boundaryBentleyInt);
	}
};



