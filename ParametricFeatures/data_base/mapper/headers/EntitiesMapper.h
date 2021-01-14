#pragma once


#include "../../../data_base/models/headers/ComponentsMapping.h"
#include "../../../data_base/dtos/headers/ComponentsMappingDTO.h"

using namespace DataBase::DTOs;
using namespace DataBase::Models;

namespace DataBase
{
	namespace Mapper
	{
		class EntitiesMapper {

		public:
			ComponentsMappingDTO* map(ComponentsMapping* componentsMapping);

			vector<ComponentsMappingDTO*> map(vector<ComponentsMapping*> componentsMappings);
		};
	}
}