#pragma once

#include "../../../../stdafx.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../../../common/enums/headers/BooleanFunctionsEnum.h"
#include "../../../../data_processing/modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../../bundle/headers/IfcElementBundle.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Common::Enums;
using namespace Common;

class IfcSolidsOperationBuilder {

public:
	static Ifc4::IfcGeometricRepresentationItem* buildIfcCreateSolidsOperation(IfcElementBundle* leftIfcRepresentationItem, IfcElementBundle* rigthIfcRepresentationItem,
		IfcReaderPropertiesBundle& ifcReaderPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

	static Ifc4::IfcGeometricRepresentationItem* solveBooleanOperation(Ifc4::IfcGeometricRepresentationItem* leftIfcRepresentationItem, 
		Ifc4::IfcGeometricRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle);
};