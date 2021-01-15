#pragma once

/**
 * @file PropertyTypeEnumUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<map>
#include<string>
#include "../../enums/headers/PropertyTypeEnum.h"

using namespace std;
using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Class for Propertoies Enumeration
		 * 
		 */
		class PropertyTypeEnumUtils {

		private:
			static const map<PropertyTypeEnum, string> mappedValues;
			PropertyTypeEnumUtils() {}

		public:
			/**
			 * @brief Get the Enum By String Value
			 * 
			 * @param stringValue 
			 * @return PropertyTypeEnum 
			 */
			static PropertyTypeEnum getEnumByStringValue(string stringValue);

		};
	}
}