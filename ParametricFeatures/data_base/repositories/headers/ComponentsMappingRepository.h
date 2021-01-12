#pragma once

#include "../../../data_base/headers/DataBaseContext.h"
#include "../../../logging/headers/Logger.h"

class ComponentsMappingRepository {

private:
	Logging::Logger* _logger;

public:
	ComponentsMappingRepository(Logging::Logger* logger);

	vector<ComponentsMapping*> getAll();

};