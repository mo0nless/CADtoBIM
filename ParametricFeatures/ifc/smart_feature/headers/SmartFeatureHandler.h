#pragma once

//#include "../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
//#include "../../headers/IfcElementBundle.h"
#include "../../boolean_functions/headers/IfcBooleanOperatorHandler.h"

class SmartFeatureHandler {

public:
	void handleSmartFeature(std::vector<IfcElementBundle*>& ifcBundleVector);

private:
	Ifc4::IfcGeometricRepresentationItem* eval(SmartFeatureTreeNode* root, std::vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement);
	IfcElementBundle* getIfcBundleByGlobalId(std::vector<IfcElementBundle*>& ifcBundleVector, int globalId);
	IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId);
};