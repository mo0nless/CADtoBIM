#pragma once

#include "../../enums/headers/BRepTypeEnum.h"

using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		struct BRepTypeEnumUtils
		{
			static BRepTypeEnum BRepTypeEnumUtils::getBRepTypeEnumByInt(int boundaryBentleyInt)
			{
				return BRepTypeEnum(boundaryBentleyInt);
			}
		};

	}
}

