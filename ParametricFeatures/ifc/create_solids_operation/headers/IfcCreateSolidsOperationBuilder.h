#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"

class IfcCreateSolidsOperationBuilder {

public:
	Ifc4::IfcRepresentationItem* buildIfcProfileDefinition(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);

};