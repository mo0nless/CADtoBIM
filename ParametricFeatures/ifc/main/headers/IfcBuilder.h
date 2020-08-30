#pragma once

#include <ctime>

#include "../../ports/headers/IfcPortsBuilder.h"


#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"


#include "IfcElementBuilder.h"
#include "../../properties/headers/IfcPropertiesEnhancer.h"
#include "../../brep_solids/headers/IfcBRepSolidsEnhancer.h"
#include "../../properties/headers/IfcColorMaterialEnhancer.h"
#include "../../../common/models/headers/SessionManager.h"

class IfcBuilder {
private:
	IfcPrimitivesEnhancer* _ifcPrimitivesEnhancer;
	IfcShapesEnhancer* _ifcShapesEnhancer;
	IfcBRepSolidsEnhancer* _ifcBRepSolidsEnhancer;
	IfcPropertiesEnhancer* _ifcPropertiesEnhancer;
	IfcColorMaterialEnhancer* _IfcColorMaterialEnhancer;
	IfcPortsBuilder* _ifcPortsBuilder;
	
public:
	IfcBuilder();

	void buildIfc(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	
};