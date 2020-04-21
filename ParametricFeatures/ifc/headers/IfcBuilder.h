#pragma once

#include "../boolean_functions/headers/IfcBooleanOperatorHandler.h"
#include "../shapes/headers/IfcShapesEnhancer.h"
#include "../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"
#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../properties/headers/IfcPropertiesEnhancer.h"
#include "../properties/headers/IfcMaterialEnhancer.h"

class IfcBuilder {
private:
	void buildIfcDistributionElem(IfcBundle*& ifcBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file);
	void buildIfcReletionshipConnectionPorts(std::vector<IfcBundle*>ifcRelBundleVector, IfcHierarchyHelper<Ifc4>& file);
public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	
};