#pragma once

#include "../../../data_base/headers/DataBaseContext.h"
#include "../../../logging/headers/Logger.h"

class ComponentsMappingRepository {

private:
	Logs::Logger* _logger;

public:
	ComponentsMappingRepository(Logs::Logger* logger);

	vector<ComponentsMapping*> getAll();

};