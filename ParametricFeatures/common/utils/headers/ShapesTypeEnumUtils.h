#pragma once


#include "../../enums/headers/ShapesTypeEnum.h"

using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		struct ShapesTypeEnumUtils
		{
			static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
			{
				return CurvesBoundaryTypeEnum(boundaryBentleyInt);
			};
		};
	}
}


