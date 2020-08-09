#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

class IfcColorEnhancer {

public:
	void enhanceColors(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	void processColour(IfcElementBundle& ifcElementBundle, IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcColourRgb* buildIfcColor(UInt32 color);


};