#pragma once

#include "../boolean_functions/headers/IfcBooleanOperatorHandler.h"
#include "../shapes/headers/IfcShapesEnhancer.h"
#include "../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"
#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "IfcElementBuilder.h"
#include "IfcPortsBuilder.h"

class IfcBuilder {
private:
	void buildIfcReletionshipConnectionPorts(std::vector<IfcElementBundle*>ifcRelBundleVector, IfcHierarchyHelper<Ifc4>& file);
public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	
};