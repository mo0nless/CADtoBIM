#include "../headers/GraphicsProcessorEnhancer.h"


GraphicsProcessorEnhancer::GraphicsProcessorEnhancer()
{
	//this->elementBundle = new ElementBundle();
	//filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	this->filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
}

void GraphicsProcessorEnhancer::setDictionaryProperties(DictionaryProperties& newDictionaryProperties)
{
	this->pDictionaryProperties = &newDictionaryProperties;
}

void GraphicsProcessorEnhancer::setElementBundle(ElementBundle & newElementBundle)
{
	this->elementBundle = &newElementBundle;
}

ElementBundle * GraphicsProcessorEnhancer::getElementBundle()
{
	return this->elementBundle;
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
	//pDictionaryProperties->addGraphicProperties(boxGraphicProperties);
	this->elementBundle->setGraphicProperties(*boxGraphicProperties);
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
	//this->pDictionaryProperties->addGraphicProperties(coneGraphicProperties);
	this->elementBundle->setGraphicProperties(*coneGraphicProperties);


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
	//this->pDictionaryProperties->addGraphicProperties(cylinderGraphicProperties);
	this->elementBundle->setGraphicProperties(*cylinderGraphicProperties);


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
	//pDictionaryProperties->addGraphicProperties(sphereGraphicProperties);
	this->elementBundle->setGraphicProperties(*sphereGraphicProperties);


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
	//pDictionaryProperties->addGraphicProperties(torusGraphicProperties);
	this->elementBundle->setGraphicProperties(*torusGraphicProperties);


}

void GraphicsProcessorEnhancer::setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, DPoint3d centerOfRotation, RotationalSweepGraphicProperties *& rotationalSweepGraphicProperties)
{
	// set rotationalSweepGraphic properties
	rotationalSweepGraphicProperties->setCenterRotation(centerOfRotation);
	double radius;
	dgnRotationalSweepDetail.GetRadius(radius, DgnRotationalSweepDetail::RadiusType::Centroidal);
	rotationalSweepGraphicProperties->setRadius(radius);
	rotationalSweepGraphicProperties->setSweepRadians(dgnRotationalSweepDetail.m_sweepAngle);

	// add rotationalSweepGraphic property to the dictionary
	//pDictionaryProperties->addGraphicProperties(rotationalSweepGraphicProperties);
	this->elementBundle->setGraphicProperties(*rotationalSweepGraphicProperties);

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
	outfile << "-------- MSBsplineSurfaceCR msBsplineSurface --------" << "Type: " << msBsplineSurface.type << std::endl;
	outfile.close();

	int numOfBounds;
	double uOrder, vOrder;
	size_t uIntervals, vIntervals, lowAindex, highAindex;
	bvector<double> vKnots, uKnots, vKnotsCompressed, uKnotsCompressed;
	bvector<size_t> vKmultiplicity, uKmultiplicity;
	bvector<bvector<DPoint2d>> boundaryUVLoops;
	
	msBsplineSurface.GetIntervalCounts(uIntervals, vIntervals);
	numOfBounds = msBsplineSurface.GetIntNumBounds();
	
	uOrder = msBsplineSurface.GetIntUOrder();
	vOrder = msBsplineSurface.GetIntVOrder();

	//TODO[SB] Check the surface poles
	bvector<DPoint2d> uvParams;
	bvector<DPoint3d> polesGrid;
	bvector<DPoint3d> poles;
	bvector<DPoint4d> poles4D;
	double uMin, uMax, vMin, vMax;
	T_DoubleVector uKnotsSupport, vKnotsSupport;
	msBsplineSurface.GetPoles(poles);
	msBsplineSurfaceGraphicProperties->mFullArrayControlPoint = poles;
	msBsplineSurface.EvaluateUniformGrid(msBsplineSurface.GetIntNumUPoles(), msBsplineSurface.GetIntNumVPoles(), uvParams, polesGrid);
	msBsplineSurface.GetParameterRegion(uMin, uMax, vMin, vMax);
	//msBsplineSurface.GetSupport(poles4D, uKnotsSupport, vKnotsSupport, msBsplineSurface.GetIntNumUPoles() - 1, msBsplineSurface.GetIntNumVPoles() - 1);
	//BSurfPatch patch;
	//msBsplineSurface.GetPatch(*patch, msBsplineSurface.GetIntNumUPoles() - 1, msBsplineSurface.GetIntNumVPoles() - 1);
	
	outfile.open(filePath, std::ios_base::app, sizeof(std::string));
	outfile << "POINT Following the m/n parameters" << std::endl;
	int mParam = ((msBsplineSurface.GetIntNumUKnots()) - (uOrder - 1) - 1);	
	int nParam = msBsplineSurface.GetIntNumPoles();
	int nParamCalc = ((msBsplineSurface.GetIntNumVKnots()) - (uOrder - 1) - 1); ;
	outfile << "mParam: " << mParam << std::endl;
	outfile << "nParam: " << nParam << std::endl;
	outfile << "nParamCalc: " << nParamCalc << std::endl;
	outfile.close();

	//msBsplineSurface.GetIntervalCounts();
	//msBsplineSurface.();

	//Get the UV Poles control points of the surface
	std::vector<std::vector<DPoint3d>> controlPointsUV;
	std::vector<std::vector<double>> weights;
	int count = 0;
	outfile.open(filePath, std::ios_base::app, sizeof(std::string));
	outfile << "POINT Controls: " << std::endl;
	//outfile << "Inverted VU" << std::endl;
	outfile << std::endl;
	for (size_t i = 0; i < msBsplineSurface.GetIntNumUPoles(); i++)
	{
		std::vector<DPoint3d> tempCP;
		std::vector<double> tempW;
		for (size_t j = 0; j < msBsplineSurface.GetIntNumVPoles(); j++)
		{
			auto point = msBsplineSurface.GetPole(i, j);
			tempW.push_back(msBsplineSurface.GetWeight(i, j));
			tempCP.push_back(point);
			count++;

			outfile << "point " << " [X] = " << point.x << std::endl;
			outfile << "point " << " [Y] = " << point.y << std::endl;
			outfile << "point " << " [Z] = " << point.z << std::endl;
			outfile << std::endl;
		}
		controlPointsUV.push_back(tempCP);
		weights.push_back(tempW);
	}
	outfile.close();

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
	outfile << "Number of UV Poles Get Poles: " << poles.size() << std::endl;
	outfile << "Grid Poles Number: " << polesGrid.size() << std::endl;
	outfile << "HasValidPoleCounts: " << msBsplineSurface.HasValidPoleCounts() << std::endl;
	outfile << "HasValidPoleAllocation: " << msBsplineSurface.HasValidPoleAllocation() << std::endl;
	outfile << std::endl;
	outfile.close();


//Curve Internal bounds
#if true
	//This function returns a parity regions
	//Outer/Inner Line String Boundaries
	CurveVectorPtr curveVecBound = msBsplineSurface.GetUVBoundaryCurves(false, false); //true,true before

	// Curve Shape for Boundaries
	CurvesShapesGraphicProperties* shapesGraphicProperties = new CurvesShapesGraphicProperties();
	bool addToDictionary = true;
	processShapesCurvesVector(*curveVecBound, false, &*shapesGraphicProperties, addToDictionary); 

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

					/*outfile.open(filePath, std::ios_base::app, sizeof(std::string));
					outfile << "point " << " [X] = " << evalP.x << std::endl;
					outfile << "point " << " [Y] = " << evalP.y << std::endl;
					outfile << "point " << " [Z] = " << evalP.z << std::endl;
					outfile << std::endl;
					outfile.close();*/
				}

				//Reset the evaluated Control Points
				bSpline->setControlPoints(controlPointsBound);
				//Reset the Start and End Point
				bSpline->setStartEndPoints(*controlPointsBound.begin(), *controlPointsBound.end());
			}
		}
	}

	//Add to the Bspline the Bound
	msBsplineSurfaceGraphicProperties->addCurvesShapesGraphicProperties(shapesGraphicProperties);
	
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
	//msBsplineSurface.GetUVBoundaryLoops(boundaryUVLoops, true);
	msBsplineSurface.GetUVBoundaryLoops(boundaryUVLoops, false);

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
	msBsplineSurfaceGraphicProperties->setUVKnots(uKnotsCompressed, vKnotsCompressed);
	//msBsplineSurfaceGraphicProperties->setUVKnots(uKnots, vKnots);
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

			/*ellipse.QuadricBezierPoles()
			ellipse.Evaluate()*/

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
						/*outfile << "point " << k << " [X] = " << p.x << std::endl;
						outfile << "point " << k << " [Y] = " << p.y << std::endl;
						outfile << "point " << k << " [Z] = " << p.z << std::endl;
						outfile << std::endl;
*/
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


void GraphicsProcessorEnhancer::processShapesCurvesVector(CurveVectorCR & curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties, bool addToDictionary)
{
	if (!curvesVector.empty())
	{
		if (shapesGraphicProperties == nullptr)
		{
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

		//TODO [SB] Check the correct enumeration type (first 2 enum suggested by Thibaut)
		curvesVector.CloneInLocalCoordinates(LocalCoordinateSelect::LOCAL_COORDINATE_SCALE_01RangeBothAxes, localToWorld, worldToLocal, range);

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
		//Bugged function returns Primitive Type curves.HasSingleCurvePrimitive() so check if the vector is equal to 1
		shapesGraphicProperties->setHasSingleCurve(curvesVector.size() == 1);
		shapesGraphicProperties->setBoundaryTypeCurvesContainer(curvesVector.GetBoundaryType());
		
		if (shapesGraphicProperties != nullptr && !shapesGraphicProperties->getCurvesPrimitivesContainerVector().empty() && addToDictionary) {

			//Add the shape to the Dictionary
			//pDictionaryProperties->addGraphicProperties(shapesGraphicProperties);
			this->elementBundle->setGraphicProperties(*shapesGraphicProperties);
		}

	}
}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
//ONLY FACETED BREP SUPPORTED
bool GraphicsProcessorEnhancer::processEntityAsFacetedBRep(ISolidKernelEntityCR entity)
{
	std::ofstream outfile;
	auto entityType = entity.GetEntityType();

#if false
	//New instance of the BRep Element
	if (mBRepGraphicProperties == nullptr)
	{
		mBRepGraphicProperties = new BRepGraphicProperties();
		mBRepGraphicProperties->setBRepTypeEnum((int)entityType);
		processElementAsMesh();
		
		if (entityType == ISolidKernelEntity::KernelEntityType::EntityType_Solid || entityType == ISolidKernelEntity::KernelEntityType::EntityType_Sheet)
		{
			bvector<ISubEntityPtr> subEntitiesFaces;
			bvector<ISubEntityPtr> subEntitiesEdges;
			bvector<ISubEntityPtr> subEntitiesVertices;

			IGeometryPtr geomFacesEval;
			CurveVectorPtr curveEdgesEval;
			CurveVectorPtr curveVerticesEval;

			DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();

			size_t nFaces = SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);
			size_t nEdges = SolidUtil::GetBodyEdges(&subEntitiesEdges, entity);
			size_t nVertices = SolidUtil::GetBodyVertices(&subEntitiesVertices, entity);

			outfile.open(filePath, std::ios_base::app);
			outfile << "Entity------------ " << std::endl;
			outfile << "Edges Entity: " << nEdges << std::endl;
			outfile << "Faces Entity: " << nFaces << std::endl;
			outfile << "Vertices Entity: " << nVertices << std::endl;
			outfile << std::endl;
			outfile.close();

			SolidUtil::Debug::DumpEntity(entity, L"DumpEntity");
			
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- Processing BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile << "Faceted BREP / ShellBased with Mesh Polyface" << std::endl;
			outfile << std::endl;
			outfile.close();

			int boundID = 0;
			int vertexCreated = 0;

			//Clear previous faces
			subEntitiesFaces.clear();
			//Clear the previous vertices
			subEntitiesVertices.clear();

			std::map<std::vector<int>, bool> mapFacesID;

			for (auto edge : subEntitiesEdges)
			{
				ISubEntityCR edgeRef = *edge;
				EdgeId edgeID;
				SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);

				outfile.open(filePath, std::ios_base::app);
				outfile << "EDGE Sub Entity: " << std::endl;
				outfile << std::endl;
				outfile.close();
							

				//Get the faces of the current edge
				SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

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
						double f = i / 15;//fraction 
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
					bound->nodeID = (int)faceID.nodeId;
					bound->faceID.push_back((int)faceID.entityId);

					outfile.open(filePath, std::ios_base::app);
					outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
					outfile << std::endl;
					outfile.close();

					std::vector<int> key = { (int)faceID.nodeId, (int)faceID.entityId };
					if (searchOnMap(mapFacesID, key) == NULL)
					{
						mapFacesID.insert({ key , true });
						mBRepGraphicProperties->addNodeIDFaceID((int)faceID.nodeId,(int)faceID.entityId);
					}

					SolidUtil::GetFaceVertices(subEntitiesVertices, faceRef);
					for (auto vertex : subEntitiesVertices)
					{
						ISubEntityCR vertexRef = *vertex;
						VertexId vertexID;
						SolidUtil::TopologyID::IdFromVertex(vertexID, vertexRef, true);

						DPoint3d vertexPoint;
						if (SolidUtil::EvaluateVertex(vertexRef, vertexPoint) == SUCCESS)
						{
							if (vertexCreated < nVertices)
							{
								outfile.open(filePath, std::ios_base::app, sizeof(std::string));
								outfile << "Vertex Point [X]: " << vertexPoint.x << std::endl;
								outfile << "Vertex Point [Y]: " << vertexPoint.y << std::endl;
								outfile << "Vertex Point [Z]: " << vertexPoint.z << std::endl;
								outfile << std::endl;
								outfile.close();

								mBRepGraphicProperties->addVertexLoop(vertexPoint);
								vertexCreated++;
							}
						}

					}

					//Clear the previous vertices
					subEntitiesVertices.clear();
				}

				boundID++;

				//Add bound Points
				mBRepGraphicProperties->addBoundsPoints(bound);

				//Clear previous faces
				subEntitiesFaces.clear();
			}

			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- End BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile << std::endl;
			outfile.close();

			subEntitiesEdges.clear();
			subEntitiesFaces.clear();
		}
	}
#endif

	bool elementProcessed = false;

	SolidUtil::Debug::DumpEntity(entity, L"Dump-Entity: ");
	//New instance of the BRep Element
	if (mBRepGraphicProperties == nullptr)
	{
		mBRepGraphicProperties = new BRepGraphicProperties();
		mBRepGraphicProperties->setBRepTypeEnum((int)entityType);
		elementProcessed = processElementAsMesh();

		outfile.open(filePath, std::ios_base::app);
		outfile << "Number of Meshes: " << mBRepGraphicProperties->getSolidEntityVector().size() << std::endl;
		outfile.close();
	}

	if (mBRepGraphicProperties != nullptr && (mBRepGraphicProperties->getSolidEntityVector().size() > 0))
	{
		auto solidEntity = mBRepGraphicProperties->getSolidEntityVector().at(mNumberSolidEntity);
		solidEntity->setBRepTypeEnum((int)entityType);
		elementProcessed = true;

		outfile.open(filePath, std::ios_base::app);
		outfile << "Solid Number: " << mNumberSolidEntity << std::endl;
		outfile.close();
		mNumberSolidEntity++;
	}

	return elementProcessed;
}
#pragma warning(pop)

bool GraphicsProcessorEnhancer::processElementAsMesh()
{
	std::ofstream outfile;

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

	if (true == ElementToApproximateFacets(mCurrentElementHandle, meshes, facetOptions.get()))
	{
		for (size_t i = 0; i < meshes.size(); i++)
		{
			SolidEntityGraphicProperties* solidKernelEntity = new SolidEntityGraphicProperties();
			//size_t numOpen, numClosed;
			size_t numVertex, numFacet, numQuad, numTriangle, numImplicitTriangle, numVisEdges, numInvEdges;
			PolyfaceHeaderPtr pMesh = meshes.at(i);
			PolyfaceVisitorPtr pv = PolyfaceVisitor::Attach(*pMesh);

			std::vector<std::vector<DPoint3d>> facetTriangulated;

			pMesh->CollectCounts(numVertex, numFacet, numQuad, numTriangle, numImplicitTriangle, numVisEdges, numInvEdges);

			outfile.open(filePath, std::ios_base::app);
			outfile << "Mesh Number: " << i << std::endl;
			outfile << "numVertex: " << numVertex << std::endl;
			outfile << "numFacet: " << numFacet << std::endl;
			outfile << "numQuad: " << numQuad << std::endl;
			outfile << "numTriangle: " << numTriangle << std::endl;
			outfile << "numImplicitTriangle: " << numImplicitTriangle << std::endl;
			outfile << "numVisEdges: " << numVisEdges << std::endl;
			outfile << "numInvEdges: " << numInvEdges << std::endl;
			outfile << std::endl;
			outfile.close();

			int nFace = 1;

			while (pv->AdvanceToNextFace())
			{
				BlockedVectorDPoint3dR pts = pv->Point();

				std::vector<DPoint3d> face;
				for (DPoint3d pt : pts)
				{
					//Store the point for the triangle face
					face.push_back(pt);
				}

				//Push the face in the container
				solidKernelEntity->addFacetTriangulated(face);

				nFace++;
				outfile.close();
			}

			outfile.open(filePath, std::ios_base::app);
			outfile << "Num Of Facet: " << nFace << std::endl;
			outfile << std::endl;
			outfile.close();

			//Add to the BRep Entity
			mBRepGraphicProperties->addSolidEntityGraphicProperties(solidKernelEntity);
		}
	}
	else
		return false;

	return true;
}

bool GraphicsProcessorEnhancer::ElementToApproximateFacets(ElementHandleCR source,bvector<PolyfaceHeaderPtr> &output,IFacetOptionsP options)
{
	output.clear();
	MeshProcessor dest(output, options);
	ElementGraphicsOutput::Process(source, dest);
	return output.size() > 0 ? true : false;
}