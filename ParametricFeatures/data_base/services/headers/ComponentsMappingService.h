#pragma once

/**
 * @file ComponentsMappingService.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../data_base/mapper/headers/EntitiesMapper.h"
#include "../../../data_base/repositories/headers/ComponentsMappingRepository.h"

using namespace DataBase::Mapper;
using namespace DataBase::Repositories;


namespace DataBase
{
	namespace Services
	{
		/**
		 * @brief Class as repository to handle the ComponentMapping DTO
		 * 
		 */
		class ComponentsMappingService {

		private:
			Logging::Logger* _logger;
			ComponentsMappingRepository* _componentsMappingRepository;
			EntitiesMapper* _entitiesMapper;

		public:
			ComponentsMappingService(Logging::Logger* logger);

			/**
			 * @brief Get All ComponentsMapping DTO objects vector
			 * 
			 * @return vector<ComponentsMappingDTO*> 
			 */
			vector<ComponentsMappingDTO*> getAll();


		};
	}
}