#pragma once

/**
 * @file IfcReaderPropertiesBundle.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<vector>
#include "../../../stdafx.h"
#include "../../../modeler/properties/reader/headers/ReaderPropertyDefinition.h"

using namespace std;
using namespace Modeler::Properties;

namespace Ifc
{
	namespace Bundle
	{
		/**
		 * @brief Ifc Reader Property bundle class that contains all the NOT graphic information of an Element:
		 * IfcPropertySet, Reader Properties, Name, Class, IDs, etc..
		 * 
		 */
		class IfcReaderPropertiesBundle {

		private:
			string className;
			int localId;
			string _name;
			vector<ReaderPropertyDefinition*> properties;
			Ifc4::IfcPropertySet* ifcPropertySet;

		public:
			/**
			 * @brief Construct a new Ifc Reader Properties Bundle object
			 * 
			 * @param newClassName Class Name of the Element 
			 * @param newLocalId the local ID of the Element
			 */
			IfcReaderPropertiesBundle(string newClassName, int newLocalId);

			/**
			 * @brief Get the Element Class Name object
			 * 
			 * @return string 
			 */
			string getClassName();

			/**
			 * @brief Get the Element Local Id object 
			 * 
			 * @return int 
			 */
			int getLocalId();

			/**
			 * @brief Set the Element Local Id object
			 * 
			 * @param newLocalId 
			 */
			void setLocalId(int newLocalId);

			/**
			 * @brief Get the Element Property Name object
			 * 
			 * @return string 
			 */
			string getName();

			/**
			 * @brief Set the Element Property Name object
			 * 
			 * @param name 
			 */
			void setName(string name);

			/**
			 * @brief Get the Element Property definitions
			 * 
			 * @return vector<ReaderPropertyDefinition*> set of all definitions
			 */
			vector<ReaderPropertyDefinition*> getPropertiesDefinitions();

			/**
			 * @brief Add a definitions to the Element Property 
			 * 
			 * @param readerPropertyDefinition the definition
			 */
			void addPropertyDefinition(ReaderPropertyDefinition* readerPropertyDefinition);

			/**
			 * @brief Set the Ifc Property Set object
			 * 
			 * @param ifcPropertySetValue 
			 */
			void setIfcPropertySet(Ifc4::IfcPropertySet* ifcPropertySetValue);

			/**
			 * @brief Get the Ifc Property Set object
			 * 
			 * @return Ifc4::IfcPropertySet* 
			 */
			Ifc4::IfcPropertySet* getIfcPropertySet();

		};
	}
}