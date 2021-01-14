#pragma once

#include "../../../data_base/mapper/headers/EntitiesMapper.h"
#include "../../../data_base/repositories/headers/ComponentsMappingRepository.h"

using namespace DataBase::Mapper;
using namespace DataBase::Repositories;


namespace DataBase
{
	namespace Services
	{
		class ComponentsMappingService {

		private:
			Logging::Logger* _logger;
			ComponentsMappingRepository* _componentsMappingRepository;
			EntitiesMapper* _entitiesMapper;

		public:
			ComponentsMappingService(Logging::Logger* logger);

			vector<ComponentsMappingDTO*> getAll();


		};
	}
}