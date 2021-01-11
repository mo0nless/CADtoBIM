#pragma once

#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../ifc/main/headers/IfcReaderPropertiesBundle.h"
#include "../../boolean_functions/headers/IfcBooleanOperatorHandler.h"
#include "../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"

using namespace Ifc::Main;

class SmartFeatureHandler {

public:
	void handleSmartFeature(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	IfcElementBundle* eval(SmartFeatureTreeNode* root, vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement,IfcHierarchyHelper<Ifc4>& file);
	IfcElementBundle* getIfcBundleByGlobalId(vector<IfcElementBundle*>& ifcBundleVector, int globalId);
	IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId);
};