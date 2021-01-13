#pragma once

#include <ctime>

#include "IfcElementBuilder.h"

#include "../../main/headers/IfcGeneralInformation.h"
#include "../../ports/headers/IfcPortsBuilder.h"


#include "../../../data_processing/modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
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

namespace Ifc
{
	namespace Main
	{
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
			map<LevelId, IfcEntityList*> getLevelFileCache();

			void generateIfcLevelsCache(IfcHierarchyHelper<Ifc4>& file);
			Utilities::DialogCompletionBar* _progressBar;

			mutable boost::shared_mutex _mutex;
			Logging::Logger* _logger = Logging::Logger::getLogger();

			template<typename ValueType>
			vector<vector<ValueType>> splitVector(const std::vector<ValueType>& vec, size_t n);

			void processElementVector(vector<IfcElementBundle*> ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file);
		public:
			IfcBuilder();

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