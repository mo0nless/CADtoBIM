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
	void enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationShapes(ShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
private:	
	Ifc4::IfcCurve* buildIfcCurve(CurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, ShapesTypeEnum curveContainerType, IfcElementBundle*& ifcElementBundle, bool isClosed);		
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle, bool isClosed);
	Ifc4::IfcCurve* ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	Ifc4::IfcBoundaryCurve* buildIfcBoundaryCurve(ShapesGraphicProperties * curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	void defineIfcGeometricRepresentationItem(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);

	Ifc4::IfcGeometricRepresentationItem* geomItem = nullptr;
};

