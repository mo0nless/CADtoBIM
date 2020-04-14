#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../modeler/properties/primitives/graphic/headers/SolidPrimitiveProperty.h"
#include "../../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"
#include "../../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"
#include "../../../modeler/properties/primitives/graphic/headers/BoxGraphicProperties.h"
#include "../../../modeler/properties/primitives/graphic/headers/SphereGraphicProperties.h"
#include "../../../modeler/properties/primitives/graphic/headers/TorusGraphicProperties.h"
#include "../../headers/IfcBundle.h"
#include "../../../enhancer/headers/IfcOperationsEnhancer.h"


class IfcPrimitivesEnhancer {

public:
	void enhanceIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties ,IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperty& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
};