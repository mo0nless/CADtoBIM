#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"



class IfcPrimitivesBuilder {

public:
	std::vector<Ifc4::IfcRepresentation*> buildIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties,IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcCsgSolid* buildBasicPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(PrimitiveGraphicProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file, DVec3d pointOfPlacement, DVec3d axe1, DVec3d axe2);

};