#pragma once

/**
 * @file ComponentsMapping.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>

using namespace std;

namespace DataBase
{
	namespace Models
	{
		/**
		 * @brief Internal Object Class for the components
		 * 
		 * @see EntitiesMapper DataBaseContext
		 */
		class ComponentsMapping {

		private:
			int _id;

			string _modelerComponentName;
			string _ifcTypeComponentName;
			string _ifcComponentName;

		public:
			/**
			 * @brief Get the Modeler Component Name object
			 * 
			 * @return string 
			 */
			string getModelerComponentName();
			/**
			 * @brief Set the Modeler Component Name object
			 * 
			 * @param modelerComponentName 
			 */
			void setModelerComponentName(string modelerComponentName);

			/**
			 * @brief Get the Ifc Component Name object
			 * 
			 * @return string 
			 */
			string getIfcComponentName();

			/**
			 * @brief Set the Ifc Component Name object
			 * 
			 * @param ifcComponentName 
			 */
			void setIfcComponentName(string ifcComponentName);

			string getIfcComponentTypeName();
			/**
			 * @brief Set the Ifc Component Type Name object
			 * 
			 * @param ifcComponentTypeName 
			 */
			void setIfcComponentTypeName(string ifcComponentTypeName);
		};
	}
}