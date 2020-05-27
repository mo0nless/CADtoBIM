#include "../headers/GraphicsProcessorEnhancer.h"


GraphicsProcessorEnhancer::GraphicsProcessorEnhancer()
{
	//filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
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

void GraphicsProcessorEnhancer::setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, DPoint3d centerOfRotation, RotationalSweepGraphicProperties *& rotationalSweepGraphicProperties)
{
	double radius = 0;
	dgnRotationalSweepDetail.GetRadius(radius, DgnRotationalSweepDetail::RadiusType::Centroidal);
	rotationalSweepGraphicProperties->setRadius(radius);

	rotationalSweepGraphicProperties->setSweepRadians(dgnRotationalSweepDetail.m_sweepAngle);
	rotationalSweepGraphicProperties->setCenterRotation(centerOfRotation);


	pDictionaryProperties->addGraphicProperties(rotationalSweepGraphicProperties);
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

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
CurveGraphicProperties* GraphicsProcessorEnhancer::processCurvePrimitives(ICurvePrimitivePtr curve)
{
	std::ofstream outfile;
	
	outfile.open(filePath, std::ios_base::app, sizeof(std::string));
	outfile << "----------------------------------------" << std::endl;
	outfile << std::fixed;
	outfile << std::endl;
	outfile.close();

	switch (curve->GetCurvePrimitiveType())
	{
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
	{
		AkimaGraphicProperties* curveGraphicProperties = new AkimaGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_AkimaCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetAkimaCurveCP() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			for (size_t k = 0; k < curve->GetAkimaCurveCP()->size(); k++)
			{
				// add control point
				curveGraphicProperties->addControlPoint(curve->GetAkimaCurveCP()->at(k));

				outfile << "point " << k << " [X] = " << curve->GetAkimaCurveCP()->at(k).x << std::endl;
				outfile << "point " << k << " [Y] = " << curve->GetAkimaCurveCP()->at(k).y << std::endl;
				outfile << "point " << k << " [Z] = " << curve->GetAkimaCurveCP()->at(k).z << std::endl;
				outfile << std::endl;
			}

			outfile.close();

			//curveGraphicProperties->setControlPoints(*curve->GetAkimaCurveCP());
		}

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc:
	{
		ArcGraphicProperties* curveGraphicProperties = new ArcGraphicProperties();

		DEllipse3d ellipse;
		DPoint3d centerOUT, startPoint, endPoint, centroID;
		DVec3d directionX, directionY;
		double* pQuatXYZW = nullptr;
		double rx, ry, startAngle, sweepAngle, endAngle, length;
		
		if (!curve->TryGetArc(ellipse))
			break;

		ellipse.GetDGNFields3d(centerOUT, pQuatXYZW, directionX, directionY, rx, ry, startAngle, sweepAngle);

		ellipse.EvaluateEndPoints(startPoint, endPoint);

		//bvector<DPoint3d> polesControlP;
		//polesControlP.push_back(startPoint);
		//polesControlP.push_back(endPoint);

		curveGraphicProperties->addControlPoint(startPoint);
		curveGraphicProperties->addControlPoint(endPoint);

		curveGraphicProperties->setLength(ellipse.ArcLength());
		curveGraphicProperties->setIsCircular(ellipse.IsCircular());
		//curveGraphicProperties->setControlPoints(polesControlP);
		curveGraphicProperties->setDirectionXY(directionX, directionY);
		curveGraphicProperties->setStartAngle(startAngle);
		curveGraphicProperties->setSweepAngle(sweepAngle);
		curveGraphicProperties->setCenterOut(centerOUT);
		curveGraphicProperties->setRadiusXY(rx, ry);
		curveGraphicProperties->setIsFullEllipse(ellipse.IsFullEllipse());

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Arc --------" << std::endl;
		outfile << std::endl;
		outfile << "Center out: x=" << centerOUT .x << ",y=" << centerOUT.y << ",z="<< centerOUT.z <<std::endl;
		outfile << "DirectionX: x=" << directionX.x << ",y=" << directionX.y << ",z=" << directionX.z << std::endl;
		outfile << "DirectionX: Y=" << directionY.x << ",y=" << directionY.y << ",z=" << directionY.z << std::endl;
		outfile << "RX:" << rx << std::endl;
		outfile << "RY:" << ry << std::endl;
		outfile << "startAngle:" << startAngle << std::endl;
		outfile << "sweepAngle:" << sweepAngle << std::endl;
		outfile << "Start point: x=" << startPoint.x << ",y=" << startPoint.y << ",z=" << startPoint.z << std::endl;
		outfile << "End point: x=" << endPoint.x << ",y=" << endPoint.y << ",z=" << endPoint.z << std::endl;
		outfile << "Is Circular: " << ellipse.IsCircular();
		outfile.close();

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
	{
		BsplineGraphicProperties* curveGraphicProperties = new BsplineGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_BsplineCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		MSBsplineCurvePtr bSpline = curve->GetBsplineCurvePtr();
		DPoint3d startP, endP;
		bvector<DPoint3d> polesControlP;

		for (size_t k = 0; k < polesControlP.size(); k++)
		{
			// add control point
			curveGraphicProperties->addControlPoint(polesControlP.at(k));

			outfile << "point " << k << " [X] = " << polesControlP.at(k).x << std::endl;
			outfile << "point " << k << " [Y] = " << polesControlP.at(k).y << std::endl;
			outfile << "point " << k << " [Z] = " << polesControlP.at(k).z << std::endl;
			outfile << std::endl;
		}


		if (bSpline != nullptr)
		{
			bSpline->ExtractEndPoints(startP, endP);

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "Is Closed = " << bSpline->IsClosed() << std::endl;
			outfile << std::endl;
			outfile.close();

			bSpline->GetPoles(polesControlP);
			
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
			//curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setOrder(bSpline->GetOrder());

			return curveGraphicProperties;

		}		
		else { break; }
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
	{
		//CurveGraphicProperties* curveGraphicProperties = nullptr;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_CurveVector --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetChildCurveVectorCP() != nullptr)
		{
			CurveVectorCP cPvector = curve->GetChildCurveVectorCP();
			for each (ICurvePrimitivePtr c in *cPvector)
			{
				//TODO [SB] NEEDS TO BE CHECKED Curve Vector
				return processCurvePrimitives(c); 
			}
		}

		//return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
	{
		InterpolationGraphicProperties* curveGraphicProperties = new InterpolationGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_InterpolationCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		bvector<DPoint3d> polesControlP;

		if (curve->GetInterpolationCurveCP() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			MSInterpolationCurveCP intCurve = curve->GetInterpolationCurveCP();
			interpolationParam intParams = curve->GetInterpolationCurveCP()->params;

			outfile << "Interpolation Is Periodic: " << intParams.isPeriodic << std::endl;
			outfile << "Interpolation Curve Order: " << intParams.order << std::endl;
			outfile << std::endl;

			for (size_t k = 0; k < intParams.numPoints; k++)
			{
				curveGraphicProperties->addControlPoint(curve->GetInterpolationCurveCP()->fitPoints[k]);
				outfile << "point " << k << " [X] = " << curve->GetInterpolationCurveCP()->fitPoints[k].x << std::endl;
				outfile << "point " << k << " [Y] = " << curve->GetInterpolationCurveCP()->fitPoints[k].y << std::endl;
				outfile << "point " << k << " [Z] = " << curve->GetInterpolationCurveCP()->fitPoints[k].z << std::endl;
				outfile << std::endl;

			}

			//curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setOrder(intCurve->GetOrder());
			curveGraphicProperties->setIsPeriodic(intParams.isPeriodic);

			outfile.close();
			
		}

		return curveGraphicProperties;
	}
	break;
	//TODO [SB] Check Line starting point and crf Line String
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
	{
		LineGraphicProperties* curveGraphicProperties = new LineGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Line --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		DSegment3d segment, segment0, segment1;
		DPoint3d directionTangent, originStartPoint0, point0, point1, centroid;
		double fraction0, fraction1, lineLength;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));

		if (curve->TryGetLine(segment))
		{
			outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile << std::endl;

			outfile << "Start Point [X]: " << segment.point[0].x << std::endl;
			outfile << "Start Point [Y]: " << segment.point[0].y << std::endl;
			outfile << "Start Point [Z]: " << segment.point[0].z << std::endl;
			outfile << std::endl;

			outfile << "End Point [X]: " << segment.point[1].x << std::endl;
			outfile << "End Point [Y]: " << segment.point[1].y << std::endl;
			outfile << "End Point [Z]: " << segment.point[1].z << std::endl;
			outfile << std::endl;

			segment.FromOriginAndDirection(originStartPoint0, directionTangent);

			/*outfile << "FromOriginAndDirection" << std::endl;
			outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
			outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
			outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
			outfile << std::endl;

			outfile << "Tangent [X]: " << directionTangent.x << std::endl;
			outfile << "Tangent [Y]: " << directionTangent.y << std::endl;
			outfile << "Tangent [Z]: " << directionTangent.z << std::endl;
			outfile << std::endl;*/

			outfile << "Curve Line String Length: " << segment.Length() << std::endl;
			outfile << std::endl;

			curve->GetStartEnd(point0, point1);
			
			//TODO [SB] Check the start point
			bvector<DPoint3d> polesControlP;
			polesControlP.push_back(point0);

			if (curve->GetLineCP() != nullptr) {
				int k = 0;
				for each (DPoint3d p in *curve->GetLineStringCP())
				{
					curveGraphicProperties->addControlPoint(p);
					outfile << "point " << k << " [X] = " << p.x << std::endl;
					outfile << "point " << k << " [Y] = " << p.y << std::endl;
					outfile << "point " << k << " [Z] = " << p.z << std::endl;
					outfile << std::endl;

					//polesControlP.push_back(p);
					k++;
				}
			}

			//curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setDirectionTanget(directionTangent);
			
		}

		outfile.close();

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: //Polyline
	{
		LineStringGraphicProperties* curveGraphicProperties = new LineStringGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_LineString --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		DSegment3d segment, segment0, segment1;
		size_t startPointIndex = 0;
		DPoint3d directionTangent, originStartPoint0, point0, point1, centroid;
		double fraction0, fraction1, lineLength;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));

		if (curve->TryGetSegmentInLineString(segment, startPointIndex))
		{
			//outfile << "startPointIndex [X]: " << std::to_string(startPointIndex) << std::endl;

			outfile << "Start Point [X]: " << segment.point[0].x << std::endl;
			outfile << "Start Point [Y]: " << segment.point[0].y << std::endl;
			outfile << "Start Point [Z]: " << segment.point[0].z << std::endl;
			outfile << std::endl;

			outfile << "End Point [X]: " << segment.point[1].x << std::endl;
			outfile << "End Point [Y]: " << segment.point[1].y << std::endl;
			outfile << "End Point [Z]: " << segment.point[1].z << std::endl;
			outfile << std::endl;

			segment.FromOriginAndDirection(originStartPoint0, directionTangent);

			/*outfile << "FromOriginAndDirection" << std::endl;
			outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
			outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
			outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
			outfile << std::endl;

			outfile << "Tangent [X]: " << directionTangent.x << std::endl;
			outfile << "Tangent [Y]: " << directionTangent.y << std::endl;
			outfile << "Tangent [Z]: " << directionTangent.z << std::endl;
			outfile << std::endl;*/

			outfile << "Curve Line String Length: " << segment.Length() << std::endl;
			outfile << std::endl;

			curve->GetStartEnd(point0, point1);

			bvector<DPoint3d> polesControlP;
			if (curve->GetLineStringCP() != nullptr) {
				int k = 0;
				for each (DPoint3d p in *curve->GetLineStringCP())
				{
					curveGraphicProperties->addControlPoint(p);
					outfile << "point " << k << " [X] = " << p.x << std::endl;
					outfile << "point " << k << " [Y] = " << p.y << std::endl;
					outfile << "point " << k << " [Z] = " << p.z << std::endl;
					outfile << std::endl;

					polesControlP.push_back(p);
					k++;
				}
			}

			//curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setDirectionTanget(directionTangent);

		}	

		outfile.close();		

		return curveGraphicProperties;
	}

	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
	{
		//CurveGraphicProperties* curveGraphicProperties = nullptr;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PartialCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetPartialCurveDetailCP() != nullptr)
		{
			//TODO [SB] NEEDS TO BE CHECKED the partial curve composition
			return processCurvePrimitives(curve->GetPartialCurveDetailCP()->parentCurve);
		}

		//return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
	{
		PointStringGraphicProperties* curveGraphicProperties = new PointStringGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PointString --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		bvector<DPoint3d> polesControlP;

		if (curve->GetPointStringCP() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			for (size_t k = 0; k < curve->GetPointStringCP()->size(); k++)
			{
				DPoint3d point = curve->GetPointStringCP()->at(k);

				curveGraphicProperties->addControlPoint(point);
				outfile << "point " << k << " [X] = " << point.x << std::endl;
				outfile << "point " << k << " [Y] = " << point.y << std::endl;
				outfile << "point " << k << " [Z] = " << point.z << std::endl;
				outfile << std::endl;

				polesControlP.push_back(point);
			}

			outfile.close();

			//curveGraphicProperties->setControlPoints(polesControlP);
		}
		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
	{
		//CurveGraphicProperties* curveGraphicProperties = nullptr;
		//curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Spiral --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementDescriptor() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		//TODO [SB] Needs to be checked how to handle Spiral 
		if (curve->GetSpiralPlacementCP() != nullptr)
		{
			//DSpiral2dPlacementCP spiralPlace = curve->GetSpiralPlacementCP();
		}
		//return curveGraphicProperties;
	}
	break;
	default:
		break;
	}

	outfile.flush();

	//TODO [SB] Handle the output for null pointer
	return nullptr;
}
#pragma warning (pop)


void GraphicsProcessorEnhancer::processShapesCurvesVector(CurveVectorCR & curves, bool isFilled , ShapesGraphicProperties*& shapesGraphicProperties)
{
	std::ofstream outfile;

	DPoint3d center;
	DRange3d range;
	DVec3d normal, centroid;
	double area;
	Transform localToWorld, worldToLocal;
	//DMatrix4d matrix;

	curves.CentroidNormalArea(center, normal, area);
	centroid.Init(center);

	//TODO [SB] Check the correct enumeration type (first 2 enum suggested by Thibaut)
	curves.CloneInLocalCoordinates(LocalCoordinateSelect::LOCAL_COORDINATE_SCALE_01RangeBothAxes, localToWorld, worldToLocal, range);
	//curves.CentroidAreaXY(centroid, area);
	DMatrix4d matrix;
	curves.ComputeSecondMomentAreaProducts(matrix);

	DPoint4d col1, col2, col3, col4;
	matrix.GetColumn(col1, 0);
	matrix.GetColumn(col2, 1);
	matrix.GetColumn(col3, 2);
	matrix.GetColumn(col4, 3);

	DVec3d columnVectorX2, columnVectorY2, columnVectorZ2;
	columnVectorX2.x = col1.x;
	columnVectorX2.x = col1.y;
	columnVectorX2.x = col1.z;

	columnVectorY2.x = col2.x;
	columnVectorY2.x = col2.y;
	columnVectorY2.x = col2.z;

	columnVectorZ2.x = col3.x;
	columnVectorZ2.x = col3.y;
	columnVectorZ2.x = col3.z;

	//shapesGraphicProperties->setVectorAxis(columnVectorX2, columnVectorY2, columnVectorZ2);


	DPoint3d startPoint;
	curves.GetStartPoint(startPoint);

	DPoint3d centroid2;
	double c_length;
	curves.WireCentroid(c_length,centroid2);

	setGraphicPropertiesAxes((GraphicProperties*&)shapesGraphicProperties, localToWorld);
	
	DVec3d columnVectorX, columnVectorY, columnVectorZ,col;

	localToWorld.GetMatrixColumn(columnVectorX, 0);
	localToWorld.GetMatrixColumn(columnVectorY, 1);
	localToWorld.GetMatrixColumn(columnVectorZ, 2);
	localToWorld.GetMatrixColumn(col, 3);

	shapesGraphicProperties->setIsFilled(isFilled);
	shapesGraphicProperties->setArea(area);
	shapesGraphicProperties->setCentroid(centroid);
	shapesGraphicProperties->setNormal(normal);
	//TODO[SB] Check if the other bool closed path is relevant
	shapesGraphicProperties->setIsClosed(curves.IsClosedPath()); 

	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;
	outfile << "Centroid2: x=" << centroid2.x << ",y=" << centroid2.y << ",z=" << centroid2.z << std::endl;
	outfile << "startPoint: x=" << startPoint.x << ",y=" << startPoint.y << ",z=" << startPoint.z << std::endl;
	outfile << "col1: x=" << col1.x << ",y=" << col1.y << ",z=" << col1.z << ",w=" << col1.w << std::endl;
	outfile << "col2: x=" << col2.x << ",y=" << col2.y << ",z=" << col2.z << ",w=" << col2.w << std::endl;
	outfile << "col3: x=" << col3.x << ",y=" << col3.y << ",z=" << col3.z << ",w=" << col3.w << std::endl;
	outfile << "col4: x=" << col4.x << ",y=" << col4.y << ",z=" << col4.z << ",w=" << col4.w << std::endl;
	outfile << "Centroid: x=" << centroid.x << ",y=" << centroid.y << ",z=" << centroid.z << std::endl;
	outfile << "center: x=" << center.x << ",y=" << center.y << ",z=" << center.z << std::endl;
	outfile << "columnVectorX: x=" << columnVectorX.x << ",y=" << columnVectorX.y << ",z=" << columnVectorX.z << std::endl;
	outfile << "columnVectorY: x=" << columnVectorY.x << ",y=" << columnVectorY.y << ",z=" << columnVectorY.z << std::endl;
	outfile << "columnVectorZ: x=" << columnVectorZ.x << ",y=" << columnVectorZ.y << ",z=" << columnVectorZ.z << std::endl;
	outfile << "col: x=" << col.x << ",y=" << col.y << ",z=" << col.z << std::endl;
	outfile.flush();
	outfile.close();

	switch (curves.GetBoundaryType())
	{
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Inner:
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_Inner --------" << std::endl;
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_Inner);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_None:
	{

		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_None --------" << std::endl;
		
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_None);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Open:
	{

		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_Open --------" << std::endl;
		
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_Open);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_Outer:
	{

		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_Outer --------" << std::endl;
		
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_Outer);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_ParityRegion:
	{

		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_ParityRegion --------" << std::endl;
		
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_ParityRegion);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	case CurveVector::BoundaryType::BOUNDARY_TYPE_UnionRegion:
	{

		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "-------- BOUNDARY_TYPE_UnionRegion --------" << std::endl;
		
		outfile.flush();
		outfile.close();

		shapesGraphicProperties->setBoundaryTypeCurvesContainer(CurveVector::BoundaryType::BOUNDARY_TYPE_UnionRegion);

		for each (ICurvePrimitivePtr curve in curves)
		{
			CurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
			shapesGraphicProperties->insertCurvesGraphicsProperties(curveGraphicProperties);
		}
	}
	break;
	default:
		break;
	}

	//Add the shape to the Dictionary
	pDictionaryProperties->addGraphicProperties(shapesGraphicProperties);
}
