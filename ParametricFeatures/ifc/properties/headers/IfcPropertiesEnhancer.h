#pragma once

/**
 * @file IfcPropertiesEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"

#include "../../bundle/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;

namespace Ifc
{
	namespace Properties
	{
		/**
		 * @brief Ifc Property Class Enhancer. Process the properties of all the IfcElementBundle and generate the IfcPropertySet
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcPropertiesEnhancer {

		public:
			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param ifcElementBundleVector 
			 * @param file 
			 * @param ownerHistory 
			 */
			void enhance(vector<IfcElementBundle*>& ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			Ifc4::IfcOwnerHistory* _ownerHistory;

			/**
			 * @brief Create a Ifc Property Set object
			 * 
			 * @param readerPropertiesBundle 
			 * @param file 
			 * @return Ifc4::IfcPropertySet* 
			 */
			Ifc4::IfcPropertySet* createIfcPropertySet(IfcReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Create a Ifc Basic Property object
			 * 
			 * @param readerPropertyDefinition 
			 * @return Ifc4::IfcProperty* 
			 */
			Ifc4::IfcProperty* createIfcBasicProperty(ReaderPropertyDefinition& readerPropertyDefinition);

			/**
			 * @brief Create a Ifc Complex Property object
			 * 
			 * @param readerPropertyDefinition 
			 * @return Ifc4::IfcProperty* 
			 */
			Ifc4::IfcProperty* createIfcComplexProperty(ReaderPropertyDefinition& readerPropertyDefinition);
		};
	}
}