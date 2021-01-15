#pragma once

/**
 * @file ReaderPropertiesEnumUtils.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <map>
#include <string>

#include "../../enums/headers/ReaderPropertiesEnum.h"

using namespace std;
using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		*  @brief Class used to contain the immutable map between ReaderPropertiesEnum and the string value from the modeler
		*
		*/
		class ReaderPropertiesEnumUtils {
		public:

			/**
			*  @brief static method to retrieve enum value based on the string(label) value received from the modeler
			*
			*  @param stringValue[in]
			*  @return ReaderPropertiesEnum
			*/
			static ReaderPropertiesEnum getElementPropertiesEnumByStringValue(string stringValue);
			static ReaderPropertiesEnum getElementPropertiesEnumByInt(int primitiveBentleyInt);

		private:
			/**
			* @brief Hide contructor to have a static class
			*/
			ReaderPropertiesEnumUtils() {};

			/**
			* @brief map contains relevant and needed properties from the reader, enum as keys and values as the string(label) value from modeler
			*/
			static map<ReaderPropertiesEnum, string> mappedValues;

		};
	}
}