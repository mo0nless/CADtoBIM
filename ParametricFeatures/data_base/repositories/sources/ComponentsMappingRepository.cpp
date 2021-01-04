#include "../headers/ComponentsMappingRepository.h"

ComponentsMappingRepository::ComponentsMappingRepository(Logs::Logger * logger)
{
	this->_logger = logger;
}

vector<ComponentsMapping*> ComponentsMappingRepository::getAll()
{
	return DataBaseContext::getDataBaseContext()->getComponentsMappingVector();
}
