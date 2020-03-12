#pragma once

#include"../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesBuilder.h"


class IfcBooleanOperatorHandler {
private:

public:
	IfcBooleanOperatorHandler() {};
	Ifc4::IfcRepresentationItem* buildBooleanRepresentation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcRepresentationItem* solveBooleanOperaionts(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file);
};