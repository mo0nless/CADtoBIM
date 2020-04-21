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

void GraphicsProcessorEnhancer::setGraphicPropertiesAxes(GraphicProperties*& graphicProperties, Transform& localToWorld, const double parametrizationSign)
{
	DVec3d columnVectorX, columnVectorY, columnVectorZ;

	localToWorld.GetMatrixColumn(columnVectorX, 0);
	localToWorld.GetMatrixColumn(columnVectorY, 1);
	localToWorld.GetMatrixColumn(columnVectorZ, 2);
	//columnVectorZ = parametrizationSign * columnVectorZ;

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

SolidPrimitiveProperty * GraphicsProcessorEnhancer::handleConeAndCylinder(DgnConeDetail dgnConeDetail)
{
	// open plant modeler treats the cylinder as cone. in order to distinguish between them, we compare the radius to determine which exact solid we're dealing with
	if (dgnConeDetail.m_radiusA == dgnConeDetail.m_radiusB && dgnConeDetail.m_radiusA > 0) {
		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cylinder " << std::endl;
		outfile << std::endl;

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		return cylinderGraphicProperties;
	} else if (dgnConeDetail.m_radiusB == 0) {
			std::ofstream outfile;
			outfile.open(filePath, std::ios_base::app);
			outfile << std::fixed;
			outfile << std::endl;
			outfile << " Cone " << std::endl;
			outfile << std::endl;

			ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::CONE);
			return coneGraphicProperties;
	} else if (dgnConeDetail.m_radiusB > 0 && dgnConeDetail.m_radiusA != dgnConeDetail.m_radiusB) {
			std::ofstream outfile;
			outfile.open(filePath, std::ios_base::app);
			outfile << std::fixed;
			outfile << std::endl;
			outfile << " Truncated cone " << std::endl;
			outfile << std::endl;

			ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::TRUNCATED_CONE);
			return coneGraphicProperties;
	}

	return nullptr;
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
	DgnConeDetail dgnConeDetail;
	Transform localToWorld;
	Transform worldToLocal;

	primitive.TryGetDgnConeDetail(dgnConeDetail);
	dgnConeDetail.TryGetConstructiveFrame(localToWorld, worldToLocal);

	DVec3d columnVectorX, columnVectorY, columnVectorZ;

	if (dgnConeDetail.m_radiusA == dgnConeDetail.m_radiusB && dgnConeDetail.m_radiusA > 0)
	{


		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cylinder " << std::endl;
		outfile << std::endl;

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		
		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)cylinderGraphicProperties);
		columnVectorX = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector0;
		columnVectorY = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector90;

		columnVectorZ.CrossProduct(dgnConeDetail.m_vector0, dgnConeDetail.m_vector90);
		columnVectorZ = dgnConeDetail.ParameterizationSign() * columnVectorZ;

		cylinderGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
		setCylinderGraphicProperties(dgnConeDetail, cylinderGraphicProperties);

	}
	else if (dgnConeDetail.m_radiusB == 0)
	{
		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cone " << std::endl;
		outfile << std::endl;

		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::CONE);
		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)coneGraphicProperties);
		columnVectorX = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector0;
		columnVectorY = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector90;

		columnVectorZ.CrossProduct(dgnConeDetail.m_vector0, dgnConeDetail.m_vector90);
		columnVectorZ = dgnConeDetail.ParameterizationSign() * columnVectorZ;

		coneGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
		setConeGraphicProperties(dgnConeDetail, coneGraphicProperties);
	}
	else if (dgnConeDetail.m_radiusB > 0 && dgnConeDetail.m_radiusA != dgnConeDetail.m_radiusB)
	{
		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Truncated cone " << std::endl;
		outfile << std::endl;

		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties(PrimitiveTypeEnum::TRUNCATED_CONE);
		PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)coneGraphicProperties);

		columnVectorX = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector0;
		columnVectorY = dgnConeDetail.ParameterizationSign() * dgnConeDetail.m_vector90;
		
		columnVectorZ.CrossProduct(dgnConeDetail.m_vector0, dgnConeDetail.m_vector90);
		columnVectorZ = dgnConeDetail.ParameterizationSign() * columnVectorZ;

		coneGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
		setConeGraphicProperties(dgnConeDetail, coneGraphicProperties);
	}

}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
ICurveGraphicProperties* GraphicsProcessorEnhancer::processCurvePrimitives(ICurvePrimitivePtr curve)
{
	std::ofstream outfile;
	
	switch (curve->GetCurvePrimitiveType())
	{
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
	{
		AkimaGraphicProperties* curveGraphicProperties = new AkimaGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_AkimaCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetAkimaCurveCP() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			for (size_t k = 0; k < curve->GetAkimaCurveCP()->size(); k++)
			{
				outfile << "point " << k << " [X] = " << curve->GetAkimaCurveCP()->at(k).x << std::endl;
				outfile << "point " << k << " [Y] = " << curve->GetAkimaCurveCP()->at(k).y << std::endl;
				outfile << "point " << k << " [Z] = " << curve->GetAkimaCurveCP()->at(k).z << std::endl;
				outfile << std::endl;
			}

			outfile.close();

			curveGraphicProperties->setControlPoints(*curve->GetAkimaCurveCP());
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
		bvector<DPoint3d> polesControlP;
		polesControlP.push_back(startPoint);
		polesControlP.push_back(endPoint);

		curveGraphicProperties->setLength(ellipse.ArcLength());
		curveGraphicProperties->setIsCircular(ellipse.IsCircular());
		curveGraphicProperties->setControlPoints(polesControlP);
		curveGraphicProperties->setDirectionXY(directionX, directionY);
		curveGraphicProperties->setStartAngle(startAngle);
		curveGraphicProperties->setSweepAngle(sweepAngle);
		curveGraphicProperties->setCenterOut(centerOUT);
		curveGraphicProperties->setRadiusXY(rx, ry);
		curveGraphicProperties->setIsFullEllipse(ellipse.IsFullEllipse());

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Arc --------" << std::endl;
		outfile << std::endl;
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

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		MSBsplineCurvePtr bSpline = curve->GetBsplineCurvePtr();
		DPoint3d startP, endP;
		bvector<DPoint3d> polesControlP;


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
			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setOrder(bSpline->GetOrder());

			return curveGraphicProperties;

		}		
		else { break; }
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
	{
		//ICurveGraphicProperties* curveGraphicProperties = nullptr;

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

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
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
				outfile << "point " << k << " [X] = " << curve->GetInterpolationCurveCP()->fitPoints[k].x << std::endl;
				outfile << "point " << k << " [Y] = " << curve->GetInterpolationCurveCP()->fitPoints[k].y << std::endl;
				outfile << "point " << k << " [Z] = " << curve->GetInterpolationCurveCP()->fitPoints[k].z << std::endl;
				outfile << std::endl;

			}

			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setOrder(intCurve->GetOrder());
			curveGraphicProperties->setIsPeriodic(intParams.isPeriodic);

			outfile.close();
			
		}

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
	{
		LineGraphicProperties* curveGraphicProperties = new LineGraphicProperties();

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Line --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		DSegment3d segment, segment0, segment1;
		DPoint3d directionTangent, originStartPoint0, point0, point1, centroid;
		double fraction0, fraction1, lineLength;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));

		if (curve->TryGetLine(segment))
		{
			outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
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

			outfile << "FromOriginAndDirection" << std::endl;
			outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
			outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
			outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
			outfile << std::endl;

			outfile << "Tangent [X]: " << directionTangent.x << std::endl;
			outfile << "Tangent [Y]: " << directionTangent.y << std::endl;
			outfile << "Tangent [Z]: " << directionTangent.z << std::endl;
			outfile << std::endl;

			outfile << "Curve Line String Length: " << segment.Length() << std::endl;
			outfile << std::endl;

			curve->GetStartEnd(point0, point1);

			bvector<DPoint3d> polesControlP;
			polesControlP.push_back(originStartPoint0);

			curveGraphicProperties->setControlPoints(polesControlP);
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

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
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

			outfile << "FromOriginAndDirection" << std::endl;
			outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
			outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
			outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
			outfile << std::endl;

			outfile << "Tangent [X]: " << directionTangent.x << std::endl;
			outfile << "Tangent [Y]: " << directionTangent.y << std::endl;
			outfile << "Tangent [Z]: " << directionTangent.z << std::endl;
			outfile << std::endl;

			outfile << "Curve Line String Length: " << segment.Length() << std::endl;
			outfile << std::endl;

			curve->GetStartEnd(point0, point1);

			bvector<DPoint3d> polesControlP;
			if (curve->GetLineStringCP() != nullptr) {
				for each (DPoint3d p in *curve->GetLineStringCP())
				{
					polesControlP.push_back(p);
				}
			}

			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setDirectionTanget(directionTangent);

		}	

		outfile.close();		

		return curveGraphicProperties;
	}

	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
	{
		//ICurveGraphicProperties* curveGraphicProperties = nullptr;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PartialCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
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

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		bvector<DPoint3d> polesControlP;

		if (curve->GetPointStringCP() != nullptr)
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			for (size_t k = 0; k < curve->GetPointStringCP()->size(); k++)
			{
				DPoint3d point = curve->GetPointStringCP()->at(k);
				outfile << "point " << k << " [X] = " << point.x << std::endl;
				outfile << "point " << k << " [Y] = " << point.y << std::endl;
				outfile << "point " << k << " [Z] = " << point.z << std::endl;
				outfile << std::endl;

				polesControlP.push_back(point);
			}

			outfile.close();

			curveGraphicProperties->setControlPoints(polesControlP);
		}
		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
	{
		//ICurveGraphicProperties* curveGraphicProperties = nullptr;
		//curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Spiral --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
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


void GraphicsProcessorEnhancer::processShapesCurvesVector(CurveVectorCR & curves, bool isFilled , IShapesGraphicProperties*& shapesGraphicProperties)
{
	std::ofstream outfile;

	DPoint3d center;
	DRange3d range;
	DVec3d normal, centroID;
	double area;
	Transform localToWorld, worldToLocal;

	curves.CentroidNormalArea(center, normal, area);
	centroID.Init(center);

	//TODO [SB] Check the correct enumeration type (first 2 enum suggested by Thibaut)
	curves.CloneInLocalCoordinates(LocalCoordinateSelect::LOCAL_COORDINATE_SCALE_01RangeBothAxes, localToWorld, worldToLocal, range);

	setGraphicPropertiesAxes((GraphicProperties*&)shapesGraphicProperties, localToWorld);

	shapesGraphicProperties->setIsFilled(isFilled);
	shapesGraphicProperties->setArea(area);
	shapesGraphicProperties->setCentroid(centroID);
	shapesGraphicProperties->setNormal(normal);
	shapesGraphicProperties->setIsClosed(curves.IsPhysicallyClosedPath());

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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
			ICurveGraphicProperties* curveGraphicProperties = processCurvePrimitives(curve);
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
