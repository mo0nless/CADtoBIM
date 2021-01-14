#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>

#include "../models/headers/ComponentsMapping.h"
#include "../../logging/headers/Logger.h"
#include "../../common/models/headers/SessionManager.h"

using namespace Common::Models;
using namespace DataBase::Models;

namespace DataBase
{
	class DataBaseContext {

	private:
		static DataBaseContext* _dataBaseContext;
		DataBaseContext();
		vector<ComponentsMapping*> _componentsMappingVector;
		Logging::Logger* _logger;
	public:
		static DataBaseContext *getDataBaseContext() {
			if (!_dataBaseContext) {
				_dataBaseContext = new DataBaseContext();
			}

			return _dataBaseContext;
		}
		vector<ComponentsMapping*> getComponentsMappingVector();
	};
}