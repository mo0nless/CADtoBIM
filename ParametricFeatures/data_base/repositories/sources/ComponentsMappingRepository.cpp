#include "../headers/ComponentsMappingRepository.h"

using namespace DataBase::Repositories;

ComponentsMappingRepository::ComponentsMappingRepository(Logging::Logger * logger)
{
	this->_logger = logger;
}

vector<ComponentsMapping*> ComponentsMappingRepository::getAll()
{
	return DataBaseContext::getDataBaseContext()->getComponentsMappingVector();
}
