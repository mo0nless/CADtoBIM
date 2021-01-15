#pragma once

/**
 * @file ComponentsMappingDTO.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <vector>

using namespace std;

namespace DataBase
{
	namespace DTOs
	{
		/**
		 * @brief Data Transfer Object Class for the components
		 * 
		 * @see EntitiesMapper ComponentMappingService
		 */
		class ComponentsMappingDTO {
		private:
			int _id;

			string _modelerComponentName;
			string _ifcComponentName;
			string _ifcTypeComponentName;

		public:
			ComponentsMappingDTO();

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

			/**
			 * @brief Get the Ifc Component Type Name object
			 * 
			 * @return string 
			 */
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