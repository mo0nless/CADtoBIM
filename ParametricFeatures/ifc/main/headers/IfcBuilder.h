#pragma once

#include <ctime>
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
//#include "../create_solids_operation/headers/IfcCreateSolidsOperationBuilder.h"
//#include "../../enhancer/headers/IfcOperationsHelper.h"
#include "IfcElementBuilder.h"
#include "IfcPortsBuilder.h"
#include "../../properties/headers/IfcPropertiesEnhancer.h"
#include "../../brep_solids/headers/IfcBRepSolidsEnhancer.h"
#include "../../properties/headers/IfcColorEnhancer.h"
#include "../../../common/models/headers/SessionManager.h"

class IfcBuilder {
private:
	
public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	
};