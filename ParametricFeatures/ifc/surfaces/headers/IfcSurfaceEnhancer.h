#pragma once

#pragma once

#include "../../../stdafx.h"

#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../modeler/primitives/headers/SolidPrimitiveProperties.h"
#include "../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../modeler/brep_solids/headers/MSBsplineSurfaceGraphicProperties.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"


using namespace std;
using namespace Ifc::Bundle;

class IfcSurfaceEnhancer 
{

public:
	void enhance(IfcHierarchyHelper<Ifc4>& file, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, IfcElementBundle*& ifcElementBundle,
		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, bool addToIfcElementBundle = true);

	Ifc4::IfcBSplineSurface* buildIfcSurface(MSBsplineSurfaceGraphicProperties& msBsplineSurfaceGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
private:
	Logging::Logger* _logger = Logging::Logger::getLogger();

	mutable boost::shared_mutex _mutex;
};