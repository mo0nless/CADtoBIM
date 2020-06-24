#pragma once

#include "../../../stdafx.h"
#include "../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../headers/IfcElementBundle.h"
//#include "../../../enhancer/headers/IfcOperationsEnhancer.h"
//#include "../../../modeler/properties/create_solids_operations/reader/headers/CreateSolidsOperationProperties.h"

class IfcCreateSolidsOperationBuilder {

public:
	/*Ifc4::IfcRepresentationItem* buildIfcCreateSolidsOperation(SmartFeatureTreeNode& smartFeatureTreeNode, IfcHierarchyHelper<Ifc4>& file);*/
	static Ifc4::IfcGeometricRepresentationItem* buildIfcCreateSolidsOperation(IfcElementBundle* leftIfcRepresentationItem, IfcElementBundle* rigthIfcRepresentationItem,
		IfcReaderPropertiesBundle& ifcReaderPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);
};