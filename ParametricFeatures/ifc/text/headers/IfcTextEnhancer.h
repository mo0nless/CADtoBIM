#pragma once

#include "../../../stdafx.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/text/headers/TextGraphicProperties.h"
#include <vector>

class IfcTextEnhancer
{
public:
	IfcTextEnhancer();
	void enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle*& ifcElementBundle,
		GraphicGeomBundle* elementBundle);

private:
	Ifc4::IfcTextLiteralWithExtent* buildTextString(TextGraphicProperties* textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, GraphicGeomBundle * elementBundle);
	Logs::Logger* _logger = Logs::Logger::getLogger();
	
};