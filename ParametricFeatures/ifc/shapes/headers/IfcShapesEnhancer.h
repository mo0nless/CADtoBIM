#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/properties/shapes/headers/CurvesShapesGraphicProperties.h"
#include "../../../enhancer/headers/IfcOperationsEnhancer.h"
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../headers/IfcElementBundle.h"

class IfcShapesEnhancer
{
public:
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationShapes(IShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	void enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
private:	
	Ifc4::IfcCurve* buildIfcCurvesRepresentationItems(ICurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, ShapesTypeEnum curveContainerType, IfcElementBundle*& ifcElementBundle, bool isClosed);

	Ifc4::IfcCurve* buildIfcCurvesSubTypes(IShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(IShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle, bool isClosed);
};

