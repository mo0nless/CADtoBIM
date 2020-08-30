#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../modeler/primitives/headers/SolidPrimitiveProperties.h"
#include "../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../modeler/primitives/headers/RotationalSweepGraphicProperties.h"
#include "../../../modeler/primitives/headers/ExtrusionGraphicProperties.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"

#include "../../../common/models/headers/SessionManager.h"


class IfcPrimitivesEnhancer {

public:
	void enhance(IfcHierarchyHelper<Ifc4>& file, SolidPrimitiveProperties* solidPrimitiveProperties, IfcElementBundle* ifcElementBundle,
		ElementBundle* elementBundle);
	Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
		ElementBundle* elementBundle);
private:
	

	Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
		ElementBundle* elementBundle);
};