#pragma once

#include "../smart_feature/headers/SmartFeatureHandler.h"
//#include "../shapes/headers/IfcShapesEnhancer.h"
#include "../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"
//#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "IfcElementBuilder.h"
#include "IfcPortsBuilder.h"
#include "../properties/headers/IfcPropertiesEnhancer.h"
#include "../properties/headers/IfcMaterialEnhancer.h"
#include "../brep_solids/headers/IfcBRepSolidsEnhancer.h"

class IfcBuilder {
private:
	
public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	
};