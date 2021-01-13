#pragma once

#include "../../../stdafx.h"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../data_processing/modeler/primitives/headers/SolidPrimitiveProperties.h"
#include "../../../data_processing/modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/RotationalSweepGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../data_processing/modeler/primitives/headers/ExtrusionGraphicProperties.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"

#include "../../../common/models/headers/SessionManager.h"

using namespace Ifc::Bundle;

class IfcPrimitivesEnhancer {

public:
	void enhance(IfcHierarchyHelper<Ifc4>& file, SolidPrimitiveProperties* solidPrimitiveProperties, IfcElementBundle* ifcElementBundle,
		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
	Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
private:
	Logging::Logger* _logger = Logging::Logger::getLogger();

	mutable boost::shared_mutex _mutex;

	Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
};