#pragma once

#include "../../../stdafx.h"

#include "../../main/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

class IfcColorMaterialEnhancer {

public:
	void enhance(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory);

private:
	Logs::Logger* _logger = Logs::Logger::getLogger();
	Ifc4::IfcOwnerHistory* _ownerHistory;
	
	void processColour(IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcColourRgb* buildIfcColor(UInt32 color);
	Ifc4::IfcColourRgb * buildIfcColor(RgbFactor color);

};