#pragma once

#include "../boolean_functions/headers/IfcBooleanOperatorHandler.h"

class IfcBuilder {
private:

public:
	IfcBuilder() {};

	void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

};