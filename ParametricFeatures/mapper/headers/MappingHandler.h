#pragma once

#include "../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../modeler/properties/headers/DictionaryProperties.h"

class MappingHandler {


public:
	static void mapDictoinaryPropertiesToSmartFeaureContainer(SmartFeatureContainer& smartFeatureContainer, std::vector<DictionaryProperties>& dictionaryProperties);


};