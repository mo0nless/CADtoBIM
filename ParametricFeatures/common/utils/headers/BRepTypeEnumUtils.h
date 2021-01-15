#pragma once

/**
 * @file BRepTypeEnumUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../enums/headers/BRepTypeEnum.h"

using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief BRep Utilities structure
		 * 
		 */
		struct BRepTypeEnumUtils
		{
			/**
			 * @brief Get the BRep Type Enumeration
			 * 
			 * @param boundaryBentleyInt 
			 * @return BRepTypeEnum 
			 */
			static BRepTypeEnum BRepTypeEnumUtils::getBRepTypeEnumByInt(int boundaryBentleyInt)
			{
				return BRepTypeEnum(boundaryBentleyInt);
			}
		};

	}
}

