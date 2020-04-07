#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../modeler/properties/primitives/graphic/headers/SolidPrimitiveProperty.h"
#include "../../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"
#include "../../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"



class IfcPrimitivesBuilder {

public:
	std::vector<Ifc4::IfcRepresentation*> buildIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties,IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file, DVec3d pointOfPlacement, DVec3d axe1, DVec3d axe2);

};