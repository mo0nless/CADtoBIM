#include "../headers/IfcShapesEnhancer.h"


IfcShapesEnhancer::IfcShapesEnhancer()
{
	this->mShapeBoundTypeCurvesVector = vector<BoundTypeIfcCurve*>();
	this->mSingleShapeRepresentation = nullptr;
	this->mHasSingleShape = false;
}

bool IfcShapesEnhancer::hasSingleShapeItem()
{
	return this->mHasSingleShape;
}

Ifc4::IfcGeometricRepresentationItem * IfcShapesEnhancer::getSingleShapeRepresentation()
{
	return this->mSingleShapeRepresentation;
}

vector<BoundTypeIfcCurve*> IfcShapesEnhancer::getCurvesShapeRepresentationVector()
{
	return this->mShapeBoundTypeCurvesVector;
}

void IfcShapesEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, ShapesGraphicProperties* shapeGraphicProperties, IfcElementBundle*& ifcElementBundle,
	ElementBundle* elementBundle, bool addToIfcElementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	//Handler for boundaries 
	switch (shapeGraphicProperties->getBoundaryTypeCurvesContainer())
	{
		//All curves drawed as single are open (Line string inside pipes)
		//Curves should join head to tail in a single path. The path is not expected to be closed. 
		case CurvesBoundaryTypeEnum::OPEN:
		{
			vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);		

			BoundTypeIfcCurve* boundCurveVec = new BoundTypeIfcCurve();
			boundCurveVec->vecIfcCurves = curveVector;

			if (shapeGraphicProperties->getHasSingleCurve()) {
				mSingleShapeRepresentation = curveVector.front();
			}
			else //Complex Chain 
			{
				IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				Ifc4::IfcCompositeCurve* compositeCurve = new Ifc4::IfcCompositeCurve(complexChain, false);

				curveVector.clear();
				curveVector.push_back(compositeCurve);

				mSingleShapeRepresentation = compositeCurve;
			}

			boundCurveVec->vecPrimitivesCurves = shapeGraphicProperties->getCurvesPrimitivesContainerVector();
			boundCurveVec->boundary = CurvesBoundaryTypeEnum::OPEN;
			boundCurveVec->ifcCurve = curveVector.front();
			boundCurveVec->start = shapeGraphicProperties->getStartPoint();
			boundCurveVec->end = shapeGraphicProperties->getEndPoint();
			boundCurveVec->isClosed = shapeGraphicProperties->getIsClosed();
			this->mShapeBoundTypeCurvesVector.push_back(boundCurveVec);

			this->mHasSingleShape = true;
		}
		break;

		//This defines the OUTER boundaries of an entity (Solid/Surface) eg Smart Solid shape
		//Curves should join head to tail in a single closed path; this area expected to be an outer (or only) loop
		case CurvesBoundaryTypeEnum::OUTER:
		{
			vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);		

			BoundTypeIfcCurve* boundCurveVec = new BoundTypeIfcCurve();
			boundCurveVec->vecIfcCurves = curveVector;

			if (shapeGraphicProperties->getHasSingleCurve()) {
				mSingleShapeRepresentation = curveVector.front();
			}
			else
			{
				IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				//Ifc4::IfcCompositeCurve* outerBoundaryCurve = new Ifc4::IfcCompositeCurve(complexChain, false);
				Ifc4::IfcOuterBoundaryCurve* outerBoundaryCurve = new Ifc4::IfcOuterBoundaryCurve(complexChain, false);

				curveVector.clear();
				curveVector.push_back(outerBoundaryCurve);

				mSingleShapeRepresentation = curveVector.front();
			}

			boundCurveVec->vecPrimitivesCurves = shapeGraphicProperties->getCurvesPrimitivesContainerVector();
			boundCurveVec->boundary = CurvesBoundaryTypeEnum::OUTER;
			boundCurveVec->ifcCurve = curveVector.front();
			boundCurveVec->start = shapeGraphicProperties->getStartPoint();
			boundCurveVec->end = shapeGraphicProperties->getEndPoint();
			boundCurveVec->isClosed = shapeGraphicProperties->getIsClosed();
			this->mShapeBoundTypeCurvesVector.push_back(boundCurveVec);

			this->mHasSingleShape = true;
		}
		break;

		//This defines the INNER boundaries of an entity (Solid/Surface) eg Hole
		//Curves should join head to tail in a single closed path; this area is expected to be an inner loop.
		case CurvesBoundaryTypeEnum::INNER:
		{
			vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);

			BoundTypeIfcCurve* boundCurveVec = new BoundTypeIfcCurve();
			boundCurveVec->vecIfcCurves = curveVector;

			if (shapeGraphicProperties->getHasSingleCurve()) {
				mSingleShapeRepresentation = curveVector.front();
			}
			else
			{
				IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = nullptr;
				tempEntityList = buildIfcCompositeCurveSegment(curveVector);

				if (tempEntityList == nullptr)
					break;

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> complexChain(tempEntityList);

				//Ifc4::IfcCompositeCurve* innerBoundaryCurve = new Ifc4::IfcCompositeCurve(complexChain, false);
				Ifc4::IfcBoundaryCurve* innerBoundaryCurve = new Ifc4::IfcBoundaryCurve(complexChain, false);

				curveVector.clear();
				curveVector.push_back(innerBoundaryCurve);

				mSingleShapeRepresentation = curveVector.front();
			}

			boundCurveVec->vecPrimitivesCurves = shapeGraphicProperties->getCurvesPrimitivesContainerVector();
			boundCurveVec->boundary = CurvesBoundaryTypeEnum::INNER;
			boundCurveVec->ifcCurve = curveVector.front();
			boundCurveVec->start = shapeGraphicProperties->getStartPoint();
			boundCurveVec->end = shapeGraphicProperties->getEndPoint();
			boundCurveVec->isClosed = shapeGraphicProperties->getIsClosed();
			this->mShapeBoundTypeCurvesVector.push_back(boundCurveVec);

			this->mHasSingleShape = true;
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
					addToIfcElementBundle = false;
					enhance(file, shape, ifcElementBundle,elementBundle, addToIfcElementBundle);
				}
			}

			this->mHasSingleShape = false;
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
					addToIfcElementBundle = false;
					enhance(file, shape, ifcElementBundle, elementBundle,  addToIfcElementBundle);
				}
			}

			this->mHasSingleShape = false;
		}

		//Point and ports have no Boundary
		//no specific properties expected for contained curves or points. 
		case CurvesBoundaryTypeEnum::NONE_BOUNDARY:
		{
			vector<Ifc4::IfcCurve*> curveVector = ifcShapesCurvesParser(shapeGraphicProperties, file, ifcElementBundle);

			BoundTypeIfcCurve* boundCurveVec = new BoundTypeIfcCurve();
			boundCurveVec->vecIfcCurves = curveVector;
			boundCurveVec->vecPrimitivesCurves = shapeGraphicProperties->getCurvesPrimitivesContainerVector();

			boundCurveVec->boundary = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
			boundCurveVec->ifcCurve = curveVector.front();
			this->mShapeBoundTypeCurvesVector.push_back(boundCurveVec);

			mSingleShapeRepresentation = curveVector.front();

			this->mHasSingleShape = true;
		}
		break;
		default:
			break;
	}

	if (this->mSingleShapeRepresentation != nullptr && addToIfcElementBundle)
	{
		if (shapeGraphicProperties->getIsFilled()) //If It's a Shape included in an Element, build an IfcCurveBoundedPlane
		{
			Ifc4::IfcCurve* curve = (Ifc4::IfcCurve*)mSingleShapeRepresentation;

			Ifc4::IfcPlane* plane = new Ifc4::IfcPlane(file.addPlacement3d());

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCurve>> temp(new IfcTemplatedEntityList<Ifc4::IfcCurve>());

			Ifc4::IfcCurveBoundedPlane* shape = new Ifc4::IfcCurveBoundedPlane(plane, curve, temp);

			this->mSingleShapeRepresentation = shape;
		}
		auto bundle = new IfcGraphicPropertiesBundle(shapeGraphicProperties, mSingleShapeRepresentation,
			elementBundle->getElementHandle());
		bundle->setColor(elementBundle->getColor());
		bundle->setTransparency(elementBundle->getTransparency());
		bundle->setMaterial(elementBundle->getMaterial());

		ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);


		this->mSingleShapeRepresentation = nullptr;
	}
}

Ifc4::IfcCurve* IfcShapesEnhancer::buildIfcCurvePrimitives(CurveGraphicProperties * curveProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	Ifc4::IfcCurve* curveRepresentationItem = nullptr;

	switch (curveProperties->getCurvesTypeEnum())
	{
		case CurvesPrimitivesTypeEnum::BSPLINE:
		{
			BsplineGraphicProperties* curveP = dynamic_cast<BsplineGraphicProperties*>(curveProperties);
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			
			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = nullptr;

				//Check dimension 2D/3D
				if (dimension == IfcDimensionEnum::dim_3D)
					cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
				else if (dimension == IfcDimensionEnum::dim_2D)
					cP = IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(p);

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

			Ifc4::IfcAxis2Placement* place = nullptr;

			//Check dimension 2D/3D
			if (dimension == IfcDimensionEnum::dim_3D)
				place = place = IfcOperationsHelper::buildIfcAxis2Placement3D(
					curveP->getCenterOut(),
					curveP->getDirectionZ(),
					curveP->getDirectionX()
				);
			else if (dimension == IfcDimensionEnum::dim_2D)
				place = place = IfcOperationsHelper::buildIfcAxis2Placement2D(
					curveP->getCenterOut(),
					curveP->getDirectionX()
				);

			Ifc4::IfcCurve* curve = nullptr;

			if (curveP->getIsCircular())
			{
				curve = new Ifc4::IfcCircle(
					place,
					NumberUtils::convertCurrentUnitToMeters(curveP->getRadiusX())
				);
			}
			else //if (curveP->getIsFullEllipse())
			{
				curve = new Ifc4::IfcEllipse(
					place,
					NumberUtils::convertCurrentUnitToMeters(curveP->getRadiusX()),
					NumberUtils::convertCurrentUnitToMeters(curveP->getRadiusY())
				);
			}

			if (!IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(curveP->getStartPoint(), curveP->getEndPoint())) //!isClosed 
			{
				IfcEntityList* t1EntityList = new IfcEntityList();
				IfcEntityList* t2EntityList = new IfcEntityList();

				Ifc4::IfcParameterValue* pV0 = new Ifc4::IfcParameterValue(curveP->getStartAngle());
				Ifc4::IfcParameterValue* pV1 = new Ifc4::IfcParameterValue(curveP->getSweepAngle());

				/*Ifc4::IfcCartesianPoint* cP0 = IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(curveP->getStartPoint());
				Ifc4::IfcCartesianPoint* cP1 = IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(curveP->getEndPoint());				
				
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

			/*Ifc4::IfcCartesianPoint * cP0 = IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(curveP->getStartPoint());

			
			Ifc4::IfcVector* dir0 = IfcOperationsHelper::buildIfcVectorFromDirectionPoint3D<DVec3d>(curveP->getDirectionTangent());

			curveRepresentationItem = new Ifc4::IfcLine(cP0, dir0);*/

			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = nullptr;

				//Check dimension 2D/3D
				if (dimension == IfcDimensionEnum::dim_3D)
					cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
				else if (dimension == IfcDimensionEnum::dim_2D)
					cP = IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(p);

				tempEntityList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlPoints(tempEntityList);

			file.addEntities(tempEntityList->generalize());

			curveRepresentationItem = new Ifc4::IfcPolyline(controlPoints);
		}
		break;

		case CurvesPrimitivesTypeEnum::LINE_STRING:
		{
			LineStringGraphicProperties* curveP = dynamic_cast<LineStringGraphicProperties*>(curveProperties);
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

			for each(DPoint3d p in curveP->getControlPoints()) {
				Ifc4::IfcCartesianPoint * cP = nullptr;
				
				if(uvCoordsParse)
				{ 
					cP = new Ifc4::IfcCartesianPoint(vector<double>{p.x, p.y});
				}
				else
				{
					//Check dimension 2D/3D
					if (dimension == IfcDimensionEnum::dim_3D)
						cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
					else if (dimension == IfcDimensionEnum::dim_2D)
						cP = IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(p);
				}
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
				Ifc4::IfcCartesianPoint * cP = nullptr;

				//Check dimension 2D/3D
				if (dimension == IfcDimensionEnum::dim_3D)
					cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
				else if (dimension == IfcDimensionEnum::dim_2D)
					cP = IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(p);

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
				Ifc4::IfcCartesianPoint* cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);

				//Ifc4::IfcCartesianPoint * cP = nullptr;

				////Check dimension 2D/3D
				//if (dimension == IfcDimensionEnum::dim_3D)
				//	cP = IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(p);
				//else if (dimension == IfcDimensionEnum::dim_2D)
				//	cP = IfcOperationsHelper::buildIfcCartesian2DfromCoordsPoint3D(p);
				
				//Add the point to the IfcElementBundle its own ports
				ifcElementBundle->addIfcPortsPoints(cP);
			}
			
		}
		break;

		default:
			break;
	}	
	//Ifc4::IfcColourRgb* ifcColour = new Ifc4::IfcColourRgb(string("Color"), 1,0,0);
	//Ifc4::IfcDescriptiveMeasure* ss = new Ifc4::IfcDescriptiveMeasure(string("ss"));
	//Ifc4::IfcPreDefinedCurveFont* csfs = new Ifc4::IfcPreDefinedCurveFont(string("red"));
	//Ifc4::IfcCurveStyle* curveStyle = new Ifc4::IfcCurveStyle(string("style"), csfs, ss, ifcColour, boost::none);

	return curveRepresentationItem;
}

vector<Ifc4::IfcCurve*> IfcShapesEnhancer::ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	vector<Ifc4::IfcCurve*> curveVector;
	for each (CurveGraphicProperties* curveProperties in curvesShape->getCurvesPrimitivesContainerVector())
	{
		Ifc4::IfcCurve* curveRepresentationItem = buildIfcCurvePrimitives(curveProperties, file, ifcElementBundle);

		curveVector.push_back(curveRepresentationItem);
	}

	return curveVector;
}

IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* IfcShapesEnhancer::buildIfcCompositeCurveSegment(vector<Ifc4::IfcCurve*> curveVector)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

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




