#pragma once

#include "../../../../data_processing/modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../bundle/headers/IfcReaderPropertiesBundle.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../solids_operation/headers/IfcSolidsOperationBuilder.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Ifc::GeometricRepresentation;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		class SmartFeatureHandler {

		public:
			void handleSmartFeature(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

		private:
			IfcElementBundle* eval(SmartFeatureTreeNode* root, vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement, IfcHierarchyHelper<Ifc4>& file);
			IfcElementBundle* getIfcBundleByGlobalId(vector<IfcElementBundle*>& ifcBundleVector, int globalId);
			IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId);
		};
	}
}