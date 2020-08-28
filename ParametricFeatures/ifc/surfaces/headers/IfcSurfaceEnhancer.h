#pragma once

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
#include "../../../modeler/brep_solids/headers/MSBsplineSurfaceGraphicProperties.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"


using namespace std;

class IfcSurfaceEnhancer 
{

public:
	void enhanceIfcSurface(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

	Ifc4::IfcGeometricRepresentationItem* buildIfcSurface(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file, ElementBundle* elementBundle);
private:

	Ifc4::IfcSurface* buildIfcElementarySurface(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcSurface* buildBoundedSurface(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
		ElementBundle* elementBundle);
};