#pragma once

#include"../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../../common/enums/headers/BooleanFunctionsEnum.h"

using namespace Ifc::Main;

class IfcBooleanOperatorHandler {


private:
	IfcBooleanOperatorHandler() {};

public:
	static Ifc4::IfcGeometricRepresentationItem* solveBooleanOperation(Ifc4::IfcGeometricRepresentationItem* leftIfcRepresentationItem, Ifc4::IfcGeometricRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle);

};