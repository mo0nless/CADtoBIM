#include "..\headers\EntitiesMapper.h"

ComponentsMappingDTO * EntitiesMapper::map(ComponentsMapping * componentsMapping)
{
	ComponentsMappingDTO* componentsMappingDTO =  new ComponentsMappingDTO();
	componentsMappingDTO->setModelerComponentName(componentsMapping->getModelerComponentName());
	componentsMappingDTO->setIfcComponentName(componentsMapping->getIfcComponentName());
	componentsMappingDTO->setIfcComponentTypeName(componentsMapping->getIfcComponentTypeName());

	return componentsMappingDTO;
}

vector<ComponentsMappingDTO*> EntitiesMapper::map(vector<ComponentsMapping*> componentsMappings)
{

	 vector<ComponentsMappingDTO*> componentsMappingDTOs;
	 for each (ComponentsMapping* componentsMapping in componentsMappings)
	 {
		 if (componentsMapping != nullptr) {
			 componentsMappingDTOs.push_back(map(componentsMapping));
		 }
	 }

	 return componentsMappingDTOs;
}
