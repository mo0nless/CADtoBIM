#pragma once

/**
 * @file SmartFeatureTypeEnumUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../enums/headers/SmartFeatureTypeEnum.h"
#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Struct for SmartFeature enum utility
		 * 
		 */
		class SmartFeatureTypeEnumUtils {
		public:
			/**
			 * @brief Get the Smart Feature Type Enum By Class Name object
			 * 
			 * @param classNameValue 
			 * @return SmartFeatureTypeEnum 
			 */
			static SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(string classNameValue);

		private:

			SmartFeatureTypeEnumUtils() {};
			static map<SmartFeatureTypeEnum, vector<string>> mappedValues;
		};
	}
}