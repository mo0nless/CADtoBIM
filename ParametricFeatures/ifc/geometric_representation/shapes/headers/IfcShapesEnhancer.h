#pragma once

#include "../../../../stdafx.h"

#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../../../data_processing/modeler/shapes/headers/ShapesGraphicProperties.h"
#include "../../../../data_processing/modeler/curves/headers/CurveGraphicProperties.h"
#include "../../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../../../common/enums/headers/ShapesTypeEnum.h"
#include <vector>

using namespace Ifc::Bundle;
using namespace Common::Enums;
using namespace Common::Utilities;

struct BoundTypeIfcCurve 
{
	CurvesBoundaryTypeEnum boundary;
	Ifc4::IfcCurve* ifcCurve;
	vector<Ifc4::IfcCurve*> vecIfcCurves;
	vector<CurveGraphicProperties*> vecPrimitivesCurves;
	bool isClosed = false; 
	DPoint3d start, end;
};

class IfcShapesEnhancer
{
public:
	IfcShapesEnhancer();
	void enhance(IfcHierarchyHelper<Ifc4>& file, ShapesGraphicProperties* shapeGraphicProperties,  IfcElementBundle*& ifcElementBundle,
		IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle,bool addToIfcElementBundle = true);
	
	bool hasSingleShapeItem();
	Ifc4::IfcGeometricRepresentationItem* getSingleShapeRepresentation();
	vector<BoundTypeIfcCurve*> getCurvesShapeRepresentationVector();

	IfcDimensionEnum dimension = IfcDimensionEnum::dim_3D;
	bool uvCoordsParse = false;

private:
	Logging::Logger* _logger = Logging::Logger::getLogger();
	
	Ifc4::IfcCurve* buildIfcCurvePrimitives(CurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(vector<Ifc4::IfcCurve*> curveVector);
	vector<Ifc4::IfcCurve*> ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
	
	Ifc4::IfcGeometricRepresentationItem* mSingleShapeRepresentation;
	vector<BoundTypeIfcCurve*> mShapeBoundTypeCurvesVector;
	bool mHasSingleShape;

	mutable boost::shared_mutex _mutex;
};

