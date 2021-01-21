#pragma once

/**
 * @file IfcBuilder.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <ctime>

#include "IfcElementBuilder.h"
#include "../../main/headers/IfcGeneralInformation.h"
#include "../../ports/headers/IfcPortsBuilder.h"

#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../geometric_representation/shapes/headers/IfcShapesEnhancer.h"
#include "../../geometric_representation/surfaces/headers/IfcSurfaceEnhancer.h"
#include "../../geometric_representation/text/headers/IfcTextEnhancer.h"
#include "../../geometric_representation/brep_solids/headers/IfcBRepSolidsEnhancer.h"
#include "../../geometric_representation/primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../geometric_representation/smart_feature/headers/SmartFeatureHandler.h"


#include "../../properties/headers/IfcPropertiesEnhancer.h"
#include "../../properties/headers/IfcColorMaterialEnhancer.h"
#include "../../../common/models/headers/SessionManager.h"


using namespace Common;
using namespace Common::Models;
using namespace Ifc;
using namespace Ifc::Main;
using namespace Ifc::Ports;
using namespace Ifc::Properties;
using namespace Ifc::GeometricRepresentation;
using namespace Modeler::Properties;

namespace Ifc
{
	namespace Main
	{
		/**
		 * @brief Main clas to handle the creation of an Ifc. Parsing the IfcElementBundle and calls to the different geometry builder
		 * 
		 */
		class IfcBuilder {
		private:
			IfcPrimitivesEnhancer* _ifcPrimitivesEnhancer;
			IfcShapesEnhancer* _ifcShapesEnhancer;
			IfcBRepSolidsEnhancer* _ifcBRepSolidsEnhancer;
			IfcPropertiesEnhancer* _ifcPropertiesEnhancer;
			IfcColorMaterialEnhancer* _IfcColorMaterialEnhancer;
			IfcPortsBuilder* _ifcPortsBuilder;
			IfcSurfaceEnhancer* _ifcSurfaceEnhancer;
			IfcElementBuilder* _ifcElementBuilder;
			IfcTextEnhancer* _ifcTextEnhancer;
			SmartFeatureHandler* _smartFeatureHandler;
			map<LevelId, IfcEntityList*> _levelFileEntities;
			vector<LevelHandle> _fileLevelHandle;
			Utilities::DialogCompletionBar* _progressBar;

			mutable boost::shared_mutex _mutex;
			Logging::Logger* _logger = Logging::Logger::getLogger();
			
			/**
			 * @brief Get the Level File Cache related to the current Bentley DGN file object
			 * 
			 * @return map<LevelId, IfcEntityList*> 
			 */
			map<LevelId, IfcEntityList*> getLevelFileCache();	

			/**
			 * @brief Generate and write on the Ifc file the Levels File Cache
			 * 
			 * @param file 
			 */
			void generateIfcLevelsCache(IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Split a vector in N sub vectors
			 * 
			 * @tparam ValueType 
			 * @param vec the vector to split
			 * @param n number of split
			 * @return vector<vector<ValueType>> 
			 */
			template<typename ValueType>
			vector<vector<ValueType>> splitVector(const std::vector<ValueType>& vec, size_t n);

			/**
			 * @brief Process each IfcElementBundle and build the correct geometry associated to the element
			 * 
			 * @param ifcElementBundleVector 
			 * @param file 
			 */
			void processElementVector(vector<IfcElementBundle*> ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file);
		public:
			IfcBuilder();
			
			/**
			 * @brief Method to start building the Ifc File with the IfcElementBundle vector
			 * 
			 * @param ifcElementBundleVector 
			 */
			void buildIfc(vector<IfcElementBundle*>& ifcElementBundleVector);

		};
	}
}

template<typename ValueType>
vector<vector<ValueType>> Ifc::Main::IfcBuilder::splitVector(const vector<ValueType>& vec, size_t n)
{
	vector<vector<ValueType>> outVec;

	size_t length = vec.size() / n;
	size_t remain = vec.size() % n;

	size_t begin = 0;
	size_t end = 0;

	for (size_t i = 0; i < min(n, vec.size()); ++i)
	{
		end += (remain > 0) ? (length + !!(remain--)) : length;

		outVec.push_back(vector<ValueType>(vec.begin() + begin, vec.begin() + end));

		begin = end;
	}

	return outVec;
}