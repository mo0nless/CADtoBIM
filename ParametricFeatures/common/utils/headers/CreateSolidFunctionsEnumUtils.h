#pragma once

/**
 * @file CreateSolidFunctionsEnumUtils.h
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

#include "../../enums/headers/CreateSolidFunctionsEnum.h"

using namespace std;
using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		/**
		 * @brief Solid Creation enumeration utility
		 * 
		 */
		class CreateSolidFunctionsEnumUtils {

		private:
			CreateSolidFunctionsEnumUtils() {};
			static map<CreateSolidFunctionsEnum, string> mappedValues;
			static map<CreateSolidPropertiesEnum, string> mappedValuesProps;

		public:
			/**
			 * @brief Get the Create Solid Functions Enum By Class Name object
			 * 
			 * @param className 
			 * @return CreateSolidFunctionsEnum 
			 */
			static CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(string className);

			/**
			 * @brief Get the Solid Properties Enum By Class Name object
			 * 
			 * @param className 
			 * @return CreateSolidPropertiesEnum 
			 */
			static CreateSolidPropertiesEnum getSolidPropertiesEnumByClassName(string className);
		};
	}
}