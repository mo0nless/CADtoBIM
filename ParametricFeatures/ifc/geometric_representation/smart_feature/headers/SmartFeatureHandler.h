#pragma once

/**
 * @file SmartFeatureHandler.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../bundle/headers/IfcReaderPropertiesBundle.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../solids_operation/headers/IfcSolidsOperationBuilder.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Ifc::GeometricRepresentation;
using namespace Modeler::Properties;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief SmartFeature Handler Class. Process the IfcElementBundle vector to search and build SmartFeature (e.g. Parametric Solid) IFC representation
		 * 
		 * @remark the function is called by the class IfcBuilder before of the creatrion of an IfcElement with IfcElementEnhancer
		 * @see IfcBuilder
		 */
		class SmartFeatureHandler {

		public:
			/**
			 * @brief Parser for the IfcElementBundle vector  
			 * 
			 * @param ifcBundleVector 
			 * @param file 
			 */
			void handleSmartFeature(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

		private:
			/**
			 * @brief Evaluation function of the Smart Feature Tree
			 * 
			 * @param root 
			 * @param ifcBundleVector 
			 * @param currentElement 
			 * @param file 
			 * @return IfcElementBundle* 
			 */
			IfcElementBundle* eval(SmartFeatureTreeNode* root, vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement, IfcHierarchyHelper<Ifc4>& file);
			
			/**
			 * @brief Get the IfcElementBundle By Global Id
			 * 
			 * @param ifcBundleVector 
			 * @param globalId 
			 * @return IfcElementBundle* 
			 */
			IfcElementBundle* getIfcBundleByGlobalId(vector<IfcElementBundle*>& ifcBundleVector, int globalId);

			/**
			 * @brief Get the IfcReaderPropertiesBundle related to the element By Global Id
			 * 
			 * @param ifcBundle 
			 * @param localId 
			 * @return IfcReaderPropertiesBundle* 
			 */
			IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId);
		};
	}
}