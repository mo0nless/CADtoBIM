#include "../headers/GraphicsProcessorEnhancer.h"


GraphicsProcessorEnhancer::GraphicsProcessorEnhancer()
{
	filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	//filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
}

void GraphicsProcessorEnhancer::setDictionaryProperties(DictionaryProperties& newDictionaryProperties)
{
	this->pDictionaryProperties = &newDictionaryProperties;
}

DictionaryProperties* GraphicsProcessorEnhancer::getDictionaryProperties()
{
	return this->pDictionaryProperties;
}

bool GraphicsProcessorEnhancer::isDoubleEqual(double x, double y)
{
	/* some small number such as 1e-5 */
	const double epsilon = 1e-5;
	return std::abs(x - y) <= epsilon * std::abs(x);
	// see Knuth section 4.2.2 pages 217-218
}

void GraphicsProcessorEnhancer::PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties)
{
	std::ofstream outfile;
	double area, volume;
	DVec3d centroid;
	RotMatrix axes;
	DVec3d momentxyz;

	primitive.ComputePrincipalAreaMoments(area, centroid, axes, momentxyz);

	// set the centroid values from here, because in the function bellow sometimes is 0
	GraphicProperties->setCentroid(centroid);
	GraphicProperties->setArea(area);

	outfile.open(filePath, std::ios_base::app);

	outfile << std::fixed;
	outfile << std::endl;
	outfile << "Centroid1 [X] = " << centroid.x << std::endl;
	outfile << "Centroid1 [Y] = " << centroid.y << std::endl;
	outfile << "Centroid1 [Z] = " << centroid.z << std::endl;
	outfile << "Area1 = " << area << std::endl;

	outfile << std::endl;


	primitive.ComputePrincipalMoments(volume, centroid, axes, momentxyz);
	GraphicProperties->setVolume(volume);

	outfile << "Centroid2 [X] = " << centroid.x << std::endl;
	outfile << "Centroid2 [Y] = " << centroid.y << std::endl;
	outfile << "Centroid2 [Z] = " << centroid.z << std::endl;
	outfile << "Volume = " << volume << std::endl;
	outfile << "Area2 = " << area << std::endl;
	outfile << std::endl;

	outfile.close();

}

void GraphicsProcessorEnhancer::setGraphicPropertiesAxes(GraphicProperties*& graphicProperties, Transform& localToWorld)
{
	DVec3d columnVectorX, columnVectorY, columnVectorZ;

	localToWorld.GetMatrixColumn(columnVectorX, 0);
	localToWorld.GetMatrixColumn(columnVectorY, 1);
	localToWorld.GetMatrixColumn(columnVectorZ, 2);

	graphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
}

void GraphicsProcessorEnhancer::PrintPrincipalProperties(DRange3d& range, DVec3d& vectorRotation, DPoint4d& qRotation, Transform& localToWorld)
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);

	outfile << std::fixed;
	outfile << "Range [XLength] = " << range.XLength() << std::endl;
	outfile << "Range [YLength] = " << range.YLength() << std::endl;
	outfile << "Range [ZLength] = " << range.ZLength() << std::endl;
	outfile << std::endl;

	outfile << "Quaternion Rotation" << std::endl;
	outfile << "qRotation [X] = " << qRotation.x << std::endl;
	outfile << "qRotation [Y] = " << qRotation.y << std::endl;
	outfile << "qRotation [Z] = " << qRotation.z << std::endl;
	outfile << "qRotation [W] = " << qRotation.w << std::endl;
	outfile << std::endl;

	outfile << "Vector Rotation Axis Local to World" << std::endl;
	outfile << "vRotation [X] = " << vectorRotation.x << std::endl;
	outfile << "vRotation [Y] = " << vectorRotation.y << std::endl;
	outfile << "vRotation [Z] = " << vectorRotation.z << std::endl;
	outfile << std::endl;

	outfile << "Origin [X] = " << localToWorld.Origin().x << std::endl;
	outfile << "Origin [Y] = " << localToWorld.Origin().y << std::endl;
	outfile << "Origin [Z] = " << localToWorld.Origin().z << std::endl;

	outfile << std::endl;

	outfile.close();
}

void GraphicsProcessorEnhancer::setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& boxGraphicProperties)
{
	// TODO to be removed
	// write to file the type of solide which was parsed
	//std::ofstream outfile;
	//outfile.open(filePath, std::ios_base::app);
	//outfile << std::fixed;
	//outfile << std::endl;
	//outfile << " BOX "<< std::endl;
	//outfile << std::endl;

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

	// add box graphic property to dictionary
	pDictionaryProperties->addGraphicProperties(boxGraphicProperties);
}

void GraphicsProcessorEnhancer::setConeGraphicProperties(DgnConeDetail cgnConeDetail,ConeGraphicProperties*& coneGraphicProperties)
{
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
	// add property to the dictionary
	this->pDictionaryProperties->addGraphicProperties(coneGraphicProperties);

}

void GraphicsProcessorEnhancer::setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties *& cylinderGraphicProperties)
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

	// add property to the dictionary
	this->pDictionaryProperties->addGraphicProperties(cylinderGraphicProperties);

}

void GraphicsProcessorEnhancer::setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties)
{
	// TODO to enable if needed, but to be removed at the end
	//std::ofstream outfile;
	//outfile.open(filePath, std::ios_base::app);
	//outfile << std::fixed;
	//outfile << std::endl;
	//outfile << " Sphere " << std::endl;
	//outfile << std::endl;

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
	pDictionaryProperties->addGraphicProperties(sphereGraphicProperties);

}

void GraphicsProcessorEnhancer::setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties)
{
	// TODO to be enabled if needed, remove at the end
	//std::ofstream outfile;
	//outfile.open(filePath, std::ios_base::app);
	//outfile << std::fixed;
	//outfile << std::endl;
	//outfile << " Torus " << std::endl;
	//outfile << std::endl;

	// set torus properties
	torusGraphicProperties->setCenterPointOfRotation(centerOfRotation);
	torusGraphicProperties->setMinorRadius(dgnTorusPipeDetail.m_minorRadius);
	torusGraphicProperties->setMajorRadius(dgnTorusPipeDetail.m_majorRadius);
	torusGraphicProperties->setSweepRadians(sweepRadians);



	// add torus property to the dictionary
	pDictionaryProperties->addGraphicProperties(torusGraphicProperties);

}

void GraphicsProcessorEnhancer::processConeAndCylinder(ISolidPrimitiveCR& primitive)
{
	std::ofstream outfile;

	DgnConeDetail dgnConeDetail;
	Transform localToWorld;
	Transform worldToLocal;

	primitive.TryGetDgnConeDetail(dgnConeDetail);
	//dgnConeDetail.TryGetConstructiveFrame(localToWorld, worldToLocal);

	double rA, rB;
	bool centerOfTheConeInB;
	
	//Try to set up a nonsingular coordinate frame. Returns false if centerB is in base plane !!!!
	centerOfTheConeInB = dgnConeDetail.GetTransforms(localToWorld, worldToLocal, rA, rB);

	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;
	outfile << std::endl;
	outfile << "THIS IS A CONE: " << std::endl;
	outfile << "Try to set up a nonsingular coordinate frame. Returns false if centerB is in base plane !!!! " << std::endl;
	outfile << "CenterB is in base plane: " << centerOfTheConeInB << std::endl;
	outfile << std::endl;
	outfile << std::endl;
	outfile.close();

	if (isDoubleEqual(dgnConeDetail.m_radiusA, dgnConeDetail.m_radiusB) && dgnConeDetail.m_radiusA > 0)
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cylinder " << std::endl;
		outfile << std::endl;
		outfile.close();

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		
		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)cylinderGraphicProperties);
		setGraphicPropertiesAxes((GraphicProperties*&)cylinderGraphicProperties, localToWorld);
		setCylinderGraphicProperties(dgnConeDetail, cylinderGraphicProperties);

	}
	else if (dgnConeDetail.m_radiusB == 0)
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cone " << std::endl;
		outfile << std::endl;
		outfile.close();


		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::CONE);

		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)coneGraphicProperties);
		setGraphicPropertiesAxes((GraphicProperties*&)coneGraphicProperties, localToWorld);
		setConeGraphicProperties(dgnConeDetail, coneGraphicProperties);
	}
	else if (dgnConeDetail.m_radiusB > 0 && !isDoubleEqual(dgnConeDetail.m_radiusA, dgnConeDetail.m_radiusB))
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Truncated cone " << std::endl;
		outfile << std::endl;
		outfile.close();

		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::TRUNCATED_CONE);

		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)coneGraphicProperties);
		setGraphicPropertiesAxes((GraphicProperties*&)coneGraphicProperties, localToWorld);
		setConeGraphicProperties(dgnConeDetail, coneGraphicProperties);
	}

}


void GraphicsProcessorEnhancer::processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties)
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << "-------- MSBsplineSurfaceCR msBsplineSurface --------" << std::endl;
	outfile.close();

	int numOfBounds;
	double uOrder, vOrder;
	size_t uIntervals, vIntervals, lowAindex, highAindex;
	bvector<double> vKnots, uKnots, vKnotsCompressed, uKnotsCompressed;
	bvector<size_t> vKmultiplicity, uKmultiplicity;
	bvector<bvector<DPoint2d>> boundaryUVLoops;

	std::vector<std::vector<DPoint3d>> controlPointsUV;
	std::vector<std::vector<double>> weights;

	msBsplineSurface.GetIntervalCounts(uIntervals, vIntervals);
	numOfBounds = msBsplineSurface.GetIntNumBounds();

	uOrder = msBsplineSurface.GetIntUOrder();
	vOrder = msBsplineSurface.GetIntVOrder();
		
	//Get the UV Poles control points of the surface
	int count = 0;
	for (size_t i = 0; i < msBsplineSurface.GetIntNumUPoles(); i++)
	{
		std::vector<DPoint3d> tempCP;
		std::vector<double> tempW;
		for (size_t j = 0; j < msBsplineSurface.GetIntNumVPoles(); j++)
		{
			tempW.push_back(msBsplineSurface.GetWeight(i, j));
			tempCP.push_back(msBsplineSurface.GetPole(i, j));
			count++;
		}
		controlPointsUV.push_back(tempCP);
		weights.push_back(tempW);
	}

	//msBsplineSurface.EvaluatePointAndUnitNormal();
	msBsplineSurface.GetVKnots(vKnots);
	msBsplineSurface.GetUKnots(uKnots);

	//Extract the multiplicity compressing the UV Knots
	MSBsplineCurve::CompressKnots(vKnots, vOrder, vKnotsCompressed, vKmultiplicity, lowAindex, highAindex);
	MSBsplineCurve::CompressKnots(uKnots, uOrder, uKnotsCompressed, uKmultiplicity, lowAindex, highAindex);
	
	outfile.open(filePath, std::ios_base::app);
	outfile << "Number of Bounds: " << numOfBounds << std::endl;
	outfile << "Total number of Poles: " << msBsplineSurface.GetNumPoles() << std::endl;
	outfile << "U number of Poles: " << msBsplineSurface.GetIntNumUPoles() << std::endl;
	outfile << "V number of Poles: " << msBsplineSurface.GetIntNumVPoles() << std::endl;
	outfile << "Stored number of UV Poles: " << count << std::endl;
	outfile << std::endl;
	outfile.close();

#if true
	//This function returns a parity regions
	CurveVectorPtr curveVecBound = msBsplineSurface.GetUVBoundaryCurves(true, true);

	// Curve Shape for Boundaries
	CurvesShapesGraphicProperties* shapesGraphicProperties = new CurvesShapesGraphicProperties();
	processShapesCurvesVector(*curveVecBound, false, &*shapesGraphicProperties);

	//Save the faceID to Parity Region
	shapesGraphicProperties->setFaceBoundID(msBsplineSurfaceGraphicProperties->getFaceId());
	shapesGraphicProperties->setNodeId(msBsplineSurfaceGraphicProperties->getNodeId());

	//Parity Region Container
	if (shapesGraphicProperties->hasShapesGraphicsContainer())
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << "-------- PARITY REGION Boundaries --------" << std::endl;
		outfile.close();

		// Outer, Inner Boundaries NB: the path is supposed to be always closed
		for (auto boundary : shapesGraphicProperties->getShapesGraphicsContainer())
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "Bound -------- " << std::endl;
			outfile << std::endl;
			outfile.close();

			//Save the faceID to the Outer/Inner boundary
			boundary->setFaceBoundID(msBsplineSurfaceGraphicProperties->getFaceId());
			boundary->setNodeId(msBsplineSurfaceGraphicProperties->getNodeId());

			// Primitives curves that compose the boundary (UV coordinates as control points)
			for (auto bSpline : boundary->getCurvesPrimitivesContainerVector())
			{
				outfile.open(filePath, std::ios_base::app);
				outfile << "Curve -------- " << std::endl;
				outfile << std::endl;
				outfile.close();

				// Evaluation of the Control Points using the surface
				bvector<DPoint3d> controlPointsBound;
				for (auto uv : bSpline->getControlPoints())
				{
					DPoint3d evalP;
					msBsplineSurface.EvaluatePoint(evalP, uv.x, uv.y);
					controlPointsBound.push_back(evalP);

					outfile.open(filePath, std::ios_base::app, sizeof(std::string));
					outfile << "point " << " [X] = " << evalP.x << std::endl;
					outfile << "point " << " [Y] = " << evalP.y << std::endl;
					outfile << "point " << " [Z] = " << evalP.z << std::endl;
					outfile << std::endl;
					outfile.close();
				}
				outfile.close();

				//Reset the evaluated Control Points
				bSpline->setControlPoints(controlPointsBound);
			}
		}
	}

#endif

//DPoint3d PolyLoop Evaluation MDL
#if false
	std::vector<std::vector<DPoint3d>> UVBoundsP;
	for (int i = 0; i<msBsplineSurface.numBounds; i++)
	{
		std::vector<DPoint3d> bound;
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


	std::vector<std::vector<DPoint3d>> boundsVectorPoints;
	msBsplineSurface.GetUVBoundaryLoops(boundaryUVLoops, true);

	//Points Loop of the boundaries
	for (auto b : boundaryUVLoops)
	{
		/*outfile.open(filePath, std::ios_base::app);
		outfile << "-------- Points UV Boundary --------" << std::endl;
		outfile.close();*/

		std::vector<DPoint3d> bound;
		for (auto uv : b)
		{
			DPoint3d evalP;
			msBsplineSurface.EvaluatePoint(evalP, uv.x, uv.y);
			bound.push_back(evalP);
		}

		boundsVectorPoints.push_back(bound);
	}

	msBsplineSurfaceGraphicProperties->setUVIsClosed(msBsplineSurface.GetIsUClosed(), msBsplineSurface.GetIsVClosed());
	msBsplineSurfaceGraphicProperties->setUVKnots(uKnots, vKnots);
	msBsplineSurfaceGraphicProperties->setUVKnotsMultiplicity(uKmultiplicity, vKmultiplicity);
	msBsplineSurfaceGraphicProperties->setUVOrder(uOrder, vOrder);
	msBsplineSurfaceGraphicProperties->setWeights(weights);
	msBsplineSurfaceGraphicProperties->setControlPoints(controlPointsUV, msBsplineSurface.GetIntNumUPoles(), msBsplineSurface.GetIntNumVPoles());
	msBsplineSurfaceGraphicProperties->setBoundsVectorPoints(boundsVectorPoints);
}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
void GraphicsProcessorEnhancer::processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties)
{
	std::ofstream outfile;
	
	outfile.open(filePath, std::ios_base::app, sizeof(std::string));
	outfile << "                              " << std::endl;
	outfile << std::fixed;
	outfile.close();


	for each (ICurvePrimitivePtr curvePrimitive in curvesVector)
	{
		switch (curvePrimitive->GetCurvePrimitiveType())
		{
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
		{
			AkimaGraphicProperties* curveGraphicProperties = new AkimaGraphicProperties();

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_AkimaCurve --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curvePrimitive->GetAkimaCurveCP() != nullptr)
			{
				outfile.open(filePath, std::ios_base::app, sizeof(std::string));

				for (size_t k = 0; k < curvePrimitive->GetAkimaCurveCP()->size(); k++)
				{
					outfile << "point " << k << " [X] = " << curvePrimitive->GetAkimaCurveCP()->at(k).x << std::endl;
					outfile << "point " << k << " [Y] = " << curvePrimitive->GetAkimaCurveCP()->at(k).y << std::endl;
					outfile << "point " << k << " [Z] = " << curvePrimitive->GetAkimaCurveCP()->at(k).z << std::endl;
					outfile << std::endl;
				}

				outfile.close();

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

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_Arc --------" << std::endl;
			outfile << "Is Circular: " << ellipse.IsCircular() << std::endl;
			outfile << "Is Ellipse: " << ellipse.IsFullEllipse() << std::endl;
			outfile << std::endl;

			outfile << "Start Point [X]: " << startP.x << std::endl;
			outfile << "Start Point [Y]: " << startP.y << std::endl;
			outfile << "Start Point [Z]: " << startP.z << std::endl;
			outfile << std::endl;

			outfile << "End Point [X]: " << endP.x << std::endl;
			outfile << "End Point [Y]: " << endP.y << std::endl;
			outfile << "End Point [Z]: " << endP.z << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
		{
			BsplineGraphicProperties* curveGraphicProperties = new BsplineGraphicProperties();

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_BsplineCurve --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			MSBsplineCurvePtr bSpline = curvePrimitive->GetBsplineCurvePtr();
			DPoint3d startP, endP;
			bvector<DPoint3d> polesControlP;


			if (bSpline != nullptr)
			{
				bSpline->ExtractEndPoints(startP, endP);

				outfile.open(filePath, std::ios_base::app, sizeof(std::string));
				outfile << "Is Closed = " << bSpline->IsClosed() << std::endl;

				bSpline->GetPoles(polesControlP);

				outfile << "Control Points: " << std::endl;
				outfile << std::endl;
				outfile.close();

				for (auto point : polesControlP)
				{
					outfile.open(filePath, std::ios_base::app, sizeof(std::string));
					outfile << "point " << " [X] = " << point.x << std::endl;
					outfile << "point " << " [Y] = " << point.y << std::endl;
					outfile << "point " << " [Z] = " << point.z << std::endl;
					outfile << std::endl;
					outfile.close();
				}


				if (bSpline->AreKnotsValid()) {

					bvector<double> inKnots, outKnots;
					bvector<size_t> multiplicityKnots;
					size_t highIndex, lowIndex;
					bSpline->GetKnots(inKnots);

					bSpline->CompressKnots(inKnots, int(bSpline->GetOrder()), outKnots, multiplicityKnots, lowIndex, highIndex);

					curveGraphicProperties->setAreKnotsValid(bSpline->AreKnotsValid());
					curveGraphicProperties->setKnots(inKnots);
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
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_CurveVector --------" << std::endl;
			outfile << std::endl;
			outfile.close();


			if (curvePrimitive->GetChildCurveVectorCP() != nullptr)
			{
				CurveVectorCP cPvector = curvePrimitive->GetChildCurveVectorCP();
				CurvesShapesGraphicProperties* newShapesGraphicProperties = new CurvesShapesGraphicProperties();
				processShapesCurvesVector(*cPvector, false, &*newShapesGraphicProperties);
				shapesGraphicProperties->insertShapesGraphicProperties(newShapesGraphicProperties);

			}

		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
		{
			InterpolationGraphicProperties* curveGraphicProperties = new InterpolationGraphicProperties();

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_InterpolationCurve --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			bvector<DPoint3d> polesControlP;
			DPoint3d startP, endP;
			curvePrimitive->GetStartEnd(startP, endP);

			if (curvePrimitive->GetInterpolationCurveCP() != nullptr)
			{
				MSInterpolationCurveCP intCurve = curvePrimitive->GetInterpolationCurveCP();
				interpolationParam intParams = curvePrimitive->GetInterpolationCurveCP()->params;

				outfile.open(filePath, std::ios_base::app, sizeof(std::string));
				outfile << "Interpolation Is Periodic: " << intParams.isPeriodic << std::endl;
				outfile << "Interpolation Curve Order: " << intParams.order << std::endl;
				outfile << std::endl;

				for (size_t k = 0; k < intParams.numPoints; k++)
				{
					DPoint3d point = curvePrimitive->GetInterpolationCurveCP()->fitPoints[k];
					polesControlP.push_back(point);

					outfile << "point " << k << " [X] = " << point.x << std::endl;
					outfile << "point " << k << " [Y] = " << point.y << std::endl;
					outfile << "point " << k << " [Z] = " << point.z << std::endl;
					outfile << std::endl;

				}

				outfile.close();

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

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_Line --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			DSegment3d segment;
			DPoint3d directionTangent, originStartPoint0;
			DPoint3d startP, endP;
			double lineLength;


			if (curvePrimitive->TryGetLine(segment))
			{
				curvePrimitive->GetStartEnd(startP, endP);

				outfile.open(filePath, std::ios_base::app, sizeof(std::string));
				outfile << "Start Point [X]: " << startP.x << std::endl;
				outfile << "Start Point [Y]: " << startP.y << std::endl;
				outfile << "Start Point [Z]: " << startP.z << std::endl;
				outfile << std::endl;

				outfile << "End Point [X]: " << endP.x << std::endl;
				outfile << "End Point [Y]: " << endP.y << std::endl;
				outfile << "End Point [Z]: " << endP.z << std::endl;
				outfile << std::endl;

				segment.FromOriginAndDirection(originStartPoint0, directionTangent);

				outfile << "Curve Line String Length: " << segment.Length() << std::endl;
				outfile << std::endl;

				outfile.close();

				bvector<DPoint3d> polesControlP;
				polesControlP.push_back(startP);

				curveGraphicProperties->setControlPoints(polesControlP);
				curveGraphicProperties->setDirectionTanget(directionTangent);
				curveGraphicProperties->setStartEndPoints(startP, endP);
			}

			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: //Polyline
		{
			LineStringGraphicProperties* curveGraphicProperties = new LineStringGraphicProperties();

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_LineString --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			DSegment3d segment;
			size_t startPointIndex = 0;
			DPoint3d directionTangent, originStartPoint0, startP, endP;
			double lineLength;


			if (curvePrimitive->TryGetSegmentInLineString(segment, startPointIndex))
			{
				curvePrimitive->GetStartEnd(startP, endP);

				outfile.open(filePath, std::ios_base::app, sizeof(std::string));
				outfile << "Start Point [X]: " << startP.x << std::endl;
				outfile << "Start Point [Y]: " << startP.y << std::endl;
				outfile << "Start Point [Z]: " << startP.z << std::endl;
				outfile << std::endl;

				outfile << "End Point [X]: " << endP.x << std::endl;
				outfile << "End Point [Y]: " << endP.y << std::endl;
				outfile << "End Point [Z]: " << endP.z << std::endl;
				outfile << std::endl;

				segment.FromOriginAndDirection(originStartPoint0, directionTangent);

				outfile << "Curve Line String Length: " << segment.Length() << std::endl;
				outfile << std::endl;

				bvector<DPoint3d> polesControlP;
				if (curvePrimitive->GetLineStringCP() != nullptr) {
					int k = 0;
					for each (DPoint3d p in *curvePrimitive->GetLineStringCP())
					{
						outfile << "point " << k << " [X] = " << p.x << std::endl;
						outfile << "point " << k << " [Y] = " << p.y << std::endl;
						outfile << "point " << k << " [Z] = " << p.z << std::endl;
						outfile << std::endl;

						polesControlP.push_back(p);
						k++;
					}
				}

				outfile.close();

				curveGraphicProperties->setControlPoints(polesControlP);
				curveGraphicProperties->setDirectionTanget(directionTangent);
				curveGraphicProperties->setStartEndPoints(startP, endP);
			}


			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}

		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
		{
			//CurveGraphicProperties* curveGraphicProperties = nullptr;

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_PartialCurve --------" << std::endl;
			outfile << std::endl;
			outfile.close();

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

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_PointString --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			bvector<DPoint3d> polesControlP;

			if (curvePrimitive->GetPointStringCP() != nullptr)
			{
				outfile.open(filePath, std::ios_base::app, sizeof(std::string));

				for (size_t k = 0; k < curvePrimitive->GetPointStringCP()->size(); k++)
				{
					DPoint3d point = curvePrimitive->GetPointStringCP()->at(k);

					outfile << "point " << k << " [X] = " << point.x << std::endl;
					outfile << "point " << k << " [Y] = " << point.y << std::endl;
					outfile << "point " << k << " [Z] = " << point.z << std::endl;
					outfile << std::endl;

					polesControlP.push_back(point);
				}

				outfile.close();

				curveGraphicProperties->setControlPoints(polesControlP);

			}
			if (curveGraphicProperties != nullptr)
				shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "CURVE_PRIMITIVE_TYPE_Spiral --------" << std::endl;
			outfile << std::endl;
			outfile.close();

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

		outfile.flush();
	}
}
#pragma warning (pop)


void GraphicsProcessorEnhancer::processShapesCurvesVector(CurveVectorCR & curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties)
{
	if (!curvesVector.empty())
	{
		if (shapesGraphicProperties == nullptr)
		{
			//TODO [SB] Verify that it's the correct way to identify shapes
			//NB: the object STD_BOLT has no name and it produce an empty container
			//ShapesTypeEnum curveShapesTypeEnum = ShapesTypeEnumUtils::getShapesTypeEnumByDescriptor(pDictionaryProperties->getElementDescriptor());

			/*switch (curveShapesTypeEnum)
			{
			case ShapesTypeEnum::CIRCLE:
			{
				shapesGraphicProperties = new CircleShapesGraphicProperties();
			}
			break;
			case ShapesTypeEnum::SHAPE:
			{
				shapesGraphicProperties = new GenericShapesGraphicProperties();
			}
			break;
			case ShapesTypeEnum::COMPLEX_CHAIN:
			{
				shapesGraphicProperties = new ComplexChainShapesGraphicProperties();
			}
			break;
			case ShapesTypeEnum::ELLIPSE:
			{
				shapesGraphicProperties = new EllipseShapesGraphicProperties();
			}
			break;
			default:
			{
				shapesGraphicProperties = new CurvesShapesGraphicProperties();
			}
			break;
			}*/
			shapesGraphicProperties = new CurvesShapesGraphicProperties();
		}
		
		

		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "-------------------CURVE VECTOR---------------------" << std::endl;
		outfile << "Size: " << curvesVector.size() << std::endl;
		outfile << std::fixed;
		outfile << std::endl;
		outfile.close();

		DPoint3d center, start, end;
		DRange3d range;
		DVec3d normal, centroid;
		double area;
		Transform localToWorld, worldToLocal;
		bool isClosed = false;

		curvesVector.GetStartEnd(start, end);		
		curvesVector.CentroidNormalArea(center, normal, area);
		centroid.Init(center);

		//TODO [SB] Check the correct enumeration type (first 2 enum suggested by Thibaut)
		curvesVector.CloneInLocalCoordinates(LocalCoordinateSelect::LOCAL_COORDINATE_SCALE_01RangeBothAxes, localToWorld, worldToLocal, range);
		
		setGraphicPropertiesAxes((GraphicProperties*&)shapesGraphicProperties, localToWorld);
	
		//Process the primitives inside the Curve Vector
		processCurvesPrimitives(curvesVector, shapesGraphicProperties);
		shapesGraphicProperties->setIsFilled(isFilled);
		shapesGraphicProperties->setArea(area);
		shapesGraphicProperties->setCentroid(centroid);
		shapesGraphicProperties->setNormal(normal);

		// Chek if the shape is closed 
		if (curvesVector.IsClosedPath())
			isClosed = curvesVector.IsClosedPath();
		else if (curvesVector.IsPhysicallyClosedPath())
			isClosed = curvesVector.IsPhysicallyClosedPath();

		shapesGraphicProperties->setIsClosed(isClosed);

		//Bugged function returns Primitive Type curves.HasSingleCurvePrimitive() so check if the vector is equal to 1
		shapesGraphicProperties->setHasSingleCurve(curvesVector.size() == 1);
		shapesGraphicProperties->setBoundaryTypeCurvesContainer(curvesVector.GetBoundaryType());
		

		if (shapesGraphicProperties != nullptr && !shapesGraphicProperties->getCurvesPrimitivesContainerVector().empty())
			//Add the shape to the Dictionary
			pDictionaryProperties->addGraphicProperties(shapesGraphicProperties);

		switch (curvesVector.GetBoundaryType())
		{
		case CurveVector::BoundaryType::BOUNDARY_TYPE_Inner:
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_Inner --------" << std::endl;
			outfile.flush();
			outfile.close();			
		}
		break;		
		break;
		case CurveVector::BoundaryType::BOUNDARY_TYPE_Open:
		{

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_Open --------" << std::endl;
			outfile.flush();
			outfile.close();
		}
		break;
		case CurveVector::BoundaryType::BOUNDARY_TYPE_Outer:
		{

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_Outer --------" << std::endl;		
			outfile.flush();
			outfile.close();
		}
		break;
		case CurveVector::BoundaryType::BOUNDARY_TYPE_ParityRegion:
		{

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_ParityRegion --------" << std::endl;
			outfile.flush();
			outfile.close();
		}
		break;
		case CurveVector::BoundaryType::BOUNDARY_TYPE_UnionRegion:
		{

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_UnionRegion --------" << std::endl;		
			outfile.flush();
			outfile.close();
		}
		break;
		case CurveVector::BoundaryType::BOUNDARY_TYPE_None:
		{

			outfile.open(filePath, std::ios_base::app);
			outfile << std::endl;
			outfile << "BOUNDARY_TYPE_None --------" << std::endl;
			outfile.flush();
			outfile.close();
		}
		default:
			break;
		}

		outfile.open(filePath, std::ios_base::app);
		outfile << "Start Point [X]: " << start.x << std::endl;
		outfile << "Start Point [Y]: " << start.y << std::endl;
		outfile << "Start Point [Z]: " << start.z << std::endl;
		outfile << std::endl;

		outfile << "End Point [X]: " << end.x << std::endl;
		outfile << "End Point [Y]: " << end.y << std::endl;
		outfile << "End Point [Z]: " << end.z << std::endl;
		outfile << std::endl;

		outfile.flush();
		outfile.close();
	}
}
