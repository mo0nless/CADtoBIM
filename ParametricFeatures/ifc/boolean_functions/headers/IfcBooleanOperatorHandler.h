#pragma once

#include"../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../../common/enums/headers/BooleanFunctionsEnum.h"


class IfcBooleanOperatorHandler {


private:
	IfcBooleanOperatorHandler() {};

public:
	static Ifc4::IfcGeometricRepresentationItem* IfcBooleanOperatorHandler::solveBooleanOperation(Ifc4::IfcGeometricRepresentationItem* leftIfcRepresentationItem, Ifc4::IfcGeometricRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle);
};