#pragma once

//include "../../stdafx.h"
#include "../boolean_functions/headers/IfcBooleanOperatorHandler.h"

class IfcBuilder {
private:
	//IfcHierarchyHelper<Ifc4>* file = nullptr;

public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector,SmartFeatureContainer& smartFeatureContainer);

};