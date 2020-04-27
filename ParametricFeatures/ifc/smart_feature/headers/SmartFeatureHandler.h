#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../headers/IfcBundle.h"
#include "../../boolean_functions/headers/IfcBooleanOperatorHandler.h"

class SmartFeatureHandler {

public:
	void handleSmartFeature(std::vector<IfcBundle*>& ifcBundleVector);

private:
	Ifc4::IfcRepresentationItem* eval(SmartFeatureTreeNode* root, std::vector<IfcBundle*>& ifcBundleVector, IfcBundle* currentElement);
	IfcBundle* getIfcBundleByGlobalId(std::vector<IfcBundle*>& ifcBundleVector, int globalId);
	IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcBundle& ifcBundle, int localId);
};