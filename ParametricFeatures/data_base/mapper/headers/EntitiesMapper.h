#pragma once

/**
 * @file EntitiesMapper.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../data_base/models/headers/ComponentsMapping.h"
#include "../../../data_base/dtos/headers/ComponentsMappingDTO.h"

using namespace DataBase::DTOs;
using namespace DataBase::Models;

namespace DataBase
{
	namespace Mapper
	{
		/**
		 * @brief Entities Mapper class 
		 * 
		 * @see  ComponentsMappingDTO ComponentsMapping
		 */
		class EntitiesMapper {

		public:
			/**
			 * @brief Create the ComponentsMapping DTO object from the ComponentsMapping object
			 * 
			 * @param componentsMapping 
			 * @return ComponentsMappingDTO* 
			 */
			ComponentsMappingDTO* map(ComponentsMapping* componentsMapping);

			/**
			 * @brief Create the ComponentsMapping DTO object vector from the ComponentsMapping object vector
			 * 
			 * @param componentsMappings 
			 * @return vector<ComponentsMappingDTO*> 
			 */
			vector<ComponentsMappingDTO*> map(vector<ComponentsMapping*> componentsMappings);
		};
	}
}