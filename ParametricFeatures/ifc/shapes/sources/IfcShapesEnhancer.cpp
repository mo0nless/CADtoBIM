#include "../headers/IfcShapesEnhancer.h"

//IFC SPECS [SB] More information on shape representation are given by the IfcShapeRepresentation 
Ifc4::IfcGeometricRepresentationItem* IfcShapesEnhancer::buildGeometricRepresentationShapes(IShapesGraphicProperties* shapeGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcBundle*& ifcBundle)
{
	Ifc4::IfcGeometricRepresentationItem* geomItem = nullptr;

	//TODO [SB] Handle the boundary type for solids
	switch (shapeGraphicProperties->getBoundaryTypeCurvesContainer())
	{
		case CurvesBoundaryTypeEnum::OPEN:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
			/*if (shapeGraphicProperties->getIsFilled())
			{
				Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(
					Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
					std::string("Open"),
					(Ifc4::IfcBoundedCurve*)shape
				);
				Ifc4::IfcSweptAreaSolid* areaSolid = new Ifc4::IfcExtrudedAreaSolid(
					profileDef,
					IfcOperationsEnhancer::buildIfcAxis2Placement3D(
						shapeGraphicProperties->getCentroid(),
						shapeGraphicProperties->getVectorAxisZ(),
						shapeGraphicProperties->getVectorAxisX()
					),
					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(
						shapeGraphicProperties->getVectorAxisZ()
					),
					0.0
				);

				geomItem = areaSolid;
			}
			else
			{
				geomItem = shape;
			}*/			
		}
		break;
		case CurvesBoundaryTypeEnum::OUTER:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
			/*if (shapeGraphicProperties->getIsFilled())
			{
				Ifc4::IfcProfileDef* profileDef = new Ifc4::IfcArbitraryOpenProfileDef(
					Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA,
					std::string("Open"),
					(Ifc4::IfcBoundedCurve*)shape
				);

				Ifc4::IfcSweptAreaSolid* areaSolid = new Ifc4::IfcExtrudedAreaSolid(
					profileDef,
					IfcOperationsEnhancer::buildIfcAxis2Placement3D(
						shapeGraphicProperties->getCentroid(),
						shapeGraphicProperties->getVectorAxisZ(),
						shapeGraphicProperties->getVectorAxisX()
					),
					IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(
						shapeGraphicProperties->getVectorAxisZ()
					),
					0.0
				);

				geomItem = areaSolid;
			}
			else
			{
				geomItem = shape;
			}*/
		}
		break;
		case CurvesBoundaryTypeEnum::INNER:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
		}
		break;
		case CurvesBoundaryTypeEnum::PARITY_REGION:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
		}
		break;
		case CurvesBoundaryTypeEnum::UNION_REGION:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
		}
		case CurvesBoundaryTypeEnum::NONE_BOUNDARY:
		{
			geomItem = buildIfcCurvesSubTypes(shapeGraphicProperties, file, ifcBundle);
		}
		break;
		default:
		break;
	}		

	return geomItem;
}

void IfcShapesEnhancer::enhanceIfcShapesPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcBundle*& ifcBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());
			for (GraphicProperties* graphicProperties : dictionaryProperties.getGraphicPropertiesVector())
			{
				IShapesGraphicProperties* shapeGraphicProperties = dynamic_cast<IShapesGraphicProperties*>(graphicProperties);
				if (shapeGraphicProperties != nullptr)
				{
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildGeometricRepresentationShapes(shapeGraphicProperties, file, ifcBundle);
					if (ifcRepresentationItem != nullptr)
					{
						ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(graphicProperties, ifcRepresentationItem));
						ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}
}

Ifc4::IfcCurve* IfcShapesEnhancer::buildIfcCurvesRepresentationItems(ICurveGraphicProperties * curveProperties, IfcHierarchyHelper<Ifc4>& file, ShapesTypeEnum curvesShapesType, IfcBundle*& ifcBundle)
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
			else if (curveP->getIsFullEllipse())
			{
				curve = new Ifc4::IfcEllipse(
					place,
					NumberUtils::convertMicrometersToMetters(curveP->getRadiusX()),
					NumberUtils::convertMicrometersToMetters(curveP->getRadiusY())
				);
			}

			if (curvesShapesType != ShapesTypeEnum::CIRCLE && curvesShapesType != ShapesTypeEnum::ELLIPSE)
			{
				IfcEntityList* t1EntityList = new IfcEntityList();
				IfcEntityList* t2EntityList = new IfcEntityList();

				Ifc4::IfcParameterValue* pV0 = new Ifc4::IfcParameterValue(curveP->getStartAngle());
				Ifc4::IfcParameterValue* pV1 = new Ifc4::IfcParameterValue(curveP->getSweepAngle());

				t1EntityList->push(pV0);
				t2EntityList->push(pV1);

				boost::shared_ptr<IfcEntityList> trimOne(t1EntityList);
				boost::shared_ptr<IfcEntityList> trimTwo(t2EntityList);

				// Sense Agreement to TRUE (e.g. from 0° degree to 180°)
				curveRepresentationItem = new Ifc4::IfcTrimmedCurve(curve, trimOne, trimTwo, true, Ifc4::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER);
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
		case CurvesPrimitivesTypeEnum::POINT_STRING:
		{
			PointStringGraphicProperties* curveP = dynamic_cast<PointStringGraphicProperties*>(curveProperties);

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
								
				Ifc4::IfcPoint* point(cP);

				ifcBundle->addIfcPortsPoints(point);

				//Ifc4::IfcConnectionCurveGeometry* conPointEc =new Ifc4::IfcConnectionCurveGeometry()
				
				/*Ifc4::IfcRelConnectsWithRealizingElements* c = new Ifc4::IfcRelConnectsWithRealizingElements(
					std::string(""),
					file.getSingle<Ifc4::IfcOwnerHistory>(),
					boost::none,
					boost::none,
					connectionPointGeom
					);*/
			}
			

			//From here needs to be generated another object IfcConnectionPointGeometry
			
		}

		break;
		default:
			break;
	}

	return curveRepresentationItem;
}

IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* IfcShapesEnhancer::buildIfcCompositeCurveSegment(IShapesGraphicProperties * curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcBundle*& ifcBundle)
{
	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>();

	for each (ICurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
	{

		Ifc4::IfcCompositeCurveSegment* item = nullptr;
		if(curveProperties)
		item = new Ifc4::IfcCompositeCurveSegment(
			Ifc4::IfcTransitionCode::IfcTransitionCode_CONTINUOUS,
			true,
			buildIfcCurvesRepresentationItems(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcBundle)
		);

		if (item == nullptr)
			continue;

		//file.addEntity(item);
		tempEntityList->push(item);
	}

	return tempEntityList;
}

Ifc4::IfcCurve* IfcShapesEnhancer::buildIfcCurvesSubTypes(IShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcBundle*& ifcBundle)
{
	switch (curvesShape->getCurvesShapeTypeEnum())
	{
	case ShapesTypeEnum::COMPLEX_CHAIN:
	{
		IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
		tempEntityList = buildIfcCompositeCurveSegment(curvesShape, file, ifcBundle);

		if (tempEntityList == nullptr)
			break;

		boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

		if (curvesShape->getIsFilled() && curvesShape->getIsClosed())
		{
			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
				complexChain,
				false
			);

			return item;
		}
		else
		{
			Ifc4::IfcCurve* item = new Ifc4::IfcCompositeCurve(complexChain, false);

			return item;
		}
	}
	break;

	case ShapesTypeEnum::SHAPE:
	{
		if (curvesShape->getIsFilled())
		{
			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
			tempEntityList = buildIfcCompositeCurveSegment(curvesShape, file, ifcBundle);

			if (tempEntityList == nullptr)
				break;

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> curveShape(tempEntityList);

			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
				curveShape,
				false
			);

			return item;
		}
		else 
		{
			for each (ICurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
			{
				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcBundle);

				if (item == nullptr)
					continue;

				return item;
			}
		}
		
	}
	break;
	case ShapesTypeEnum::CIRCLE:
	{
		if (curvesShape->getIsFilled())
		{
			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
			tempEntityList = buildIfcCompositeCurveSegment(curvesShape, file, ifcBundle);

			if (tempEntityList == nullptr)
				break;

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> curveShape(tempEntityList);

			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
				curveShape,
				false
			);

			return item;
		}
		else
		{
			for each (ICurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
			{
				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcBundle);

				if (item == nullptr)
					continue;

				return item;
			}
		}
	}
	break;
	case ShapesTypeEnum::ELLIPSE:
	{
		if (curvesShape->getIsFilled())
		{
			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
			tempEntityList = buildIfcCompositeCurveSegment(curvesShape, file, ifcBundle);

			if (tempEntityList == nullptr)
				break;

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> shape(tempEntityList);

			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
				shape,
				false
			);

			return item;
		}
		else
		{
			for each (ICurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
			{
				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcBundle);

				if (item == nullptr)
					continue;

				return item;
			}
		}
	}
	break;
	case ShapesTypeEnum::CURVE:
	{
		for each (ICurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
		{
			Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curvesShape->getCurvesShapeTypeEnum(), ifcBundle);

			if (item == nullptr)
				continue;

			return item;
		}
	}
	break;
	default:		
		break;
	}

	return nullptr;
}



