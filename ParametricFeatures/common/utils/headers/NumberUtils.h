#pragma once

/**
 * @file NumberUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"
#include <math.h>

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Number utility to convert from bentley unit system to meter
		 * 
		 */
		struct NumberUtils
		{
			/**
			 * @brief Get the correct value converted in meter
			 * 
			 * @param value 
			 * @return double 
			 */
			static double NumberUtils::convertCurrentUnitToMeters(double value)
			{
				DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
				ModelInfoCP modelInfo = dgnModelRef->GetModelInfoCP();

				double uorPerStorage = modelInfo->GetUorPerStorage();

				return value / uorPerStorage;
			}
		};
	}
}