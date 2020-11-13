#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "../models/headers/ComponentsMapping.h"

class DataBaseContext {

private:
	static DataBaseContext* _dataBaseContext;
	DataBaseContext();
	vector<ComponentsMapping*> _componentsMappingVector;

public:
	static DataBaseContext *getDataBaseContext() {
		if (!_dataBaseContext) {
			_dataBaseContext = new DataBaseContext();
		}

		return _dataBaseContext;
	}
	vector<ComponentsMapping*> getComponentsMappingVector();
};