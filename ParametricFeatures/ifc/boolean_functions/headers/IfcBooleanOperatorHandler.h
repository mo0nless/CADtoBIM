#pragma once

#include"../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../../common/enums/headers/BooleanFunctionsEnum.h"


class IfcBooleanOperatorHandler {


private:
	IfcBooleanOperatorHandler() {};

public:
	static Ifc4::IfcRepresentationItem* IfcBooleanOperatorHandler::solveBooleanOperaiont(Ifc4::IfcRepresentationItem* leftIfcRepresentationItem, Ifc4::IfcRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle);
};