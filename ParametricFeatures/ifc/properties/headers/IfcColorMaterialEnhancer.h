#pragma once

#include "../../../stdafx.h"

#include "../../bundle/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

using namespace Ifc::Bundle;

class IfcColorMaterialEnhancer {

public:
	void enhance(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory);

private:
	Logging::Logger* _logger = Logging::Logger::getLogger();
	Ifc4::IfcOwnerHistory* _ownerHistory;
	
	void processColour(IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcColourRgb* buildIfcColor(UInt32 color);
	Ifc4::IfcColourRgb * buildIfcColor(RgbFactor color);

};