#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../headers/IfcElementBundle.h"
#include "../../boolean_functions/headers/IfcBooleanOperatorHandler.h"
#include "../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"


class SmartFeatureHandler {

public:
	void handleSmartFeature(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	IfcElementBundle* eval(SmartFeatureTreeNode* root, std::vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement,IfcHierarchyHelper<Ifc4>& file);
	IfcElementBundle* getIfcBundleByGlobalId(std::vector<IfcElementBundle*>& ifcBundleVector, int globalId);
	IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId);
};