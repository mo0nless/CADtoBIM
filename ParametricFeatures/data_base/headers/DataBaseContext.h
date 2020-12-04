#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "../models/headers/ComponentsMapping.h"
#include "../../logging/headers/Logger.h"

class DataBaseContext {

private:
	static DataBaseContext* _dataBaseContext;
	DataBaseContext();
	vector<ComponentsMapping*> _componentsMappingVector;
	Logs::Logger* _logger;
public:
	static DataBaseContext *getDataBaseContext() {
		if (!_dataBaseContext) {
			_dataBaseContext = new DataBaseContext();
		}

		return _dataBaseContext;
	}
	vector<ComponentsMapping*> getComponentsMappingVector();
};