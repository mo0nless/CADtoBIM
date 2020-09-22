#pragma once

#include "../../../mapper/entities/headers/EntitiesMapper.h"
#include "../../../repositories/components_mapping/headers/ComponentsMappingRepository.h"

class ComponentsMappingService {

private:
	Logs::Logger* _logger;
	ComponentsMappingRepository* _componentsMappingRepository;
	EntitiesMapper* _entitiesMapper;

public:
	ComponentsMappingService(Logs::Logger* logger);

	vector<ComponentsMappingDTO*> getAll();


};