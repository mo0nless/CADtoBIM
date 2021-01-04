#pragma once

#include "../../../data_base/mapper/headers/EntitiesMapper.h"
#include "../../../data_base/repositories/headers/ComponentsMappingRepository.h"

class ComponentsMappingService {

private:
	Logs::Logger* _logger;
	ComponentsMappingRepository* _componentsMappingRepository;
	EntitiesMapper* _entitiesMapper;

public:
	ComponentsMappingService(Logs::Logger* logger);

	vector<ComponentsMappingDTO*> getAll();


};