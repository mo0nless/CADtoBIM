#pragma once


#include "../../../data_base/models/headers/ComponentsMapping.h"
#include "../../../data_base/dtos/headers/ComponentsMappingDTO.h"

class EntitiesMapper {

public:
	ComponentsMappingDTO* map(ComponentsMapping* componentsMapping);

	vector<ComponentsMappingDTO*> map(vector<ComponentsMapping*> componentsMappings);
 };