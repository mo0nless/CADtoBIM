#include "../headers/IfcShapesEnhancer.h"

//IFC SPECS [SB] More information on shape representation are given by the IfcShapeRepresentation 
Ifc4::IfcGeometricRepresentationItem* IfcShapesEnhancer::buildGeometricRepresentationShapes(ShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle)
{
	Ifc4::IfcGeometricRepresentationItem* geometricRepItem = nullptr;

	bool isElementSmartSolid = ifcElementBundle->getIsSmartSolid();

	//TODO [SB] Handle the boundary type for solids
	switch (shapeGraphicProperties->getBoundaryTypeCurvesContainer())
	{
		//All curves drawed as single are open (Line string inside pipes)
		//Curves should join head to tail in a single path. The path is not expected to be closed. 
		case CurvesBoundaryTypeEnum::OPEN:
		{
			std::vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);

			if (shapeGraphicProperties->getHasSingleCurve())
			{
				geometricRepItem = curveVector[0];
			}
			else //Complex Chain 
			{
				IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				Ifc4::IfcCompositeCurve* item = new Ifc4::IfcCompositeCurve(complexChain, false);
				
				geometricRepItem = item;
			}
		}
		break;

		//This defines the OUTER boundaries of an entity (Solid/Surface) eg Smart Solid shape
		//Curves should join head to tail in a single closed path; this area expected to be an outer (or only) loop
		case CurvesBoundaryTypeEnum::OUTER:
		{
			std::vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);

			//check if they belongs to a smart solid
			if (isElementSmartSolid && !shapeGraphicProperties->getFacesBoundIDs().empty())
			{
				/*IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				Ifc4::IfcOuterBoundaryCurve* outerBoundaryCurve = new Ifc4::IfcOuterBoundaryCurve(complexChain,false);*/

				//bRepRelationship->processBRepEntityEdge(shapeGraphicProperties, outerBoundaryCurve, (int)CurvesBoundaryTypeEnum::OUTER);
				bRepRelationship->processBRepEntityEdge(shapeGraphicProperties, curveVector, (int)CurvesBoundaryTypeEnum::OUTER);
				
			}
			else 
			{
				geometricRepItem = curveVector[0];
			}
		}
		break;

		//This defines the INNER boundaries of an entity (Solid/Surface) eg Hole
		//Curves should join head to tail in a single closed path; this area is expected to be an inner loop.
		case CurvesBoundaryTypeEnum::INNER:
		{			
			std::vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);

			//check if they belongs to a smart solid
			if (isElementSmartSolid && (!shapeGraphicProperties->getFacesBoundIDs().empty()))
			{
				/*IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				Ifc4::IfcBoundaryCurve* innerBoundaryCurve = new Ifc4::IfcBoundaryCurve(complexChain, false);*/
				
				//bRepRelationship->processBRepEntityEdge(shapeGraphicProperties, innerBoundaryCurve, (int)CurvesBoundaryTypeEnum::INNER);
				bRepRelationship->processBRepEntityEdge(shapeGraphicProperties, curveVector, (int)CurvesBoundaryTypeEnum::INNER);
				
			}
			else
			{
				geometricRepItem = curveVector[0];
			}
		}
		break;

		//Set of Bounday Data which could include (OUTER, INNER boundaries)
		//Expected to contain (only) multiple CurveVectors, all of which are either BOUNDARY_TYPE_Open or BOUNDARY_TYPE_inner.
		case CurvesBoundaryTypeEnum::PARITY_REGION:
		{			
			if (shapeGraphicProperties->hasShapesGraphicsContainer())
			{
				for (auto shape : shapeGraphicProperties->getShapesGraphicsContainer())
				{
					geometricRepItem = buildGeometricRepresentationShapes(shape, file, ifcElementBundle);
				}
			}
		}
		break;

		//Expected to contain (only) multiple CurveVectors, all of which have area. 
		//(No individual curves or open paths).These are to be analyzed by union rules.
		case CurvesBoundaryTypeEnum::UNION_REGION:
		{
			if (shapeGraphicProperties->hasShapesGraphicsContainer())
			{
				for (auto shape : shapeGraphicProperties->getShapesGraphicsContainer())
				{
					geometricRepItem = buildGeometricRepresentationShapes(shape, file, ifcElementBundle);
				}
			}
		}

		//Point and ports have no Boundary
		//no specific properties expected for contained curves or points. 
		case CurvesBoundaryTypeEnum::NONE_BOUNDARY:
		{
			std::vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);
			geometricRepItem = curveVector[0];
			//DVec3d vec;
			//vec.Init(shapeGraphicProperties->getCentroid());

			//Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
			//	file.addTriplet<Ifc4::IfcDirection>(shapeGraphicProperties->getVectorAxisZ().x, shapeGraphicProperties->getVectorAxisZ().y, shapeGraphicProperties->getVectorAxisZ().z));


			//Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(
			//	Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
			//	std::string("Open"),
			//	(Ifc4::IfcBoundedCurve*)geometricRepItem);

			//Ifc4::IfcSweptAreaSolid* areaSolid = new Ifc4::IfcRevolvedAreaSolid(profileDef,
			//	IfcOperationsEnhancer::buildIfcAxis2Placement3D(vec,shapeGraphicProperties->getVectorAxisZ(),shapeGraphicProperties->getVectorAxisX()), localAxis1Placement,6.28);

			//geometricRepItem = areaSolid;
			
		}
		break;
		default:
		break;
	}	

	return geometricRepItem;

}


void IfcShapesEnhancer::enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			bool isElementSmartSolid = ifcElementBundle->getIsSmartSolid();
			this->bRepRelationship = new IfcBRepRelationship();

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());
			for (GraphicProperties* graphicProperties : dictionaryProperties.getGraphicPropertiesVector())
			{
				ShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<ShapesGraphicProperties*>(graphicProperties);
				if (shapeGraphicProperties != nullptr)
				{		
					Ifc4::IfcGeometricRepresentationItem* geometricRepItem = buildGeometricRepresentationShapes(shapeGraphicProperties, file, ifcElementBundle);
					if (geometricRepItem != nullptr)
					{
						ifcElementBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(shapeGraphicProperties, geometricRepItem));
					}
				}
			}
			
			//check if they belongs to a smart solid
			if (isElementSmartSolid)
			{
				//bRepRelationship->connectContinuosEdges();
				ifcElementBundle->addSolidEdgesCollection(
					bRepRelationship->getSmartSolidEdgesCollection()
				);
			}				
		}
	}
}

Ifc4::IfcCurve* IfcShapesEnhancer::buildIfcCurvePrimitives(CurveGraphicProperties * curveProperties, IfcHierarchyHelper<Ifc4>& file, ShapesTypeEnum curvesShapesType, IfcElementBundle*& ifcElementBundle, bool isClosed)
{
	Ifc4::IfcCurve* curveRepresentationItem = nullptr;

	switch (curveProperties->getCurvesTypeEnum())
	{
		case CurvesPrimitivesTypeEnum::BSPLINE:
		{
			BsplineGraphicProperties* curveP = dynamic_cast<BsplineGraphicProperties*>(curveProperties);
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
				tempEntityList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);

			file.addEntities(tempEntityList->generalize());

			if (curveP->getAreKnotsValid())
			{
				curveRepresentationItem = new Ifc4::IfcBSplineCurveWithKnots(
					curveP->getDegree(),
					controlPoints,
					Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
					curveP->getIsCLosed(),
					curveP->getIsSelfIntersect(),
					curveP->getKnotsMultiplicity(),
					curveP->getKnots(),
					Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED
				);
			}
			else
			{
				curveRepresentationItem = new Ifc4::IfcBSplineCurve(
					curveP->getDegree(),
					controlPoints,
					Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
					curveP->getIsCLosed(),
					curveP->getIsSelfIntersect()
				);
			}
		}
		break;

		case CurvesPrimitivesTypeEnum::ARC:
		{
			ArcGraphicProperties* curveP = dynamic_cast<ArcGraphicProperties*>(curveProperties);

			Ifc4::IfcAxis2Placement3D* place = IfcOperationsEnhancer::buildIfcAxis2Placement3D(
				curveP->getCenterOut(),
				curveP->getDirectionZ(),
				curveP->getDirectionX()
			);


			Ifc4::IfcCurve* curve = nullptr;

			if (curveP->getIsCircular())
			{
				curve = new Ifc4::IfcCircle(
					place,
					NumberUtils::convertMicrometersToMetters(curveP->getRadiusX())
				);
			}
			else //if (curveP->getIsFullEllipse())
			{
				curve = new Ifc4::IfcEllipse(
					place,
					NumberUtils::convertMicrometersToMetters(curveP->getRadiusX()),
					NumberUtils::convertMicrometersToMetters(curveP->getRadiusY())
				);
			}

			if (!isClosed)
			{
				IfcEntityList* t1EntityList = new IfcEntityList();
				IfcEntityList* t2EntityList = new IfcEntityList();

				Ifc4::IfcParameterValue* pV0 = new Ifc4::IfcParameterValue(curveP->getStartAngle());
				Ifc4::IfcParameterValue* pV1 = new Ifc4::IfcParameterValue(curveP->getSweepAngle());

				/*Ifc4::IfcCartesianPoint* cP0 = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(curveP->getStartPoint());
				Ifc4::IfcCartesianPoint* cP1 = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(curveP->getEndPoint());				
				
				t1EntityList->push(cP0);
				t2EntityList->push(cP1);*/

				t1EntityList->push(pV0);
				t2EntityList->push(pV1);

				boost::shared_ptr<IfcEntityList> trimOne(t1EntityList);
				boost::shared_ptr<IfcEntityList> trimTwo(t2EntityList);

				// Sense Agreement to TRUE (e.g. from 0° degree to 180°)
				// Except the case of a closed BasisCurve where both parameter 1 and parameter 2 exist, 
				// they shall be consistent with the sense flag, i.e., (sense = parameter 1 < parameter 2). 
				// Or, for every open curve where both parameter 1 and parameter 2 exist, they shall be consistent with the SenseAgreement, 
				// i.e., SenseAgreement = (parameter 1 < parameter 2).
				bool senseOfAgreement = (curveP->getStartAngle() < curveP->getSweepAngle());
				curveRepresentationItem = new Ifc4::IfcTrimmedCurve(curve, trimOne, trimTwo, senseOfAgreement, Ifc4::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER);
				//curveRepresentationItem = new Ifc4::IfcTrimmedCurve(curve, trimOne, trimTwo, senseOfAgreement, Ifc4::IfcTrimmingPreference::IfcTrimmingPreference_CARTESIAN);
			}
			else
				curveRepresentationItem = curve;
		}
		break;

		case CurvesPrimitivesTypeEnum::LINE:
		{
			LineGraphicProperties* curveP = dynamic_cast<LineGraphicProperties*>(curveProperties);

			DPoint3d p0 = curveP->getControlPoints().at(0);
			Ifc4::IfcCartesianPoint * cP0 = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p0);

			DPoint3d p1 = curveP->getDirectionTangent();
			Ifc4::IfcVector* dir0 = IfcOperationsEnhancer::buildIfcVectorFromDirectionPoint3D(p1);

			curveRepresentationItem = new Ifc4::IfcLine(cP0, dir0);
		}
		break;

		case CurvesPrimitivesTypeEnum::LINE_STRING:
		{
			LineStringGraphicProperties* curveP = dynamic_cast<LineStringGraphicProperties*>(curveProperties);
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
				tempEntityList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);

			file.addEntities(tempEntityList->generalize());

			curveRepresentationItem = new Ifc4::IfcPolyline(controlPoints);
			
		}
		break;

		case CurvesPrimitivesTypeEnum::INTERPOLATION_CURVE:
		{
			InterpolationGraphicProperties* curveP = dynamic_cast<InterpolationGraphicProperties*>(curveProperties);
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
				tempEntityList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);

			file.addEntities(tempEntityList->generalize());

			curveRepresentationItem = new Ifc4::IfcBSplineCurve(
				curveP->getDegree(),
				controlPoints,
				Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
				false,
				false
			);
		}
		break;

		//TODO[SB] Check representation assumption
		case CurvesPrimitivesTypeEnum::POINT_STRING:
		{
			PointStringGraphicProperties* curveP = dynamic_cast<PointStringGraphicProperties*>(curveProperties);

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint* cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
				
				//Add the point to the IfcElementBundle its own ports
				ifcElementBundle->addIfcPortsPoints(cP);
			}
			
		}
		break;

		default:
			break;
	}	

	return curveRepresentationItem;
}

std::vector<Ifc4::IfcCurve*> IfcShapesEnhancer::ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle)
{
	std::vector<Ifc4::IfcCurve*> curveVector;
	for each (CurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
	{
		Ifc4::IfcCurve* curveRepresentationItem = buildIfcCurvePrimitives(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcElementBundle, curvesShape->getIsClosed());

		curveVector.push_back(curveRepresentationItem);
	}

	return curveVector;
}

IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* IfcShapesEnhancer::buildIfcCompositeCurveSegment(std::vector<Ifc4::IfcCurve*> curveVector)
{
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>();

	for each (auto curve in curveVector)
	{
		Ifc4::IfcCompositeCurveSegment* item = nullptr;
		item = new Ifc4::IfcCompositeCurveSegment(
			Ifc4::IfcTransitionCode::IfcTransitionCode_CONTINUOUS,
			true,
			curve
		);

		if (item == nullptr)
			continue;

		tempEntityList->push(item);
	}

	return tempEntityList;
}




