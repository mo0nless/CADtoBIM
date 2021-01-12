#include "..\headers\ComponentsMappingService.h"

ComponentsMappingService::ComponentsMappingService(Logging::Logger * logger)
{
	this->_logger = logger;
	this->_componentsMappingRepository = new ComponentsMappingRepository(logger);
	this->_entitiesMapper = new EntitiesMapper();
}

vector<ComponentsMappingDTO*> ComponentsMappingService::getAll()
{
	return this->_entitiesMapper->map(this->_componentsMappingRepository->getAll());
}
