#pragma once

#include "../../../../stdafx.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../../../modeler/text/headers/TextGraphicProperties.h"
#include <vector>

using namespace Ifc::Bundle;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		class IfcTextEnhancer
		{
		public:
			IfcTextEnhancer();
			void enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

		private:
			Ifc4::IfcTextLiteralWithExtent* buildTextString(TextGraphicProperties* textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle * ifcGraphicPropertiesBundle);
			Logging::Logger* _logger = Logging::Logger::getLogger();
			Ifc4::IfcColourRgb * buildIfcColor(UInt32 color);
			Ifc4::IfcTextStyleTextModel* buildIfcTextStyleTextModel();
			vector<string> buildFamilyFont();
			vector<string> buildFontStyle();
		};
	}
}