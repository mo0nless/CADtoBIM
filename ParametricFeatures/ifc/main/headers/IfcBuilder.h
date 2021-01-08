#pragma once

#include <ctime>

#include "../../general_information/headers/IfcGeneralInformation.h"
#include "../../ports/headers/IfcPortsBuilder.h"


#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../surfaces/headers/IfcSurfaceEnhancer.h"
#include "../../text/headers/IfcTextEnhancer.h"


#include "IfcElementBuilder.h"
#include "../../properties/headers/IfcPropertiesEnhancer.h"
#include "../../brep_solids/headers/IfcBRepSolidsEnhancer.h"
#include "../../properties/headers/IfcColorMaterialEnhancer.h"
#include "../../../common/models/headers/SessionManager.h"

#include "../../smart_feature/headers/SmartFeatureHandler.h"

using namespace Common;

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
	Logs::Logger* _logger = Logs::Logger::getLogger();

	template<typename ValueType>
	vector<vector<ValueType>> splitVector(const std::vector<ValueType>& vec, size_t n);
	
	void processElementVector(vector<IfcElementBundle*> ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file);
public:
	IfcBuilder();

	void buildIfc(vector<IfcElementBundle*>& ifcElementBundleVector);
	
};


template<typename ValueType>
vector<vector<ValueType>> IfcBuilder::splitVector(const vector<ValueType>& vec, size_t n)
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