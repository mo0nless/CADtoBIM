#include "../headers/GraphicsProcessorHelper.h"


GraphicsProcessorHelper::GraphicsProcessorHelper()
{

	this->filePath = SessionManager::getInstance()->getDataOutputFilePath();
	this->_modelerDataWriterManager = new ModelerDataWriterManager(true);
}

void GraphicsProcessorHelper::setDictionaryProperties(DictionaryProperties& newDictionaryProperties)
{
	this->pDictionaryProperties = &newDictionaryProperties;
}

void GraphicsProcessorHelper::setElementBundle(ElementBundle & newElementBundle)
{
	this->elementBundle = &newElementBundle;
}

ElementBundle * GraphicsProcessorHelper::getElementBundle()
{
	return this->elementBundle;
}

DictionaryProperties* GraphicsProcessorHelper::getDictionaryProperties()
{
	return this->pDictionaryProperties;
}

void GraphicsProcessorHelper::setSolidPrimCentroidAreaVolume(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	ofstream outfile;
	double area, volume;
	DVec3d centroid;
	RotMatrix axes;
	DVec3d momentxyz;

	primitive.ComputePrincipalAreaMoments(area, centroid, axes, momentxyz);
	// set the centroid values from here, because in the function bellow sometimes is 0
	GraphicProperties->setCentroid(centroid);
	GraphicProperties->setArea(area);

	outfile.open(filePath, ios_base::app);
	outfile << fixed;
	outfile << endl;
	outfile << "Centroid from Area [X] = " << centroid.x << endl;
	outfile << "Centroid from Area [Y] = " << centroid.y << endl;
	outfile << "Centroid from Area [Z] = " << centroid.z << endl;
	outfile << "Area1 = " << area << endl;
	outfile << endl;

	primitive.ComputePrincipalMoments(volume, centroid, axes, momentxyz);
	GraphicProperties->setVolume(volume);

	outfile << "Centroid from Volume [X] = " << centroid.x << endl;
	outfile << "Centroid from Volume [Y] = " << centroid.y << endl;
	outfile << "Centroid from Volume [Z] = " << centroid.z << endl;
	outfile << "Volume = " << volume << endl;
	outfile << "Area2 = " << area << endl;
	outfile << endl;
	
	outfile.close();

}

void GraphicsProcessorHelper::setGraphicPropertiesAxes(GraphicProperties*& graphicProperties, Transform& localToWorld)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	DVec3d columnVectorX, columnVectorY, columnVectorZ;
	DPoint3d origin = localToWorld.Origin();
	localToWorld.GetMatrixColumn(columnVectorX, 0);
	localToWorld.GetMatrixColumn(columnVectorY, 1);
	localToWorld.GetMatrixColumn(columnVectorZ, 2);

	graphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
	graphicProperties->setOrigin(origin);

	ofstream outfile;
	outfile.open(filePath, ios_base::app);
	outfile << fixed;
	outfile << endl;

	outfile << endl;
	outfile << "Origin [X] = " << origin.x << endl;
	outfile << "Origin [Y] = " << origin.y << endl;
	outfile << "Origin [Z] = " << origin.z << endl;
	outfile << endl;
	outfile.close();
}


void GraphicsProcessorHelper::setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& boxGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	// calculate height of the box
	double height;
	if (boxGraphicProperties->getVolume() > 0) {
		height = boxGraphicProperties->getVolume() / (dgnBoxDetail.m_topX * dgnBoxDetail.m_topY);
	}
	else {
		double x = abs(dgnBoxDetail.m_baseOrigin.x - dgnBoxDetail.m_topOrigin.x);
		double y = abs(dgnBoxDetail.m_baseOrigin.y - dgnBoxDetail.m_topOrigin.y);
		double z = abs(dgnBoxDetail.m_baseOrigin.z - dgnBoxDetail.m_topOrigin.z);

		height = sqrt(x*x + y*y + z*z);
	}

	// set box properties
	boxGraphicProperties->setLength(dgnBoxDetail.m_topX);
	boxGraphicProperties->setWidth(dgnBoxDetail.m_topY);
	boxGraphicProperties->setHeight(height);
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, boxGraphicProperties->toString());
}

void GraphicsProcessorHelper::setConeGraphicProperties(DgnConeDetail cgnConeDetail,ConeGraphicProperties*& coneGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	// calculate height of the cone
	double height;
	if (coneGraphicProperties->getVolume() > 0) {
		 height = (3 * coneGraphicProperties->getVolume()) /
			 (PI*(pow(cgnConeDetail.m_radiusA, 2) + cgnConeDetail.m_radiusA*cgnConeDetail.m_radiusB + pow(cgnConeDetail.m_radiusB, 2)));
	}
	else {
		double x = abs(cgnConeDetail.m_centerA.x - cgnConeDetail.m_centerB.x);
		double y = abs(cgnConeDetail.m_centerA.y - cgnConeDetail.m_centerB.y);
		double z = abs(cgnConeDetail.m_centerA.z - cgnConeDetail.m_centerB.z);

		height = sqrt(x*x + y*y + z*z);
	}
	// set cone properties
	coneGraphicProperties->setHeight(height);

	if (coneGraphicProperties->getPrimitiveTypeEnum() == PrimitiveTypeEnum::CONE) {
		coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusA);
		coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusB);
		coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerB);
		coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerA);
	}
	else if (coneGraphicProperties->getPrimitiveTypeEnum() == PrimitiveTypeEnum::TRUNCATED_CONE) {
		if (cgnConeDetail.m_radiusA > cgnConeDetail.m_radiusB)
		{
			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusA);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerB);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerA);
		}
		else
		{
			// inverse the axes to handle a trimmed cone where the top radius is bigger than the base radius
			coneGraphicProperties->setVectorAxis(-1* coneGraphicProperties->getVectorAxisX(), -1* coneGraphicProperties->getVectorAxisY(), -1* coneGraphicProperties->getVectorAxisZ());

			// inverse the base radius with top radius
			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusA);
			
			// inverse the base origin with top origin
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerA);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerB);
		}
	}
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, coneGraphicProperties->toString());
}

void GraphicsProcessorHelper::setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties *& cylinderGraphicProperties)
{
	// calculate height of the cylinder
	double height;
	if (cylinderGraphicProperties->getVolume() > 0)
	{
		height = (3 * cylinderGraphicProperties->getVolume()) /
			(PI*(pow(dgnConeDetail.m_radiusA, 2) + dgnConeDetail.m_radiusA*dgnConeDetail.m_radiusB + pow(dgnConeDetail.m_radiusB, 2)));
	}
	else
	{
		double x = abs(dgnConeDetail.m_centerA.x - dgnConeDetail.m_centerB.x);
		double y = abs(dgnConeDetail.m_centerA.y - dgnConeDetail.m_centerB.y);
		double z = abs(dgnConeDetail.m_centerA.z - dgnConeDetail.m_centerB.z);

		height = sqrt(x*x + y*y + z*z);
	}
	// set cylinder properties
	cylinderGraphicProperties->setHeight(height);
	cylinderGraphicProperties->setRadius(dgnConeDetail.m_radiusA);
	cylinderGraphicProperties->setBaseOrigin(dgnConeDetail.m_centerA);
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, cylinderGraphicProperties->toString());

}

void GraphicsProcessorHelper::setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	// calculate the radius
	double radius;
	if (sphereGraphicProperties->getVolume() > 0) {
		radius = pow(((sphereGraphicProperties->getVolume() / M_PI)*(3. / 4.)), 1. / 3.);
	}
	else {
		radius = -1;
	}
	// set radius
	sphereGraphicProperties->setRadius(radius);
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, sphereGraphicProperties->toString());

}

void GraphicsProcessorHelper::setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	// set torus properties
	torusGraphicProperties->setCenterPointOfRotation(centerOfRotation);
	torusGraphicProperties->setMinorRadius(dgnTorusPipeDetail.m_minorRadius);
	torusGraphicProperties->setMajorRadius(dgnTorusPipeDetail.m_majorRadius);
	torusGraphicProperties->setSweepRadians(sweepRadians);
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, torusGraphicProperties->toString());

}

void GraphicsProcessorHelper::setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, RotationalSweepGraphicProperties *& rotationalSweepGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	ofstream outfile;

	Transform localToWorld;
	Transform worldToLocal;
	
	double radius;
	DVec3d rotationAxes;
	double sweepRadians;
	DPoint3d centerOfRotation;

	bool addToDictionary = false;

	dgnRotationalSweepDetail.GetTransforms(localToWorld, worldToLocal);

	dgnRotationalSweepDetail.TryGetRotationAxis(centerOfRotation, rotationAxes, sweepRadians);
	dgnRotationalSweepDetail.GetRadius(radius, DgnRotationalSweepDetail::RadiusType::Centroidal);

	rotationalSweepGraphicProperties->setCenterRotation(centerOfRotation);	
	rotationalSweepGraphicProperties->setRadius(radius);
	rotationalSweepGraphicProperties->setSweepRadians(sweepRadians);
	rotationalSweepGraphicProperties->rotationAxes = rotationAxes;
	rotationalSweepGraphicProperties->axisOfRotation = dgnRotationalSweepDetail.m_axisOfRotation;

	setGraphicPropertiesAxes((GraphicProperties*&)rotationalSweepGraphicProperties, localToWorld);

	ShapesGraphicProperties* shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
	processShapesCurvesVector(*dgnRotationalSweepDetail.m_baseCurve, false, shapesGraphicProperties, addToDictionary);
	
	if (shapesGraphicProperties != nullptr) {
		rotationalSweepGraphicProperties->setShapesGraphicProperties(shapesGraphicProperties);
	}
}

void GraphicsProcessorHelper::setRuledSweepGraphicProperties(DgnRuledSweepDetail ruledSweepDetails, RuledSweepGraphicProperties *& ruledSweepGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	this->_modelerDataWriterManager->writeTitleProcessDataToFile("RULED SWEEP Curves START");

	bvector<SolidLocationDetail::FaceIndices> faceIndices;
	ruledSweepDetails.GetFaceIndices(faceIndices);
	for (auto i : faceIndices)
	{
		IGeometryPtr geom = ruledSweepDetails.GetFace(i);
		/*MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();
		bool addToDictionary = false;
		processMSBsplineSurface(*geom->GetAsMSBsplineSurface(), msBsplineSurfaceGraphicProperties, addToDictionary);*/
		if (geom != nullptr)
		{
			this->_modelerDataWriterManager->writeTupleDataToFile<int>("IGeometry Type", (int)geom->GetGeometryType());
		}

	}		

	for (CurveVectorPtr cv : ruledSweepDetails.m_sectionCurves)
	{
		DVec3d curveStart;
		DVec3d curveEnd;

		cv->GetStartEnd(curveStart, curveEnd);		

		bool curveAddToDictionary = false;
		ShapesGraphicProperties* shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
		processShapesCurvesVector(*cv, false, &*shapesGraphicProperties, curveAddToDictionary);
		ruledSweepGraphicProperties->addSectionCurve(shapesGraphicProperties);
	}
}

void GraphicsProcessorHelper::setExtrusionGraphicProperties(DgnExtrusionDetail extrusionDetails, ExtrusionGraphicProperties *& extrusionGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	ofstream outfile;

	extrusionGraphicProperties->setDirectionOfExtrusion(extrusionDetails.m_extrusionVector);
	extrusionGraphicProperties->setIsSolid (extrusionDetails.m_capped);

	ShapesGraphicProperties* shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

	bool addToDictionary = false;
	processShapesCurvesVector(*extrusionDetails.m_baseCurve, false, *&shapesGraphicProperties, addToDictionary);
	if (shapesGraphicProperties != nullptr) {
		extrusionGraphicProperties->setShapesGraphicProperties(shapesGraphicProperties);
	}

	DVec3d rDX, rDY, rDZ, cDX, cDY, cDZ;
	rDX = extrusionGraphicProperties->getVectorAxisX();
	rDY = extrusionGraphicProperties->getVectorAxisY();
	rDZ = extrusionGraphicProperties->getVectorAxisZ();

	cDX = shapesGraphicProperties->getVectorAxisX();
	cDY = shapesGraphicProperties->getVectorAxisY();
	cDZ = shapesGraphicProperties->getVectorAxisZ();

	outfile.open(filePath, ios_base::app);
	outfile << endl;
	outfile << "Extrusion solid: " << endl;
	outfile << "Direction [X] = " << rDX.x << ", " << rDX.y << ", " << rDX.z << endl;
	outfile << "Direction [Y] = " << rDY.x << ", " << rDY.y << ", " << rDY.z << endl;
	outfile << "Direction [Z] = " << rDZ.x << ", " << rDZ.y << ", " << rDZ.z << endl;
	outfile << endl;
	outfile << "Curve Profile: " << endl;
	outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << endl;
	outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << endl;
	outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << endl;
	
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__, extrusionGraphicProperties->toString());

}


GraphicProperties* GraphicsProcessorHelper::processConeAndCylinder(ISolidPrimitiveCR& primitive)
{
	ofstream outfile;

	DgnConeDetail dgnConeDetail;
	Transform localToWorld;
	Transform worldToLocal;

	primitive.TryGetDgnConeDetail(dgnConeDetail);
	
	double rA, rB;
	bool centerOfTheConeInB;
	
	//Try to set up a nonsingular coordinate frame. Returns false if centerB is in base plane !!!!
	centerOfTheConeInB = dgnConeDetail.GetTransforms(localToWorld, worldToLocal, rA, rB);

	outfile.open(filePath, ios_base::app);
	outfile << endl;
	outfile << endl;
	outfile << "THIS IS A CONE: " << endl;
	outfile << "Try to set up a nonsingular coordinate frame. Returns false if centerB is in base plane !!!! " << endl;
	outfile << "CenterB is in base plane: " << centerOfTheConeInB << endl;
	outfile << endl;
	outfile << endl;
	outfile.close();

	GraphicProperties* primitiveGraphicProperties = nullptr;

	if (Comparator::isEqual(dgnConeDetail.m_radiusA, dgnConeDetail.m_radiusB) && dgnConeDetail.m_radiusA > 0)
	{
		outfile.open(filePath, ios_base::app);
		outfile << fixed;
		outfile << endl;
		outfile << " Cylinder " << endl;
		outfile << endl;
		outfile.close();

		primitiveGraphicProperties = new CylinderGraphicProperties();

		setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
		setGraphicPropertiesAxes(primitiveGraphicProperties, localToWorld);
		setCylinderGraphicProperties(dgnConeDetail, (CylinderGraphicProperties*&)primitiveGraphicProperties);

	}
	else if (dgnConeDetail.m_radiusB == 0)
	{
		outfile.open(filePath, ios_base::app);
		outfile << fixed;
		outfile << endl;
		outfile << " Cone " << endl;
		outfile << endl;
		outfile.close();

		primitiveGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::CONE);

		setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
		setGraphicPropertiesAxes(primitiveGraphicProperties, localToWorld);
		setConeGraphicProperties(dgnConeDetail, (ConeGraphicProperties*&)primitiveGraphicProperties);
	}
	else if (dgnConeDetail.m_radiusB > 0 && !Comparator::isEqual(dgnConeDetail.m_radiusA, dgnConeDetail.m_radiusB))
	{
		outfile.open(filePath, ios_base::app);
		outfile << fixed;
		outfile << endl;
		outfile << " Truncated cone " << endl;
		outfile << endl;
		outfile.close();

		primitiveGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::TRUNCATED_CONE);

		setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
		setGraphicPropertiesAxes(primitiveGraphicProperties, localToWorld);
		setConeGraphicProperties(dgnConeDetail, (ConeGraphicProperties*&)primitiveGraphicProperties);
	}

	return *&primitiveGraphicProperties;
}


void GraphicsProcessorHelper::processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, bool addToDictionary)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	if (msBsplineSurfaceGraphicProperties == nullptr) {
		msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();
	}		

	this->_modelerDataWriterManager->writeMSBsplineSurfaceDataToFile(msBsplineSurface);
	
	size_t lowAindex, highAindex;
	bvector<double> vKnots, uKnots, vKnotsCompressed, uKnotsCompressed;
	bvector<size_t> vKmultiplicity, uKmultiplicity;
	bvector<bvector<DPoint2d>> boundaryUVLoops;
			
	bvector<DPoint3d> polesGrid, gridPoints;
	bvector<DPoint3d> weightPoles, unWeightPoles, polesToParse;
	bvector<double> weights;

	msBsplineSurface.GetVKnots(vKnots);
	msBsplineSurface.GetUKnots(uKnots);

	//Extract the multiplicity compressing the UV Knots
	MSBsplineCurve::CompressKnots(uKnots, msBsplineSurface.GetIntUOrder(), uKnotsCompressed, uKmultiplicity, lowAindex, highAindex);
	MSBsplineCurve::CompressKnots(vKnots, msBsplineSurface.GetIntVOrder(), vKnotsCompressed, vKmultiplicity, lowAindex, highAindex);
		
	const int nU = msBsplineSurface.GetIntNumUPoles();
	const int nV = msBsplineSurface.GetIntNumVPoles();

	msBsplineSurface.GetUnWeightedPoles(unWeightPoles);
	msBsplineSurface.GetPoles(weightPoles);
	msBsplineSurface.GetWeights(weights);

	if (msBsplineSurface.HasWeights())
		polesToParse = unWeightPoles;
	else
		polesToParse = weightPoles;
	
	//Get the UV Poles control points of the surface
	vector<vector<DPoint3d>> controlPointsUV;
	vector<vector<double>> weightsVec;
	
	for (size_t i = 0; i < nU; i++) 
	{		
		vector<DPoint3d> tempCP;
		vector<double> tempW;

		for (size_t j = 0; j < nV; j++) 
		{
			DPoint3d point = polesToParse.at(i); 
			tempCP.push_back(point);

			this->_modelerDataWriterManager->writeSinglePointDataToFile(point, (int)i);

			if (msBsplineSurface.HasWeights())
			{
				double w = weights.at(i);
				tempW.push_back(w);
				
				this->_modelerDataWriterManager->writeTupleDataToFile<double>("Weight", w);
			}		
			
			i += nU;
		}

		for (size_t j = 0; j < nV; j++) 
		{
			i -= nU;
		}

		controlPointsUV.push_back(tempCP);
		weightsVec.push_back(tempW);
	}
	


	//This function returns a parity regions
	//Outer/Inner BSpline Surface Boundaries
	CurveVectorPtr surfaceVecBound = msBsplineSurface.GetUVBoundaryCurves(true, true);
	ShapesGraphicProperties* surfaceShapesGP = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
	surfaceShapesGP->type = "BS";
	
	//This function returns a parity regions
	//Outer/Inner Line String Boundaries
	CurveVectorPtr linesVecBound = msBsplineSurface.GetUVBoundaryCurves(true, false);
	ShapesGraphicProperties* pCurveShapesGP = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
	pCurveShapesGP->type = "LS";

	//Process the primitives
	bool curveAddToDictionary = false;
	//processShapesCurvesVector(*surfaceVecBound, false, &*surfaceShapesGP, curveAddToDictionary);
	processShapesCurvesVector(*linesVecBound, false, &*pCurveShapesGP, curveAddToDictionary);

	//Points evaluation in 3D Space
	//evaluateUVShapesCurvesVector(msBsplineSurface, surfaceShapesGP, msBsplineSurfaceGraphicProperties);
	evaluateUVShapesCurvesVector(msBsplineSurface, pCurveShapesGP, msBsplineSurfaceGraphicProperties);

	//Add the Bounds
	//msBsplineSurfaceGraphicProperties->addSurfaceBoundaryShape(surfaceShapesGP);
	msBsplineSurfaceGraphicProperties->addSurfaceBoundaryShape(pCurveShapesGP);


//DPoint3d PolyLoop Evaluation MDL
#if false
	vector<vector<DPoint3d>> UVBoundsP;
	for (int i = 0; i<msBsplineSurface.numBounds; i++)
	{
		vector<DPoint3d> bound;
		DPoint3d   *pPoints = (DPoint3d *)dlmSystem_mdlMalloc(msBsplineSurface.boundaries[i].numPoints * sizeof(DPoint3d));
		for (int j = 0; j < msBsplineSurface.boundaries[i].numPoints; j++)
		{
			DPoint3d evalP;
			msBsplineSurface.EvaluatePoint(evalP, msBsplineSurface.boundaries[i].points[j].x, msBsplineSurface.boundaries[i].points[j].y);
			bound.push_back(evalP);
			/*mdlBspline_evaluateSurfacePoint(&pPoints[j], NULL, NULL, NULL,
				msBsplineSurface.boundaries[i].points[j].x, msBsplineSurface.boundaries[i].points[j].y, &(MSBsplineSurface)msBsplineSurface);*/
		}
		UVBoundsP.push_back(bound);
	}
#endif

//Bounds as points
#if false
	vector<vector<DPoint3d>> boundsVectorPoints;
	//msBsplineSurface.GetUVBoundaryLoops(boundaryUVLoops, true);
	msBsplineSurface.GetUVBoundaryLoops(boundaryUVLoops, false);

	//Points Loop of the boundaries
	for (auto b : boundaryUVLoops)
	{
		/*outfile.open(filePath, ios_base::app);
		outfile << "-------- Points UV Boundary --------" << endl;
		outfile.close();*/

		vector<DPoint3d> bound;
		for (auto uv : b)
		{
			DPoint3d evalP;
			msBsplineSurface.EvaluatePoint(evalP, uv.x, uv.y);
			bound.push_back(evalP);
		}

		boundsVectorPoints.push_back(bound);
	}
#endif
		

	msBsplineSurfaceGraphicProperties->setUVIsClosed(msBsplineSurface.GetIsUClosed(), msBsplineSurface.GetIsVClosed());
	msBsplineSurfaceGraphicProperties->setUVKnots(uKnotsCompressed, vKnotsCompressed);
	msBsplineSurfaceGraphicProperties->setUVKnotsMultiplicity(uKmultiplicity, vKmultiplicity);
	msBsplineSurfaceGraphicProperties->setUVOrder(msBsplineSurface.GetIntUOrder(), msBsplineSurface.GetIntVOrder());
	msBsplineSurfaceGraphicProperties->setWeights(weightsVec);
	msBsplineSurfaceGraphicProperties->setControlPoints(controlPointsUV, msBsplineSurface.GetIntNumUPoles(), msBsplineSurface.GetIntNumVPoles());
	msBsplineSurfaceGraphicProperties->hasValidWeights = msBsplineSurface.HasWeights();
	msBsplineSurfaceGraphicProperties->hasValidKnots = msBsplineSurface.HasValidKnotAllocation();
	//msBsplineSurfaceGraphicProperties->setBoundsVectorPoints(boundsVectorPoints);

	if (addToDictionary) {
		this->elementBundle->setGraphicProperties(*msBsplineSurfaceGraphicProperties);
	}
}

void GraphicsProcessorHelper::evaluateUVShapesCurvesVector(MSBsplineSurfaceCR msBsplineSurface, ShapesGraphicProperties *& shapesGraphicProperties, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	//Parity Region Container
	if (shapesGraphicProperties->hasShapesGraphicsContainer())
	{
		DVec3d newCentroid;
		DPoint3d shapeCentroid, shapeStartPoint, shapeEndpoint;

		//Save the faceID to Parity Region
		shapesGraphicProperties->addFaceBoundID(msBsplineSurfaceGraphicProperties->getFaceId());
		shapesGraphicProperties->setNodeId(msBsplineSurfaceGraphicProperties->getNodeId());

		msBsplineSurface.EvaluatePoint(shapeCentroid, shapesGraphicProperties->getCentroid().x, shapesGraphicProperties->getCentroid().y);
		msBsplineSurface.EvaluatePoint(shapeStartPoint, shapesGraphicProperties->getStartPoint().x, shapesGraphicProperties->getStartPoint().y);
		msBsplineSurface.EvaluatePoint(shapeEndpoint, shapesGraphicProperties->getEndPoint().x, shapesGraphicProperties->getEndPoint().y);

		//Keep The UV
		shapesGraphicProperties->setUVstartEndPoints(shapesGraphicProperties->getStartPoint(), shapesGraphicProperties->getEndPoint());

		newCentroid.Init(shapeCentroid);
		shapesGraphicProperties->setCentroid(newCentroid);
		shapesGraphicProperties->setStartEndPoints(shapeStartPoint, shapeEndpoint);

		// Outer, Inner Boundaries NB: the path is supposed to be always closed
		for (auto boundary : shapesGraphicProperties->getShapesGraphicsContainer())
		{
			//Save the faceID to the Outer/Inner boundary
			boundary->addFaceBoundID(msBsplineSurfaceGraphicProperties->getFaceId());
			boundary->setNodeId(msBsplineSurfaceGraphicProperties->getNodeId());

			msBsplineSurface.EvaluatePoint(shapeCentroid, boundary->getCentroid().x, boundary->getCentroid().y);
			msBsplineSurface.EvaluatePoint(shapeStartPoint, boundary->getStartPoint().x, boundary->getStartPoint().y);
			msBsplineSurface.EvaluatePoint(shapeEndpoint, boundary->getEndPoint().x, boundary->getEndPoint().y);

			//Keep The UV
			boundary->setUVstartEndPoints(boundary->getStartPoint(), boundary->getEndPoint());

			newCentroid.Init(shapeCentroid);
			boundary->setCentroid(newCentroid);
			boundary->setStartEndPoints(shapeStartPoint, shapeEndpoint);

			// Primitives curves that compose the boundary (UV coordinates as control points)
			for (auto curvePrimitive : boundary->getCurvesPrimitivesContainerVector())
			{
				DPoint3d cvStartPoint, cvEndpoint;

				// Evaluation of the Control Points using the surface
				vector<DPoint3d> controlPointsBound;
				
				//Keep the UV
				vector<DPoint3d> curveControlPointsUV;
				
				for (auto uv : curvePrimitive->getControlPoints())
				{

					DPoint3d evalP;
					msBsplineSurface.EvaluatePoint(evalP, uv.x, uv.y);
					controlPointsBound.push_back(evalP);

					//Keep the UV
					curveControlPointsUV.push_back(uv);
				}

				//Reset to the new evaluated Control Points
				curvePrimitive->setControlPoints(controlPointsBound);

				//Keep the UV
				curvePrimitive->setUVcontrolPoints(curveControlPointsUV);

				msBsplineSurface.EvaluatePoint(cvStartPoint, curvePrimitive->getStartPoint().x, curvePrimitive->getStartPoint().y);
				msBsplineSurface.EvaluatePoint(cvEndpoint, curvePrimitive->getEndPoint().x, curvePrimitive->getEndPoint().y);

				//Reset the Start and End Point
				curvePrimitive->setStartEndPoints(cvStartPoint, cvEndpoint);

				//Keep the UV
				curvePrimitive->setUVstartEndPoints(curvePrimitive->getStartPoint(), curvePrimitive->getEndPoint());
			}
		}
	}

}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
void GraphicsProcessorHelper::processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	for each (ICurvePrimitivePtr curvePrimitive in curvesVector)
	{
		this->_modelerDataWriterManager->writeCurvePrimitiveDataToFile(curvePrimitive);

		switch (curvePrimitive->GetCurvePrimitiveType())
		{
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
		{
			AkimaGraphicProperties* curveGraphicProperties = new AkimaGraphicProperties();

			if (curvePrimitive->GetAkimaCurveCP() != nullptr)
			{
				for (auto point : *curvePrimitive->GetAkimaCurveCP())
				{
					//PointPrint
					this->_modelerDataWriterManager->writeSinglePointDataToFile(point);
				}

				curveGraphicProperties->setControlPoints(*curvePrimitive->GetAkimaCurveCP());
			}

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc:
		{
			ArcGraphicProperties* curveGraphicProperties = new ArcGraphicProperties();

			DEllipse3d ellipse;
			DPoint3d centerOUT, startP, endP;
			DVec3d directionX, directionY;
			double* pQuatXYZW = nullptr;
			double rx, ry, startAngle, sweepAngle, length;

			if (!curvePrimitive->TryGetArc(ellipse))
				break;

			ellipse.GetDGNFields3d(centerOUT, pQuatXYZW, directionX, directionY, rx, ry, startAngle, sweepAngle);
			
			ellipse.EvaluateEndPoints(startP, endP);
			bvector<DPoint3d> polesControlP;
			polesControlP.push_back(startP);
			polesControlP.push_back(endP);

			curveGraphicProperties->setLength(ellipse.ArcLength());
			curveGraphicProperties->setIsCircular(ellipse.IsCircular());
			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setDirectionXY(directionX, directionY);
			curveGraphicProperties->setStartAngle(startAngle);
			curveGraphicProperties->setSweepAngle(sweepAngle);
			curveGraphicProperties->setCenterOut(centerOUT);
			curveGraphicProperties->setRadiusXY(rx, ry);
			curveGraphicProperties->setIsFullEllipse(ellipse.IsFullEllipse());
			curveGraphicProperties->setStartEndPoints(startP, endP);

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
		{
			BsplineGraphicProperties* curveGraphicProperties = new BsplineGraphicProperties();

			MSBsplineCurvePtr bSpline = curvePrimitive->GetBsplineCurvePtr();
			DPoint3d startP, endP;
			bvector<DPoint3d> polesControlP;
			

			if (bSpline != nullptr)
			{
				bSpline->ExtractEndPoints(startP, endP);
				
				bSpline->GetPoles(polesControlP);

				for (auto point : polesControlP)
				{
					//PointPrint
					this->_modelerDataWriterManager->writeSinglePointDataToFile(point);
				}


				if (bSpline->AreKnotsValid()) {

					bvector<double> inKnots, outKnots;
					bvector<size_t> multiplicityKnots;
					size_t highIndex, lowIndex;
					bSpline->GetKnots(inKnots);

					bSpline->CompressKnots(inKnots, int(bSpline->GetOrder()), outKnots, multiplicityKnots, lowIndex, highIndex);

					curveGraphicProperties->setAreKnotsValid(bSpline->AreKnotsValid());
					curveGraphicProperties->setKnots(outKnots);
					curveGraphicProperties->setKnotsMultiplicity(multiplicityKnots);
				}

				curveGraphicProperties->setIsClosed(bSpline->IsClosed());
				curveGraphicProperties->setIsSelfIntersect(false);
				curveGraphicProperties->setControlPoints(polesControlP);
				curveGraphicProperties->setOrder(bSpline->GetOrder());
				curveGraphicProperties->setStartEndPoints(startP, endP);

				if (curveGraphicProperties != nullptr)
					shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);

			}
			else { break; }
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
		{
			if (curvePrimitive->GetChildCurveVectorCP() != nullptr)
			{
				CurveVectorCP cPvector = curvePrimitive->GetChildCurveVectorCP();
				ShapesGraphicProperties* newShapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
				bool addToDictionary = false;
				processShapesCurvesVector(*cPvector, false, &*newShapesGraphicProperties, addToDictionary);
				shapesGraphicProperties->insertShapesGraphicProperties(newShapesGraphicProperties);
			}
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
		{
			InterpolationGraphicProperties* curveGraphicProperties = new InterpolationGraphicProperties();

			bvector<DPoint3d> polesControlP;
			DPoint3d startP, endP;
			curvePrimitive->GetStartEnd(startP, endP);

			if (curvePrimitive->GetInterpolationCurveCP() != nullptr)
			{
				MSInterpolationCurveCP intCurve = curvePrimitive->GetInterpolationCurveCP();
				interpolationParam intParams = curvePrimitive->GetInterpolationCurveCP()->params;

				for (size_t k = 0; k < intParams.numPoints; k++)
				{
					DPoint3d point = curvePrimitive->GetInterpolationCurveCP()->fitPoints[k];
					polesControlP.push_back(point);

					//PointPrint
					this->_modelerDataWriterManager->writeSinglePointDataToFile(point);
				}

				curveGraphicProperties->setControlPoints(polesControlP);
				curveGraphicProperties->setOrder(intCurve->GetOrder());
				curveGraphicProperties->setIsPeriodic(intParams.isPeriodic);
				curveGraphicProperties->setStartEndPoints(startP, endP);

			}

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;

		//TODO [SB] Check Line starting point and crf Line String
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
		{
			LineGraphicProperties* curveGraphicProperties = new LineGraphicProperties();

			DSegment3d segment;
			DPoint3d startP, endP;

			if (curvePrimitive->TryGetLine(segment))
			{
				curvePrimitive->GetStartEnd(startP, endP);
				
				bvector<DPoint3d> polesControlP;
				polesControlP.push_back(startP);
				polesControlP.push_back(endP);

				curveGraphicProperties->setControlPoints(polesControlP);				
				curveGraphicProperties->setStartEndPoints(startP, endP);
			}

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: //Polyline
		{
			LineStringGraphicProperties* curveGraphicProperties = new LineStringGraphicProperties();

			DPoint3d startP, endP;

			curvePrimitive->GetStartEnd(startP, endP);

			bvector<DPoint3d> polesControlP;
			if (curvePrimitive->GetLineStringCP() != nullptr) {
				for each (DPoint3d point in *curvePrimitive->GetLineStringCP())
				{
					polesControlP.push_back(point); 

					//PointPrint
					//this->_modelerDataWriterManager->writeSinglePointDataToFile(point);
				}
			}

			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setStartEndPoints(startP, endP);

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}

		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
		{
			CurveGraphicProperties* curveGraphicProperties = nullptr;

			if (curvePrimitive->GetPartialCurveDetailCP() != nullptr)
			{
				//TODO [SB] NEEDS TO BE CHECKED the partial curve composition
				//return processCurvePrimitives(curve->GetPartialCurveDetailCP()->parentCurve);
			}

		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
		{
			PointStringGraphicProperties* curveGraphicProperties = new PointStringGraphicProperties();

			bvector<DPoint3d> polesControlP;

			if (curvePrimitive->GetPointStringCP() != nullptr)
			{
				for (auto point: *curvePrimitive->GetPointStringCP())
				{
					polesControlP.push_back(point);

					//PointPrint
					this->_modelerDataWriterManager->writeSinglePointDataToFile(point);
				}

				curveGraphicProperties->setControlPoints(polesControlP);

			}
			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
		{
			//TODO [SB] Needs to be checked how to handle Spiral 
			if (curvePrimitive->GetSpiralPlacementCP() != nullptr)
			{
				//DSpiral2dPlacementCP spiralPlace = curve->GetSpiralPlacementCP();
			}
		}
		break;
		default:
			break;
		}
	}
}

void GraphicsProcessorHelper::processShapesCurvesVector(CurveVectorCR & curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties, bool addToDictionary)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	if (!curvesVector.empty())
	{
		if (shapesGraphicProperties == nullptr)
		{
			shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
		}

		this->_modelerDataWriterManager->writeShapeCurvesVectorDataToFile(curvesVector);

		DPoint3d center, start, end;
		DRange3d range, planarRange;
		DVec3d normal, centroid;
		Transform localToWorld, worldToLocal, planaLocalToWorld, planarWorldToLocal;
		bool isClosed = false;
		double area;

		curvesVector.GetStartEnd(start, end);
		curvesVector.CentroidNormalArea(center, normal, area);	centroid.Init(center);

		//TODO [SB] Check the correct enumeration type (first 2 enum suggested by Thibaut)
		curvesVector.CloneInLocalCoordinates(LocalCoordinateSelect::LOCAL_COORDINATE_SCALE_01RangeBothAxes, localToWorld, worldToLocal, range);
		curvesVector.IsPlanar(planaLocalToWorld, planarWorldToLocal, planarRange);
		curvesVector.IsPlanarWithDefaultNormal(localToWorld, worldToLocal, range, &normal);

		// Chek if the shape is closed 
		if (curvesVector.IsClosedPath())
			isClosed = curvesVector.IsClosedPath();
		else if (curvesVector.IsPhysicallyClosedPath())
			isClosed = curvesVector.IsPhysicallyClosedPath();

		setGraphicPropertiesAxes((GraphicProperties*&)shapesGraphicProperties, localToWorld);

		//Process the primitives inside the Curve Vector
		processCurvesPrimitives(curvesVector, shapesGraphicProperties);

		shapesGraphicProperties->setIsFilled(isFilled);
		shapesGraphicProperties->setArea(area);
		shapesGraphicProperties->setCentroid(centroid);
		shapesGraphicProperties->setNormal(normal);
		shapesGraphicProperties->setIsClosed(isClosed);
		shapesGraphicProperties->setStartEndPoints(start, end);

		//Bugged function returns Primitive Type curves.HasSingleCurvePrimitive() so check if the vector is equal to 1
		shapesGraphicProperties->setHasSingleCurve(curvesVector.size() == 1);
		shapesGraphicProperties->setBoundaryTypeCurvesContainer(curvesVector.GetBoundaryType());

		if (shapesGraphicProperties != nullptr && !shapesGraphicProperties->getCurvesPrimitivesContainerVector().empty() && addToDictionary)
			this->elementBundle->setGraphicProperties(*shapesGraphicProperties);
		

	}
}


GraphicProperties* GraphicsProcessorHelper::processSolidPrimitives(ISolidPrimitiveCR & primitive, bool addToDictionary)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	pDictionaryProperties->setIsPrimitiveSolid(true);
	GraphicProperties* primitiveGraphicProperties = nullptr;

	switch (primitive.GetSolidPrimitiveType())
	{
	case SolidPrimitiveType::SolidPrimitiveType_DgnBox:
	{
		DgnBoxDetail boxDetails;

		if (primitive.TryGetDgnBoxDetail(boxDetails))
		{
			Transform localToWorld, worldToLocal;

			this->_modelerDataWriterManager->writeBoxDataToFile(boxDetails);

			// get local to world class to get the X,Y,Z axes 
			boxDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);

			primitiveGraphicProperties = new BoxGraphicProperties();

			// set centroid, area and volume
			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);

			// set X,Y,Z axes
			DVec3d columnVectorX, columnVectorY, columnVectorZ;

			columnVectorX = boxDetails.ParameterizationSign() * boxDetails.m_vectorX;
			columnVectorY = boxDetails.ParameterizationSign() * boxDetails.m_vectorY;

			columnVectorZ.CrossProduct(boxDetails.m_vectorX, boxDetails.m_vectorY);
			columnVectorZ = boxDetails.ParameterizationSign() * columnVectorZ;

			primitiveGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
			setBoxGraphicProperties(boxDetails, (BoxGraphicProperties*&)primitiveGraphicProperties);

		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnCone:
	{
		DgnConeDetail coneDetails;

		if (primitive.TryGetDgnConeDetail(coneDetails))
		{
			this->_modelerDataWriterManager->writeConeDataToFile(coneDetails);
			// get local to world class to get the X,Y,Z axes 
			primitiveGraphicProperties = processConeAndCylinder(primitive);
		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnExtrusion:
	{
		DgnExtrusionDetail extrusionDetails;

		if (primitive.TryGetDgnExtrusionDetail(extrusionDetails))
		{
			Transform localToWorld, worldToLocal;
			extrusionDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			this->_modelerDataWriterManager->writeExtrusionDataToFile(extrusionDetails);

			primitiveGraphicProperties = new ExtrusionGraphicProperties();
			setExtrusionGraphicProperties(extrusionDetails, (ExtrusionGraphicProperties*&)primitiveGraphicProperties);

			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
			setGraphicPropertiesAxes(primitiveGraphicProperties, localToWorld);
		}
	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnRotationalSweep:
	{
		DgnRotationalSweepDetail rotSweepDetails;

		if (primitive.TryGetDgnRotationalSweepDetail(rotSweepDetails))
		{

			this->_modelerDataWriterManager->writeRotationalSweepDataToFile(rotSweepDetails);

			primitiveGraphicProperties = new RotationalSweepGraphicProperties();
			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
			setRotationalSweepGraphicProperties(rotSweepDetails, (RotationalSweepGraphicProperties*&)primitiveGraphicProperties);
		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnRuledSweep:
	{
		DgnRuledSweepDetail ruledSweepDetails;

		if (primitive.TryGetDgnRuledSweepDetail(ruledSweepDetails))
		{
			Transform localToWorld, worldToLocal;
			ruledSweepDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			this->_modelerDataWriterManager->writeRuledSweepDataToFile(ruledSweepDetails);

			primitiveGraphicProperties = new RuledSweepGraphicProperties();
			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
			setGraphicPropertiesAxes(primitiveGraphicProperties, localToWorld);
			setRuledSweepGraphicProperties(ruledSweepDetails, (RuledSweepGraphicProperties*&)primitiveGraphicProperties);
		}
	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnSphere:
	{
		DgnSphereDetail sphereDetails;

		if (primitive.TryGetDgnSphereDetail(sphereDetails))
		{
			
			this->_modelerDataWriterManager->writeSphereDataToFile(sphereDetails);

			primitiveGraphicProperties = new SphereGraphicProperties();
			// set centroid, area and volume
			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);
			setGraphicPropertiesAxes(*&primitiveGraphicProperties, sphereDetails.m_localToWorld);

			// set spehere properties
			setSphereGraphicProperties((SphereGraphicProperties*&) primitiveGraphicProperties);
		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_DgnTorusPipe:
	{
		DgnTorusPipeDetail torusDetails;


		if (primitive.TryGetDgnTorusPipeDetail(torusDetails))
		{
			RotMatrix rotationAxes;
			DPoint3d centerRotation;

			Transform localToWorld, worldToLocal;

			double radiusA, radiusB, sweepRadians;
			this->_modelerDataWriterManager->writeTorusDataToFile(torusDetails);

			// get local to world class to get the X,Y,Z axes 
			torusDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			torusDetails.TryGetFrame(centerRotation, rotationAxes, radiusA, radiusB, sweepRadians);

			primitiveGraphicProperties = new TorusGraphicProperties();

			// set centroid, area and volume
			setSolidPrimCentroidAreaVolume(primitive, primitiveGraphicProperties);

			// set X,Y,Z axes
			DVec3d columnVectorX, columnVectorY, columnVectorZ;

			columnVectorX = torusDetails.ParameterizationSign() * torusDetails.m_vectorX;
			columnVectorY = torusDetails.ParameterizationSign() * torusDetails.m_vectorY;

			columnVectorZ.CrossProduct(torusDetails.m_vectorX, torusDetails.m_vectorY);
			columnVectorZ = torusDetails.ParameterizationSign() * columnVectorZ;

			primitiveGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
			setTorusGraphicProperties(torusDetails, sweepRadians, centerRotation, (TorusGraphicProperties*&)primitiveGraphicProperties);
		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_None:
	{

	}

	default:
		break;
	}

	if (addToDictionary && primitiveGraphicProperties != nullptr) {
		this->elementBundle->setGraphicProperties(*primitiveGraphicProperties);
	}
		
	if (primitiveGraphicProperties != nullptr)
		return *&primitiveGraphicProperties;
	else
		return nullptr;
}

void GraphicsProcessorHelper::processBodySolid(ISolidKernelEntityCR entity, bool meshProcessing) //DEFAULT meshProcessing = false
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	this->_modelerDataWriterManager->writeTitleProcessDataToFile("BRep Processing");

	pDictionaryProperties->setIsSmartSolid(true);

	this->_modelerDataWriterManager->writeBodyDataToFile(entity);

	ofstream outfile;

	SolidUtil::Debug::DumpEntity(entity, L"DumpEntity");

	SolidEntityGraphicProperties* solidKernelEntity = new SolidEntityGraphicProperties();
	solidKernelEntity->meshProcessing = meshProcessing;
	solidKernelEntity->setBRepTypeEnum((int)entity.GetEntityType());


#pragma region SOLID_PROCESS

	if (!meshProcessing)
	{
		bvector<ISubEntityPtr> subEntitiesFaces;
		bvector<ISubEntityPtr> subEntitiesEdges;
		bvector<ISubEntityPtr> subEntitiesVertices;
		bvector<ISubEntityPtr> edgeLoopSubEntities;

		IGeometryPtr geomFacesEval;
		CurveVectorPtr curveEdgesEval;
		CurveVectorPtr curveVerticesEval;

		DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();

		size_t nFaces = SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);
		size_t nEdges = SolidUtil::GetBodyEdges(&subEntitiesEdges, entity);
		size_t nVertices = SolidUtil::GetBodyVertices(&subEntitiesVertices, entity);

		//Mesh Polyface converter WORKING REPRESENTATION
#if false
		//mGraphicsProcessorHelper.ProcessAsMeshElement(solidKernelEntity);

		outfile.open(filePath, ios_base::app);
		outfile << "Faceted BREP / ShellBased with Mesh Polyface" << endl;
		outfile << endl;
		outfile.close();

		int boundID = 0;
		int faceParsed = 0;
		for (auto edge : subEntitiesEdges)
		{
			ISubEntityCR edgeRef = *edge;
			EdgeId edgeID;
			SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);
			//Get the faces of the current edge
			SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

			outfile.open(filePath, ios_base::app);
			outfile << "EDGE Sub Entity: " << endl;
			outfile << endl;
			outfile.close();

			BoundPoints* bound = new BoundPoints();
			bound->boundID = boundID;
			bound->isShared = subEntitiesFaces.size() > 1;

			if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
			{
				bound->boundType = curveEdgesEval->GetBoundaryType();
				// Chek if the shape is closed 
				bound->isClosed = false;
				if (curveEdgesEval->IsClosedPath())
					bound->isClosed = true;
				else if (curveEdgesEval->IsPhysicallyClosedPath())
					bound->isClosed = true;

				//Read more:
				//https://communities.bentley.com/products/programming/microstation_programming/f/microstation-programming---forum/193380/c-connect-point-at-distance-along-element/572437#572437
				//15 Sampling Fraction 
				for (double i = 0; i <= 15; i++)
				{
					//fraction 
					double f = i / 15;
					CurveLocationDetail cDetail;

					//Fraction Evaluation of the point on the curve
					if (curveEdgesEval->front()->FractionToPoint(f, cDetail))
					{
						auto vertexPoint = cDetail.point;
						bound->pointsVector.push_back(vertexPoint);
					}

				}
			}

			for (auto face : subEntitiesFaces)
			{
				if (face == NULL)
					continue;

				ISubEntityCR faceRef = *face;
				FaceId faceID;
				SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

				//Set the faceID
				bound->nodeID = faceID.nodeId;
				bound->faceID.push_back((int)faceID.entityId);

				outfile.open(filePath, ios_base::app);
				outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
				outfile << endl;
				outfile.close();

				if (faceParsed < nFaces)
				{
					solidKernelEntity->faceID.push_back((int)faceID.entityId);
					faceParsed++;
				}
			}

			boundID++;

			//Add bound Points
			//solidKernelEntity->addBoundsPoints(bound);
			subEntitiesFaces.clear();
		}
#endif

		//Vertices start dependences BSpline Surface
#if false 
		vector<vector<ShapesGraphicProperties*>> subShapesLoopVec = vector<vector<ShapesGraphicProperties*>>();

		for (auto vertex : subEntitiesVertices)
		{
			ISubEntityCR vertexRef = *vertex;
			VertexId vertexID;
			SolidUtil::TopologyID::IdFromVertex(vertexID, vertexRef, true);
			SolidUtil::Debug::DumpSubEntity(vertexRef, L"DumpSubEntity Vertex");

			//Clear the faces store previously
			subEntitiesFaces.clear();
			subEntitiesEdges.clear();

			//Get the Edges from the Vertex
			SolidUtil::GetVertexEdges(subEntitiesEdges, vertexRef);
			for (auto edge : subEntitiesEdges)
			{
				bool parseEdgeLoop = false;

				ISubEntityCR edgeRef = *edge;
				EdgeId edgeID;
				SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);
				SolidUtil::Debug::DumpSubEntity(edgeRef, L"DumpSubEntity Edge");

				ShapesGraphicProperties* shapesGraphicProperties = nullptr;

				if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
				{
					if (curveEdgesEval->IsClosedPath() || curveEdgesEval->IsPhysicallyClosedPath())
					{
						shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

						outfile.open(filePath, ios_base::app);
						outfile << "-------- EDGE Sub Entity: " << endl;
						outfile << endl;
						outfile.close();

						bool addToDictionary = false;
						mGraphicsProcessorHelper.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties, addToDictionary);

						curveEdgesEval->AreStartEndAlmostEqual();

						DVec3d cDX, cDY, cDZ;

						cDX = shapesGraphicProperties->getVectorAxisX();
						cDY = shapesGraphicProperties->getVectorAxisY();
						cDZ = shapesGraphicProperties->getVectorAxisZ();

						outfile.open(filePath, ios_base::app);
						outfile << endl;
						outfile << "Curve XY Plane: " << endl;
						outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << endl;
						outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << endl;
						outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << endl;
						outfile.close();
					}
					else
						parseEdgeLoop = true;
				}

				//Clear the previous stored faces
				subEntitiesFaces.clear();

				//Get te faces of the current edge
				SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

				vector<ShapesGraphicProperties*> loopVector;

				for (auto face : subEntitiesFaces)
				{
					if (face == NULL)
						continue;

					ISubEntityCR faceRef = *face;
					FaceId faceID;
					SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

					//clear the previous entities loop
					edgeLoopSubEntities.clear();

					//Loop Need to be parsed
					//if (parseEdgeLoop)
					if (shapesGraphicProperties == nullptr)
					{
						bool loopAleadyParsed = false;
						SolidUtil::GetLoopEdgesFromEdge(edgeLoopSubEntities, edgeRef, faceRef);

						//Check if the Loop is already stored and parsed
						CurveVectorPtr loopCheck;
						if (SolidUtil::Convert::SubEntityToCurveVector(loopCheck, (ISubEntityCR)*edgeLoopSubEntities.front()) == SUCCESS)
						{
							DPoint3d startP, endP;
							loopCheck->GetStartEnd(startP, endP);

							for (auto shapeVec : subShapesLoopVec)
							{
								if (!loopAleadyParsed)
								{
									for (auto s : shapeVec)
									{
										if ((s->getStartPoint() == startP) && (s->getEndPoint() == endP))
										{
											loopAleadyParsed = true;
											outfile.open(filePath, ios_base::app);
											outfile << "loopAleadyParsed = true" << endl;
											outfile << endl;
											outfile.close();
											break;
										}
									}
								}
								else
									break;
							}
						}

						//If the loop it was not parsed yet do it
						if (!loopAleadyParsed)
						{
							outfile.open(filePath, ios_base::app);
							outfile << "-------- EDGE LOOP Sub Entities: " << endl;
							outfile << endl;
							outfile.close();

							for (auto edgeLoop : edgeLoopSubEntities)
							{
								ISubEntityCR edgeRefLoop = *edgeLoop;
								CurveVectorPtr loopEval;

								outfile.open(filePath, ios_base::app);
								outfile << endl;
								outfile << "Curve of the loop: " << endl;
								outfile << endl;
								outfile.close();

								shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

								if (SolidUtil::Convert::SubEntityToCurveVector(loopEval, edgeRefLoop) == SUCCESS)
								{
									bool addToDictionary = false;
									mGraphicsProcessorHelper.processShapesCurvesVector(*loopEval, false, &*shapesGraphicProperties, addToDictionary);

									DVec3d cDX, cDY, cDZ;

									cDX = shapesGraphicProperties->getVectorAxisX();
									cDY = shapesGraphicProperties->getVectorAxisY();
									cDZ = shapesGraphicProperties->getVectorAxisZ();

									outfile.open(filePath, ios_base::app);
									outfile << endl;
									outfile << "Curve XY Plane: " << endl;
									outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << endl;
									outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << endl;
									outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << endl;
									outfile.close();

									loopVector.push_back(shapesGraphicProperties);
								}
							}

							subShapesLoopVec.push_back(loopVector);
						}

					}
					//If it's not a loop store the closed shape with face ID and entity ID
					else if (loopVector.empty())
					{
						//Save the faceID to the Curve edge
						shapesGraphicProperties->addFaceBoundID(faceID.entityId);
						shapesGraphicProperties->setNodeId(faceID.nodeId);

						//Add the edge to the Solid Entity
						solidKernelEntity->addFaceBoundaryShape(shapesGraphicProperties);
					}

					//If it's a loop store set to the shapes face ID and entity ID
					if (!loopVector.empty())
					{
						for (auto s : loopVector)
						{
							//Save the faceID to the Curve edge
							s->addFaceBoundID(faceID.entityId);
							s->setNodeId(faceID.nodeId);
						}
					}

					outfile.open(filePath, ios_base::app);
					outfile << "FACE of the Edge: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
					outfile << endl;
					outfile.close();
				}

				//If it's a loop store it in the Solid Entity
				if (!loopVector.empty())
				{
					//Add the Loop to the Solid Entity
					solidKernelEntity->loopShapesBounds.push_back(loopVector);
				}
			}
		}

		//Clear the previous stored faces
		subEntitiesFaces.clear();
		SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);

		for (auto face : subEntitiesFaces)
		{
			if (face == NULL)
				continue;

			ISubEntityCR faceRef = *face;
			FaceId faceID;
			SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

			outfile.open(filePath, ios_base::app);
			outfile << "--------- FACE Entity: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
			outfile << endl;
			outfile.close();

			if (SolidUtil::Convert::SubEntityToGeometry(geomFacesEval, faceRef, *dgnModelRef) == SUCCESS)
			{
				switch (geomFacesEval->GetGeometryType())
				{
				case IGeometry::GeometryType::BsplineSurface:
				{
					MSBsplineSurfaceCR msBspline = *geomFacesEval->GetAsMSBsplineSurface();
					MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();

					//msBsplineSurfaceGraphicProperties->setFaceId(faceID);
					msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
					msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

					mGraphicsProcessorHelper.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

					//Add the face to the solidKernelEntity
					solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
				}
				break;
				case IGeometry::GeometryType::SolidPrimitive:
				{
					outfile.open(filePath, ios_base::app);
					outfile << "---------------- IGeometry::GeometryType::SolidPrimitive ----------------" << endl;
					outfile << endl;
					outfile.close();
					ISolidPrimitiveR  prim = *geomFacesEval->GetAsISolidPrimitive();
					_ProcessSolidPrimitive(prim);
				}
				break;
				default:
					break;
				}
			}
		}

#endif

		//Faces start dependences BSpline Surface WORKS
#if true
		for (auto face : subEntitiesFaces)
		{
			if (face == NULL)
				continue;

			ISubEntityCR faceRef = *face;
			FaceId faceID;
			SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

			this->_modelerDataWriterManager->writeTitleProcessDataToFile("FACE");
			this->_modelerDataWriterManager->writeTupleDataToFile<uint32_t>("Entity", faceID.nodeId);
			this->_modelerDataWriterManager->writeTupleDataToFile<uint32_t>("ID", faceID.entityId);

			if (SolidUtil::Convert::SubEntityToGeometry(geomFacesEval, faceRef, *dgnModelRef) == SUCCESS)
			{
				switch (geomFacesEval->GetGeometryType())
				{
				case IGeometry::GeometryType::BsplineSurface:
				{
					MSBsplineSurfaceCR msBspline = *geomFacesEval->GetAsMSBsplineSurface();
					MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();

					msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
					msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);
					msBsplineSurfaceGraphicProperties->geometryType = IGeometry::GeometryType::BsplineSurface;

					bool addToDictionary = false;
					processMSBsplineSurface(msBspline, *&msBsplineSurfaceGraphicProperties, addToDictionary);

					//Add the face to the solidKernelEntity
					solidKernelEntity->addSolidOrSurfaceFace((GraphicProperties*&)msBsplineSurfaceGraphicProperties);
				}
				break;
				case IGeometry::GeometryType::SolidPrimitive:
				{
					ISolidPrimitiveR  prim = *geomFacesEval->GetAsISolidPrimitive();
					bool addToDictionary = false;

					//Add the face to the solidKernelEntity					
					GraphicProperties* primitiveGraphicProperties = processSolidPrimitives(prim, addToDictionary);

					if (primitiveGraphicProperties != nullptr)
					{
						primitiveGraphicProperties->geometryType = IGeometry::GeometryType::SolidPrimitive;

						solidKernelEntity->addSolidOrSurfaceFace((GraphicProperties*&)primitiveGraphicProperties);
					}
				}
				break;
				case IGeometry::GeometryType::Polyface:
				{
					PolyfaceHeaderPtr polyF = geomFacesEval->GetAsPolyfaceHeader();
					bvector<PolyfaceHeaderPtr> meshes;
					meshes.push_back(polyF);

					SolidEntityGraphicProperties* solidTriangles = new SolidEntityGraphicProperties();
					solidTriangles->meshProcessing = true;
					solidTriangles->setBRepTypeEnum(0);

					solidTriangles->geometryType = IGeometry::GeometryType::Polyface;

					processElementAsMesh(solidTriangles, meshes);

					solidKernelEntity->addSolidOrSurfaceFace((GraphicProperties*&)solidTriangles);
				}
				break;
				
				case IGeometry::GeometryType::CurveVector:
				{
					ShapesGraphicProperties* shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);
					
					shapesGraphicProperties->geometryType = IGeometry::GeometryType::CurveVector;

					bool addToDictionary = false;

					CurveVectorPtr curveVec = geomFacesEval->GetAsCurveVector();
					
					processShapesCurvesVector(*curveVec, false, &*shapesGraphicProperties, addToDictionary);

					solidKernelEntity->addSolidOrSurfaceFace((GraphicProperties*&)shapesGraphicProperties);
				}
				break;
				
				default:
					break;
				}
			}
		}
#endif

		//Edges start dependences BSpline Surface 
#if false
		//Clear the faces store previously
		subEntitiesFaces.clear();
		subEntitiesVertices.clear();

		vector<vector<ShapesGraphicProperties*>> subShapesLoopVec = vector<vector<ShapesGraphicProperties*>>();
		for (auto edge : subEntitiesEdges)
		{
			bool parseEdgeLoop = false;

			ISubEntityCR edgeRef = *edge;
			EdgeId edgeID;
			SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);
			SolidUtil::Debug::DumpSubEntity(edgeRef, L"DumpSubEntity Edge");

			ShapesGraphicProperties* shapesGraphicProperties = nullptr;

			if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
			{
				if (curveEdgesEval->IsClosedPath() || curveEdgesEval->IsPhysicallyClosedPath())
				{
					shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

					outfile.open(filePath, ios_base::app);
					outfile << "-------- EDGE Sub Entity: " << endl;
					outfile << endl;
					outfile.close();

					bool addToDictionary = false;
					mGraphicsProcessorHelper.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties, addToDictionary);

					//ADD ???
					//curveEdgesEval->FixupXYOuterInner(true);

					curveEdgesEval->AreStartEndAlmostEqual();

					DVec3d cDX, cDY, cDZ;

					cDX = shapesGraphicProperties->getVectorAxisX();
					cDY = shapesGraphicProperties->getVectorAxisY();
					cDZ = shapesGraphicProperties->getVectorAxisZ();

					outfile.open(filePath, ios_base::app);
					outfile << endl;
					outfile << "Curve XY Plane: " << endl;
					outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << endl;
					outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << endl;
					outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << endl;
					outfile.close();
				}
				else
					parseEdgeLoop = true;
			}

			//Clear the previous stored faces
			subEntitiesFaces.clear();

			//Get te faces of the current edge
			SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

			vector<ShapesGraphicProperties*> loopVector;

			for (auto face : subEntitiesFaces)
			{
				if (face == NULL)
					continue;

				ISubEntityCR faceRef = *face;
				FaceId faceID;
				SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

				//clear the previous entities loop
				edgeLoopSubEntities.clear();

				//Loop Need to be parsed
				//if (parseEdgeLoop)
				if (shapesGraphicProperties == nullptr)
				{
					bool loopAleadyParsed = false;
					SolidUtil::GetLoopEdgesFromEdge(edgeLoopSubEntities, edgeRef, faceRef);

					//Check if the Loop is already stored and parsed
					CurveVectorPtr loopCheck;
					if (SolidUtil::Convert::SubEntityToCurveVector(loopCheck, (ISubEntityCR)*edgeLoopSubEntities.front()) == SUCCESS)
					{
						DPoint3d startP, endP;
						loopCheck->GetStartEnd(startP, endP);

						for (auto shapeVec : subShapesLoopVec)
						{
							if (!loopAleadyParsed)
							{
								for (auto s : shapeVec)
								{
									if ((s->getStartPoint() == startP) && (s->getEndPoint() == endP))
									{
										loopAleadyParsed = true;
										outfile.open(filePath, ios_base::app);
										outfile << "loopAleadyParsed = true" << endl;
										outfile << endl;
										outfile.close();
										break;
									}
								}
							}
							else
								break;
						}
					}

					//If the loop it was not parsed yet do it
					if (!loopAleadyParsed)
					{
						outfile.open(filePath, ios_base::app);
						outfile << "-------- EDGE LOOP Sub Entities: " << endl;
						outfile << endl;
						outfile.close();

						for (auto edgeLoop : edgeLoopSubEntities)
						{
							ISubEntityCR edgeRefLoop = *edgeLoop;
							CurveVectorPtr loopEval;

							outfile.open(filePath, ios_base::app);
							outfile << endl;
							outfile << "Curve of the loop: " << endl;
							outfile << endl;
							outfile.close();

							shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

							if (SolidUtil::Convert::SubEntityToCurveVector(loopEval, edgeRefLoop) == SUCCESS)
							{
								//ADD ???
								//loopEval->FixupXYOuterInner(true);

								bool addToDictionary = false;
								mGraphicsProcessorHelper.processShapesCurvesVector(*loopEval, false, &*shapesGraphicProperties, addToDictionary);

								DVec3d cDX, cDY, cDZ;

								cDX = shapesGraphicProperties->getVectorAxisX();
								cDY = shapesGraphicProperties->getVectorAxisY();
								cDZ = shapesGraphicProperties->getVectorAxisZ();

								outfile.open(filePath, ios_base::app);
								outfile << endl;
								outfile << "Curve XY Plane: " << endl;
								outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << endl;
								outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << endl;
								outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << endl;
								outfile.close();

								loopVector.push_back(shapesGraphicProperties);
							}
						}

						subShapesLoopVec.push_back(loopVector);
						/*if (!loopVector.empty())
						{
						subShapesLoopVec.push_back(loopVector);
						}*/
					}

				}
				//If it's not a loop store the closed shape with face ID and entity ID
				else if (loopVector.empty())
				{
					//Save the faceID to the Curve edge
					shapesGraphicProperties->addFaceBoundID(faceID.entityId);
					shapesGraphicProperties->setNodeId(faceID.nodeId);

					//Add the edge to the Solid Entity
					solidKernelEntity->addFaceBoundaryShape(shapesGraphicProperties);
				}

				//If it's a loop store set to the shapes face ID and entity ID
				if (!loopVector.empty())
				{
					for (auto s : loopVector)
					{
						//Save the faceID to the Curve edge
						s->addFaceBoundID(faceID.entityId);
						s->setNodeId(faceID.nodeId);
					}
				}

				outfile.open(filePath, ios_base::app);
				outfile << "FACE of the Edge: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
				outfile << endl;
				outfile.close();
			}

			//If it's a loop store it in the Solid Entity
			if (!loopVector.empty())
			{
				//Add the Loop to the Solid Entity
				solidKernelEntity->loopShapesBounds.push_back(loopVector);
			}
		}

		//Clear the previous stored faces
		subEntitiesFaces.clear();
		SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);

		for (auto face : subEntitiesFaces)
		{
			if (face == NULL)
				continue;

			ISubEntityCR faceRef = *face;
			FaceId faceID;
			SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

			outfile.open(filePath, ios_base::app);
			outfile << "--------- FACE Entity: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
			outfile << endl;
			outfile.close();

			if (SolidUtil::Convert::SubEntityToGeometry(geomFacesEval, faceRef, *dgnModelRef) == SUCCESS)
			{
				switch (geomFacesEval->GetGeometryType())
				{
				case IGeometry::GeometryType::BsplineSurface:
				{
					MSBsplineSurfaceCR msBspline = *geomFacesEval->GetAsMSBsplineSurface();
					MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();

					//msBsplineSurfaceGraphicProperties->setFaceId(faceID);
					msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
					msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

					mGraphicsProcessorHelper.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

					//Add the face to the solidKernelEntity
					solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
				}
				break;
				case IGeometry::GeometryType::SolidPrimitive:
				{
					outfile.open(filePath, ios_base::app);
					outfile << "---------------- IGeometry::GeometryType::SolidPrimitive ----------------" << endl;
					outfile << endl;
					outfile.close();
					ISolidPrimitiveR  prim = *geomFacesEval->GetAsISolidPrimitive();
					_ProcessSolidPrimitive(prim);
				}
				break;
				default:
					break;
				}
			}
		}

#endif

		//Edges BOUNDS start dependences 
#if false
		//Clear the faces store previously
		subEntitiesFaces.clear();
		subEntitiesVertices.clear();

		int facesCreated = 0;
		int vertexCreated = 0;

		int boundID = 0;
		for (auto edge : subEntitiesEdges)
		{

			ISubEntityCR edgeRef = *edge;
			EdgeId edgeID;
			SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);
			SolidUtil::Debug::DumpSubEntity(edgeRef, L"DumpSubEntity Edge");
			//Get te faces of the current edge
			SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);


			outfile.open(filePath, ios_base::app);
			outfile << "EDGE Sub Entity: " << endl;
			outfile << endl;
			outfile.close();

			BoundPoints* bound = new BoundPoints();
			bound->boundID = boundID;
			bound->isShared = subEntitiesFaces.size() > 1;

			if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
			{
				// Chek if the shape is closed 
				bound->isClosed = false;
				if (curveEdgesEval->IsClosedPath())
					bound->isClosed = true;
				else if (curveEdgesEval->IsPhysicallyClosedPath())
					bound->isClosed = true;

				for (double i = 0; i <= 20; i++)
				{

					double f = i / 20;
					CurveLocationDetail cDetail;

					if (curveEdgesEval->front()->FractionToPoint(f, cDetail))
					{
						auto vertexPoint = cDetail.point;
						bound->pointsVector.push_back(vertexPoint);

						//[SHARED]
						if (bound->isShared)
						{
							outfile.open(filePath, ios_base::app, sizeof(string));
							outfile << "Point [X]: " << vertexPoint.x << endl;
							outfile << "Point [Y]: " << vertexPoint.y << endl;
							outfile << "Point [Z]: " << vertexPoint.z << endl;
							outfile << endl;
							outfile.close();
						}
					}

				}
			}

			for (auto face : subEntitiesFaces)
			{
				if (face == NULL)
					continue;

				ISubEntityCR faceRef = *face;
				FaceId faceID;
				SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

				outfile.open(filePath, ios_base::app);
				outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << endl;
				outfile << endl;
				outfile.close();

				bound->nodeID = faceID.nodeId;
				bound->faceID.push_back((int)faceID.entityId);

				if (SolidUtil::Convert::SubEntityToGeometry(geomFacesEval, faceRef, *dgnModelRef) == SUCCESS)
				{
					if (facesCreated < nFaces)
					{
						switch (geomFacesEval->GetGeometryType())
						{
						case IGeometry::GeometryType::BsplineSurface:
						{
							MSBsplineSurfaceCR msBspline = *geomFacesEval->GetAsMSBsplineSurface();

							MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();

							msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
							msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

							mGraphicsProcessorHelper.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

							//Add the face to the solidKernelEntity
							solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
						}
						break;
						case IGeometry::GeometryType::SolidPrimitive:
						{
							ISolidPrimitiveR  prim = *geomFacesEval->GetAsISolidPrimitive();
							_ProcessSolidPrimitive(prim);
						}
						break;
						default:
							break;
						}

						facesCreated++;

						SolidUtil::GetFaceVertices(subEntitiesVertices, faceRef);
						for (auto vertex : subEntitiesVertices)
						{
							ISubEntityCR vertexRef = *vertex;
							VertexId vertexID;
							SolidUtil::TopologyID::IdFromVertex(vertexID, vertexRef, true);

							DPoint3d vertexPoint;
							if (SolidUtil::EvaluateVertex(vertexRef, vertexPoint) == SUCCESS)
							{
								outfile.open(filePath, ios_base::app, sizeof(string));
								outfile << "Vertex Point [X]: " << vertexPoint.x << endl;
								outfile << "Vertex Point [Y]: " << vertexPoint.y << endl;
								outfile << "Vertex Point [Z]: " << vertexPoint.z << endl;
								outfile << endl;
								outfile.close();

								if (vertexCreated < nVertices)
								{
									solidKernelEntity->mVertexLoop.push_back(vertexPoint);
									vertexCreated++;
								}
							}

						}

						//Clear the previous vertices
						subEntitiesVertices.clear();
					}
				}
			}
			//Clear the previous stored faces
			subEntitiesFaces.clear();
			boundID++;

			//[SHARED]
			if (bound->isShared)
				//Add bound Points
				solidKernelEntity->addBoundsPoints(bound);
		}
#endif

		subEntitiesEdges.clear();
		subEntitiesFaces.clear();
		subEntitiesVertices.clear();

	}

#pragma endregion	

#pragma region MESH_TRIANGLES

	else if (meshProcessing)
	{
		IFacetOptionsPtr facetOptions = IFacetOptions::New();

		//Set different parameters for facet.
		facetOptions->SetIgnoreFaceMaterialAttachments(true); // Don't separate multi-symbology BReps by face symbology...
		facetOptions->SetChordTolerance(0.0);                 //many different parameters to control the final result mesh
		facetOptions->SetAngleTolerance(0.0);
		facetOptions->SetMaxEdgeLength(0.0);
		facetOptions->SetMaxFacetWidth(0.0);
		facetOptions->SetNormalsRequired(false);
		facetOptions->SetParamsRequired(false);
		facetOptions->SetMaxPerFace(4);
		facetOptions->SetCurvedSurfaceMaxPerFace(4);
		facetOptions->SetEdgeHiding(true);
		facetOptions->SetSmoothTriangleFlowRequired(true);

		bvector<PolyfaceHeaderPtr> meshes;

		if (true == ElementToApproximateFacets(this->_currentElementHandle, meshes, facetOptions.get()))
			bool elementProcessed = processElementAsMesh(*&solidKernelEntity, meshes);
	}

#pragma endregion

	this->getElementBundle()->setGraphicProperties(*solidKernelEntity);	
}

bool GraphicsProcessorHelper::processPolyfaceFacets(PolyfaceQueryCR meshData, bool isFilled, Transform currentTransform)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	this->_modelerDataWriterManager->writeTitleProcessDataToFile("PolyfaceQueryCR - meshData");

	bvector<PolyfaceHeaderPtr> meshes;
	PolyfaceHeaderPtr header = PolyfaceHeader::CreateVariableSizeIndexed();
	header->CopyFrom(meshData);
	header->Transform(currentTransform);
	meshes.push_back(header);

	SolidEntityGraphicProperties* solidKernelEntity = new SolidEntityGraphicProperties();
	solidKernelEntity->meshProcessing = true;
	solidKernelEntity->setBRepTypeEnum(0);

	bool elementProcessed = processElementAsMesh(*&solidKernelEntity, meshes);

	this->getElementBundle()->setGraphicProperties(*solidKernelEntity);

	return elementProcessed;
}

bool GraphicsProcessorHelper::processElementAsMesh(SolidEntityGraphicProperties*& solidKernelEntity, bvector<PolyfaceHeaderPtr> meshes)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	this->_modelerDataWriterManager->writeTitleProcessDataToFile("processElementAsMesh");

	for (size_t i = 0; i < meshes.size(); i++)
	{
		MeshTriangles* meshT = new MeshTriangles();

		//size_t numOpen, numClosed;
		size_t numVertex, numFacet, numQuad, numTriangle, numImplicitTriangle, numVisEdges, numInvEdges;
		PolyfaceHeaderPtr pMesh = meshes.at(i);
		PolyfaceVisitorPtr pv = PolyfaceVisitor::Attach(*pMesh);
			
		pMesh->CollectCounts(numVertex, numFacet, numQuad, numTriangle, numImplicitTriangle, numVisEdges, numInvEdges);

		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("Mesh Number", i);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numVertex", numVertex);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numFacet", numFacet);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numQuad", numQuad);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numTriangle", numTriangle);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numImplicitTriangle", numImplicitTriangle);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numVisEdges", numVisEdges);
		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("numInvEdges", numInvEdges);

		int nFace = 1;

		while (pv->AdvanceToNextFace())
		{
			BlockedVectorDPoint3dR pts = pv->Point();

			vector<DPoint3d> face;
			for (DPoint3d pt : pts)
			{
				//Store the point for the triangle face
				face.push_back(pt);
			}

			//Push the face in the container
			meshT->facesTriangulatedVector.push_back(face);

			nFace++;
		}

		this->_modelerDataWriterManager->writeTupleDataToFile<size_t>("Num Of Facet", nFace);

		//Add to the BRep Entity
		solidKernelEntity->addMeshTriangulated(meshT);
	}
	
	return true;
}

bool GraphicsProcessorHelper::ElementToApproximateFacets(ElementHandleCR source,bvector<PolyfaceHeaderPtr> &output,IFacetOptionsP options)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

	output.clear();
	MeshProcessor dest(output, options);
	ElementGraphicsOutput::Process(source, dest);
	return output.size() > 0 ? true : false;
}

ElementHandle GraphicsProcessorHelper::getCurrentElementHandle()
{
	return this->_currentElementHandle;
}

void GraphicsProcessorHelper::setElementHandle(ElementHandle elementHandle)
{
	this->_currentElementHandle = elementHandle;
}

