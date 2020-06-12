#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/properties/shapes/headers/ShapesGraphicProperties.h" //curveshape..
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../brep_solids/headers/IfcBRepRelationship.h"
#include <vector>

typedef std::tuple<CurvesBoundaryTypeEnum, std::vector<Ifc4::IfcCurve*>> BoundTypeCurvesVector;

class IfcShapesEnhancer
{
public:	
	void enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);	
	void buildGeometricRepresentationShapes(ShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle, bool addToIfcElementBundle = true);
	
	bool hasSingleShapeItem();
	Ifc4::IfcGeometricRepresentationItem* getSingleShapeRepresentation();
	std::vector<BoundTypeCurvesVector> getCurvesShapeRepresentationVector();

private:
	Ifc4::IfcCurve* buildIfcCurvePrimitives(CurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle, bool isClosed);
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(std::vector<Ifc4::IfcCurve*> curveVector);
	std::vector<Ifc4::IfcCurve*> ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	
	Ifc4::IfcGeometricRepresentationItem* mSingleShapeRepresentation = nullptr;
	std::vector<BoundTypeCurvesVector> mShapeBoundTypeCurvesVector;
	bool mHasSingleShape = false;
};

