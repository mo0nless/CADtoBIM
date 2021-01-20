#pragma once

/**
 * @file ReaderPropertyDefinition.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <Bentley/WString.h>
#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

using namespace std;

namespace Modeler
{
	namespace Properties
	{
		/**
		 * @brief Base class for the single Property definition
		 * 
		 */
		class ReaderPropertyDefinition {

		private:
			string propertyName;
			string propertyTypeName;
			ECValue propertyValue;
			string propertyValueAsString;

		public:
			/**
			 * @brief Construct a new Reader Property Definition object
			 * 
			 * @param newPropertyName Name
			 * @param newPropertyTypeName Type
			 * @param newPropertyValue Value
			 * @param newPropertyValueAsString Value as string
			 */
			ReaderPropertyDefinition(string newPropertyName, string newPropertyTypeName, ECValue newPropertyValue, string newPropertyValueAsString);

			/**
			 * @brief Get the Property Name object
			 * 
			 * @return string 
			 */
			string getPropertyName();

			/**
			 * @brief Get the Property Type Name object
			 * 
			 * @return string 
			 */
			string getPropertyTypeName();

			/**
			 * @brief Get the Property Value object
			 * 
			 * @return ECValue 
			 */
			ECValue getPropertyValue();

			/**
			 * @brief Get the Property Value As String object
			 * 
			 * @return string 
			 */
			string getPropertyValueAsString();

		};
	}
}