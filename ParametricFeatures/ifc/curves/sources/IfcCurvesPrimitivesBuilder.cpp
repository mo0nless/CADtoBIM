#include "../headers/IfcCurvesPrimitivesBuilder.h"


//std::vector<Ifc4::IfcCurve*> IfcCurvesPrimitivesBuilder::buildIfcCurvesPrimitives(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file)
//{
//	CurvesPrimitivesContainer* curveContainer;
//	std::vector<Ifc4::IfcCurve*> repItemsVector;
//
//	if (graphicProperties.tryGetCurvesPrimitivesContainer(curveContainer)) 
//	{
//		switch (curveContainer->getBoundaryTypeCurvesContainer())
//		{
//			case CurvesBoundaryTypeEnum::OPEN:
//			{
//				buildCurvesContainerTypes(curveContainer, file, repItemsVector);
//			}
//			break;
//			case CurvesBoundaryTypeEnum::OUTER:
//			{
//				buildCurvesContainerTypes(curveContainer, file, repItemsVector);
//			}
//			break;
//			case CurvesBoundaryTypeEnum::INNER:
//			{
//				buildCurvesContainerTypes(curveContainer, file, repItemsVector);
//			}
//			break;
//			case CurvesBoundaryTypeEnum::PARITY_REGION:
//			{
//				buildCurvesContainerTypes(curveContainer, file, repItemsVector);
//			}
//			break;
//			case CurvesBoundaryTypeEnum::UNION_REGION:
//			{
//				buildCurvesContainerTypes(curveContainer, file, repItemsVector);
//			}
//			break;
//			default:
//			break;
//		}		
//	}
//
//	return repItemsVector;
//}
//
//Ifc4::IfcCurve* IfcCurvesPrimitivesBuilder::buildIfcCurvesRepresentationItems(ICurveGraphicProperties * curveProperties, IfcHierarchyHelper<Ifc4>& file, CurvesContainerTypeEnum curveContainerType)
//{
//	Ifc4::IfcCurve* curveRepresentationItem = nullptr;
//
//	switch (curveProperties->getCurvesTypeEnum())
//	{
//		case CurvesTypeEnum::BSPLINE:
//		{
//			BsplineGraphicProperties* curveP = dynamic_cast<BsplineGraphicProperties*>(curveProperties);
//			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
//
//			for each(DPoint3d p in curveP->getControlPoints()) {
//				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
//				tempEntityList->push(cP);
//			}
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);
//
//			file.addEntities(tempEntityList->generalize());
//
//			if (curveP->getAreKnotsValid())
//			{
//				curveRepresentationItem = new Ifc4::IfcBSplineCurveWithKnots(
//					curveP->getDegree(),
//					controlPoints,
//					Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
//					curveP->getIsCLosed(),
//					curveP->getIsSelfIntersect(),
//					curveP->getKnotsMultiplicity(),
//					curveP->getKnots(),
//					Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED
//				);
//			}
//			else
//			{
//				curveRepresentationItem = new Ifc4::IfcBSplineCurve(
//					curveP->getDegree(),
//					controlPoints,
//					Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
//					curveP->getIsCLosed(),
//					curveP->getIsSelfIntersect()
//				);
//			}
//		}
//		break;
//
//		case CurvesTypeEnum::ARC:
//		{
//			ArcGraphicProperties* curveP = dynamic_cast<ArcGraphicProperties*>(curveProperties);
//
//			Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
//				IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(curveP->getCenterOut()),
//				IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curveP->getDirectionZ()),
//				IfcOperationsEnhancer::buildIfcDirectionFromDirectionVec3D(curveP->getDirectionX())
//			);
//
//			Ifc4::IfcCurve* curve = nullptr;
//
//			if (curveP->getIsCircular())
//			{
//				curve = new Ifc4::IfcCircle(
//					place,
//					NumberUtils::convertMicrometersToMetters(curveP->getRadiusX())
//				);
//			}
//			else if (curveP->getIsFullEllipse())
//			{
//				curve = new Ifc4::IfcEllipse(
//					place,
//					NumberUtils::convertMicrometersToMetters(curveP->getRadiusX()),
//					NumberUtils::convertMicrometersToMetters(curveP->getRadiusY())
//				);
//			}
//
//			if (curveContainerType != CurvesContainerTypeEnum::CIRCLE && curveContainerType != CurvesContainerTypeEnum::ELLIPSE)
//			{
//				IfcEntityList* t1EntityList = new IfcEntityList();
//				IfcEntityList* t2EntityList = new IfcEntityList();
//
//				Ifc4::IfcParameterValue* pV0 = new Ifc4::IfcParameterValue(curveP->getStartAngle());
//				Ifc4::IfcParameterValue* pV1 = new Ifc4::IfcParameterValue(curveP->getSweepAngle());
//
//				t1EntityList->push(pV0);
//				t2EntityList->push(pV1);
//
//				boost::shared_ptr<IfcEntityList> trimOne(t1EntityList);
//				boost::shared_ptr<IfcEntityList> trimTwo(t2EntityList);
//
//				// Sense Agreement to TRUE (e.g. from 0° degree to 180°)
//				curveRepresentationItem = new Ifc4::IfcTrimmedCurve(curve, trimOne, trimTwo, true, Ifc4::IfcTrimmingPreference::IfcTrimmingPreference_PARAMETER);
//			}
//			else
//				curveRepresentationItem = curve;
//		}
//		break;
//		case CurvesTypeEnum::LINE:
//		{
//			LineGraphicProperties* curveP = dynamic_cast<LineGraphicProperties*>(curveProperties);
//
//			DPoint3d p0 = curveP->getControlPoints().at(0);
//			Ifc4::IfcCartesianPoint * cP0 = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p0);
//
//			DPoint3d p1 = curveP->getDirectionTangent();
//			Ifc4::IfcVector* dir0 = IfcOperationsEnhancer::buildIfcVectorFromDirectionPoint3D(p1);
//
//			curveRepresentationItem = new Ifc4::IfcLine(cP0, dir0);
//		}
//		break;
//		case CurvesTypeEnum::LINE_STRING:
//		{
//			LineGraphicProperties* curveP = dynamic_cast<LineGraphicProperties*>(curveProperties);
//			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
//
//			for each(DPoint3d p in curveP->getControlPoints()) {
//				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
//				tempEntityList->push(cP);
//			}
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);
//
//			file.addEntities(tempEntityList->generalize());
//
//			curveRepresentationItem = new Ifc4::IfcPolyline(controlPoints);
//		}
//		break;
//		case CurvesTypeEnum::INTERPOLATION_CURVE:
//		{
//			InterpolationGraphicProperties* curveP = dynamic_cast<InterpolationGraphicProperties*>(curveProperties);
//			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
//
//			for each(DPoint3d p in curveP->getControlPoints()) {
//				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(p);
//				tempEntityList->push(cP);
//			}
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);
//
//			file.addEntities(tempEntityList->generalize());
//
//			curveRepresentationItem = new Ifc4::IfcBSplineCurve(
//				curveP->getDegree(),
//				controlPoints,
//				Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
//				false,
//				false
//			);
//		}
//		break;
//		default:
//			break;
//	}
//
//	return curveRepresentationItem;
//}
//
//IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* IfcCurvesPrimitivesBuilder::buildIfcCompositeCurveSegment(CurvesPrimitivesContainer * curveContainer, IfcHierarchyHelper<Ifc4>& file)
//{
//	IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>();
//
//	for each (ICurveGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//	{
//
//		Ifc4::IfcCompositeCurveSegment* item = nullptr;
//		if(curveProperties)
//		item = new Ifc4::IfcCompositeCurveSegment(
//			Ifc4::IfcTransitionCode::IfcTransitionCode_CONTINUOUS,
//			true,
//			buildIfcCurvesRepresentationItems(curveProperties, file, curveContainer->getContainerTypeEnum())
//		);
//
//		if (item == nullptr)
//			continue;
//
//		file.addEntity(item);
//		tempEntityList->push(item);
//	}
//
//	return tempEntityList;
//}
//
//void IfcCurvesPrimitivesBuilder::buildCurvesContainerTypes(CurvesPrimitivesContainer* curveContainer, IfcHierarchyHelper<Ifc4>& file, std::vector<Ifc4::IfcCurve*>& repItemsVector)
//{
//	switch (curveContainer->getContainerTypeEnum())
//	{
//	case CurvesContainerTypeEnum::COMPLEX_CHAIN:
//	{
//		IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
//		tempEntityList = buildIfcCompositeCurveSegment(curveContainer, file);
//
//		if (tempEntityList == nullptr)
//			break;
//
//		boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);
//
//		if (curveContainer->getIsFilled() && curveContainer->getIsClosed())
//		{
//			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
//				complexChain,
//				false
//			);
//			
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//		else
//		{
//			Ifc4::IfcCurve* item = new Ifc4::IfcCompositeCurve(complexChain, false);
//
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//	}
//	break;
//
//	case CurvesContainerTypeEnum::SHAPE:
//	{
//		if (curveContainer->getIsFilled())
//		{
//			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
//			tempEntityList = buildIfcCompositeCurveSegment(curveContainer, file);
//
//			if (tempEntityList == nullptr)
//				break;
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> shape(tempEntityList);
//
//			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
//				shape,
//				false
//			);
//
//
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//		else 
//		{
//			for each (ICurveGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//			{
//				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curveContainer->getContainerTypeEnum());
//
//				if (item == nullptr)
//					continue;
//
//				file.addEntity(item);
//				repItemsVector.push_back(item);
//			}
//		}
//		
//	}
//	break;
//	case CurvesContainerTypeEnum::CIRCLE:
//	{
//		if (curveContainer->getIsFilled())
//		{
//			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
//			tempEntityList = buildIfcCompositeCurveSegment(curveContainer, file);
//
//			if (tempEntityList == nullptr)
//				break;
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> shape(tempEntityList);
//
//			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
//				shape,
//				false
//			);
//
//
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//		else
//		{
//			for each (ICurveGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//			{
//				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curveContainer->getContainerTypeEnum());
//
//				if (item == nullptr)
//					continue;
//
//				file.addEntity(item);
//				repItemsVector.push_back(item);
//			}
//		}
//	}
//	break;
//	case CurvesContainerTypeEnum::ELLIPSE:
//	{
//		if (curveContainer->getIsFilled())
//		{
//			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
//			tempEntityList = buildIfcCompositeCurveSegment(curveContainer, file);
//
//			if (tempEntityList == nullptr)
//				break;
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> shape(tempEntityList);
//
//			Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
//				shape,
//				false
//			);
//
//
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//		else
//		{
//			for each (ICurveGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//			{
//				Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curveContainer->getContainerTypeEnum());
//
//				if (item == nullptr)
//					continue;
//
//				file.addEntity(item);
//				repItemsVector.push_back(item);
//			}
//		}
//	}
//	break;
//	// The Default operation handles the standard curves creation (only curves primitives)
//	default:
//	{
//		for each (ICurveGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//		{
//			Ifc4::IfcCurve* item = buildIfcCurvesRepresentationItems(curveProperties, file, curveContainer->getContainerTypeEnum());
//
//			if (item == nullptr)
//				continue;
//
//			file.addEntity(item);
//			repItemsVector.push_back(item);
//		}
//	}
//	break;
//	}
//}



