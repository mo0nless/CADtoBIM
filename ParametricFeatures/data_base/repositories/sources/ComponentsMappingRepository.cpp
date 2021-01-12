#include "../headers/ComponentsMappingRepository.h"

ComponentsMappingRepository::ComponentsMappingRepository(Logging::Logger * logger)
{
	this->_logger = logger;
}

vector<ComponentsMapping*> ComponentsMappingRepository::getAll()
{
	return DataBaseContext::getDataBaseContext()->getComponentsMappingVector();
}
