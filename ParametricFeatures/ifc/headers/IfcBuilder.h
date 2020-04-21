#pragma once

#include "../boolean_functions/headers/IfcBooleanOperatorHandler.h"
#include "../curves/headers/IfcShapesEnhancer.h"
#include "../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"
#include "../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../properties/headers/IfcPropertiesEnhancer.h"
#include "../properties/headers/IfcMaterialEnhancer.h"

class IfcBuilder {
private:

public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

};