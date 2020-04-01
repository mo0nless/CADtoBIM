#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"


class IfcPrimitivesBuilder {

public:
	Ifc4::IfcRepresentationItem* buildIfcPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, std::vector<ReaderPropertyBundle*> readerPropertiesVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcRepresentationItem* buildBasicPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, std::vector<ReaderPropertyBundle*> readerPropertiesVector, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcRepresentationItem* buildComplexPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file, DVec3d pointOfPlacement, DVec3d axe1, DVec3d axe2);

};