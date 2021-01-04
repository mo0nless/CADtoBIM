#pragma once

#include "../../../stdafx.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../../modeler/text/headers/TextGraphicProperties.h"
#include <vector>

class IfcTextEnhancer
{
public:
	IfcTextEnhancer();
	void enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle*& ifcElementBundle,
		IfcGraphicPropertiesBundle* elementBundle);

private:
	Ifc4::IfcTextLiteralWithExtent* buildTextString(TextGraphicProperties* textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle * elementBundle);
	Logs::Logger* _logger = Logs::Logger::getLogger();
	Ifc4::IfcColourRgb * buildIfcColor(UInt32 color);
	Ifc4::IfcTextStyleTextModel* buildIfcTextStyleTextModel();
	vector<string> buildFamilyFont();
	vector<string> buildFontStyle();
};