#pragma once

#include "../../../stdafx.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h" //curveshape..
//#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
//#include "../../brep_solids/headers/IfcBRepRelationship.h"
#include <vector>

struct BoundTypeIfcCurve 
{
	CurvesBoundaryTypeEnum boundary;
	Ifc4::IfcCurve* ifcCurve;
	std::vector<Ifc4::IfcCurve*> vecIfcCurves;
	std::vector<CurveGraphicProperties*> vecPrimitivesCurves;
	bool isClosed = false; 
	DPoint3d start, end;
};

class IfcShapesEnhancer
{
public:
	IfcShapesEnhancer();
	void enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);	
	void buildGeometricRepresentationShapes(ShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle,
		ElementBundle* elementBundle,bool addToIfcElementBundle = true);
	
	bool hasSingleShapeItem();
	Ifc4::IfcGeometricRepresentationItem* getSingleShapeRepresentation();
	std::vector<BoundTypeIfcCurve*> getCurvesShapeRepresentationVector();

	IfcDimensionEnum dimension = IfcDimensionEnum::dim_3D;
	bool uvCoordsParse = false;

private:
	Ifc4::IfcCurve* buildIfcCurvePrimitives(CurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(std::vector<Ifc4::IfcCurve*> curveVector);
	std::vector<Ifc4::IfcCurve*> ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	
	Ifc4::IfcGeometricRepresentationItem* mSingleShapeRepresentation;
	std::vector<BoundTypeIfcCurve*> mShapeBoundTypeCurvesVector;
	bool mHasSingleShape;

};

