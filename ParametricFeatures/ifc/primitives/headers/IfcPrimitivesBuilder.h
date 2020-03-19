#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"


class IfcPrimitivesBuilder {

public:
	//void buildIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector);

	Ifc4::IfcRepresentationItem* buildIfcPrimitive(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcRepresentationItem* buildBasicPrimitive(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcRepresentationItem* buildComplexPrimitive(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file, DVec3d pointOfPlacement, DVec3d axe1, DVec3d axe2);

};