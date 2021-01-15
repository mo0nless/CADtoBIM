#pragma once

/**
 * @file DataBaseContext.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
	/**
	 * @brief Class to handle the Database setup and Context
	 * 
	 */
	class DataBaseContext {

	private:
		static DataBaseContext* _dataBaseContext;
		DataBaseContext();
		vector<ComponentsMapping*> _componentsMappingVector;
		Logging::Logger* _logger;
	public:
		/**
		 * @brief Get the Data Base Context object
		 * 
		 * @return DataBaseContext* 
		 */
		static DataBaseContext *getDataBaseContext() {
			if (!_dataBaseContext) {
				_dataBaseContext = new DataBaseContext();
			}

			return _dataBaseContext;
		}

		/**
		 * @brief Get the Components Mapping Vector object
		 * 
		 * @return vector<ComponentsMapping*> 
		 */
		vector<ComponentsMapping*> getComponentsMappingVector();
	};
}