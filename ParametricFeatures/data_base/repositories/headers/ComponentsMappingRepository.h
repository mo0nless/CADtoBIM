#pragma once

/**
 * @file ComponentsMappingRepository.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../data_base/headers/DataBaseContext.h"
#include "../../../logging/headers/Logger.h"

using namespace DataBase;

namespace DataBase
{
	namespace Repositories
	{
		/**
		 * @brief Class as repository to handle the ComponentMapping 
		 * 
		 */
		class ComponentsMappingRepository {

		private:
			Logging::Logger* _logger;

		public:
			ComponentsMappingRepository(Logging::Logger* logger);

			/**
			 * @brief Get All ComponentsMapping objects vector
			 * 
			 * @return vector<ComponentsMapping*> 
			 */
			vector<ComponentsMapping*> getAll();

		};
	}
}