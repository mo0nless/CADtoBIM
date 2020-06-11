#pragma once

#include <map>
#include <string>
#include "../../enums/headers/ShapesTypeEnum.h"

class ShapesTypeEnumUtils
{
public:	
	static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt);

private:
	ShapesTypeEnumUtils() {};

};

