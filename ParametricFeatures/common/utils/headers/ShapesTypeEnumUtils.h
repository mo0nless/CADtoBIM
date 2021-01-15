#pragma once

/**
 * @file ShapesTypeEnumUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../enums/headers/ShapesTypeEnum.h"

using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Struct for Shapes and curves enum utility
		 * 
		 */
		struct ShapesTypeEnumUtils
		{
			/**
			 * @brief Get the Curves Boundary Type Enum By Int 
			 * 
			 * @param boundaryBentleyInt 
			 * @return CurvesBoundaryTypeEnum 
			 */
			static CurvesBoundaryTypeEnum getCurvesBoundaryTypeEnumByInt(int boundaryBentleyInt)
			{
				return CurvesBoundaryTypeEnum(boundaryBentleyInt);
			};
		};
	}
}


