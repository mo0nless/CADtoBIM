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

void GraphicsProcessorEnhancer::setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties)
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << std::fixed;
	outfile << std::endl;
	outfile << " BOX "<< std::endl;
	outfile << std::endl;

	PrimitiveGraphicProperties* primitiveGraphicProperties = new PrimitiveGraphicProperties();
	primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::BOX);

	// calculate axis Z
	DVec3d vectorBaseZ;
	vectorBaseZ.CrossProduct(dgnBoxDetail.m_vectorX, dgnBoxDetail.m_vectorY);

	// set x,y,z axis in dectionary
	primitiveCommonGraphicProperties->setVectorAxisX(dgnBoxDetail.m_vectorX);
	primitiveCommonGraphicProperties->setVectorAxisY(dgnBoxDetail.m_vectorY);
	primitiveCommonGraphicProperties->setVectorAxisZ(vectorBaseZ);

	// set slab properties
	SlabGraphicProperties* slabProperties = new SlabGraphicProperties();
	slabProperties->setLength(dgnBoxDetail.m_topX);
	slabProperties->setWidth(dgnBoxDetail.m_topY);

	double height;
	if (primitiveCommonGraphicProperties->getVolume() > 0) 
	{
		height = primitiveCommonGraphicProperties->getVolume() / (dgnBoxDetail.m_topX * dgnBoxDetail.m_topY);
	}
	else 
	{
		double x = abs(dgnBoxDetail.m_baseOrigin.x - dgnBoxDetail.m_topOrigin.x);
		double y = abs(dgnBoxDetail.m_baseOrigin.y - dgnBoxDetail.m_topOrigin.y);
		double z = abs(dgnBoxDetail.m_baseOrigin.z - dgnBoxDetail.m_topOrigin.z);

		height = sqrt(x*x + y*y + z*z);
	}

	slabProperties->setHeight(height);

	// set slab properties in graphic properties
	primitiveGraphicProperties->setSlabProperties(slabProperties);
	primitiveGraphicProperties->setPrimitiveCommonGraphicProperties(primitiveCommonGraphicProperties);

	pDictionaryProperties->getGraphicProperties()->addPrimitiveGraphicProperties(primitiveGraphicProperties);
}

void GraphicsProcessorEnhancer::setConeGraphicProperties(DgnConeDetail cgnConeDetail, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties)
{
	double height;
	if (primitiveCommonGraphicProperties->getVolume() > 0) 
	{
		 height = (3 * primitiveCommonGraphicProperties->getVolume()) / 
			 (PI*(pow(cgnConeDetail.m_radiusA, 2) + cgnConeDetail.m_radiusA*cgnConeDetail.m_radiusB + pow(cgnConeDetail.m_radiusB, 2)));
	}
	else 
	{
		double x = abs(cgnConeDetail.m_centerA.x - cgnConeDetail.m_centerB.x);
		double y = abs(cgnConeDetail.m_centerA.y - cgnConeDetail.m_centerB.y);
		double z = abs(cgnConeDetail.m_centerA.z - cgnConeDetail.m_centerB.z);

		height = sqrt(x*x + y*y + z*z);
	}

	PrimitiveGraphicProperties* primitiveGraphicProperties = new PrimitiveGraphicProperties();
	// calculate axis Z
	DVec3d vectorBaseZ;
	vectorBaseZ.CrossProduct(cgnConeDetail.m_vector0, cgnConeDetail.m_vector90);

	// set x,y,z axis in dectionary
	primitiveCommonGraphicProperties->setVectorAxisX(cgnConeDetail.m_vector0);
	primitiveCommonGraphicProperties->setVectorAxisY(cgnConeDetail.m_vector90);
	primitiveCommonGraphicProperties->setVectorAxisZ(vectorBaseZ);


	if (cgnConeDetail.m_radiusA == cgnConeDetail.m_radiusB && cgnConeDetail.m_radiusA > 0)
	{
		std::ofstream outfile;
		outfile.open(filePath, std::ios_base::app);
		outfile << std::fixed;
		outfile << std::endl;
		outfile << " Cylinder " << std::endl;
		outfile << std::endl;
		primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::CYLINDER);

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		cylinderGraphicProperties->setRadius(cgnConeDetail.m_radiusA);
		cylinderGraphicProperties->setHeight(height);
		cylinderGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerA);


		primitiveGraphicProperties->setCylinderGraphicProperties(cylinderGraphicProperties);

	}
	else {
		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties();

		if (cgnConeDetail.m_radiusB == 0)
		{
			primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::CONE);
			std::ofstream outfile;
			outfile.open(filePath, std::ios_base::app);
			outfile << std::fixed;
			outfile << std::endl;
			outfile << " Cone " << std::endl;
			outfile << std::endl;
		}
		else if (cgnConeDetail.m_radiusB > 0 && cgnConeDetail.m_radiusA != cgnConeDetail.m_radiusB)
		{
			primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::TRUNCATED_CONE);
			std::ofstream outfile;
			outfile.open(filePath, std::ios_base::app);
			outfile << std::fixed;
			outfile << std::endl;
			outfile << " Truncated cone " << std::endl;
			outfile << std::endl;
		}


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
			primitiveCommonGraphicProperties->setVectorAxisX(-1 * primitiveCommonGraphicProperties->getVectorAxisX());
			primitiveCommonGraphicProperties->setVectorAxisY(-1 * primitiveCommonGraphicProperties->getVectorAxisY());
			primitiveCommonGraphicProperties->setVectorAxisZ(-1 * primitiveCommonGraphicProperties->getVectorAxisZ());

			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusA);
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerA);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerB);
		}

		coneGraphicProperties->setHeight(height);
		primitiveGraphicProperties->setConeGraphicProperties(coneGraphicProperties);
		
	}
	primitiveGraphicProperties->setPrimitiveCommonGraphicProperties(primitiveCommonGraphicProperties);
	pDictionaryProperties->getGraphicProperties()->addPrimitiveGraphicProperties(primitiveGraphicProperties);
}

void GraphicsProcessorEnhancer::setSphereGraphicProperties(PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties)
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << std::fixed;
	outfile << std::endl;
	outfile << " Sphere " << std::endl;
	outfile << std::endl;

	double radius;
	if (primitiveCommonGraphicProperties->getVolume() > 0) 
	{
		radius = pow(((primitiveCommonGraphicProperties->getVolume() / M_PI)*(3. / 4.)), 1. / 3.);
	}
	else 
	{
		radius = -1;
	}
	SphereGraphicProperties* sphereGraphicProperties = new SphereGraphicProperties();
	sphereGraphicProperties->setRadius(radius);

	PrimitiveGraphicProperties* primitiveGraphicProperties = new PrimitiveGraphicProperties();
	primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::SPHERE);

	primitiveGraphicProperties->setSphereGraphicProperties(sphereGraphicProperties);
	primitiveGraphicProperties->setPrimitiveCommonGraphicProperties(primitiveCommonGraphicProperties);

	pDictionaryProperties->getGraphicProperties()->addPrimitiveGraphicProperties(primitiveGraphicProperties);
}

void GraphicsProcessorEnhancer::setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties)
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << std::fixed;
	outfile << std::endl;
	outfile << " Torus " << std::endl;
	outfile << std::endl;

	TorusGraphicProperties* torusGraphicProperties = new TorusGraphicProperties();
	torusGraphicProperties->setCenterPointOfRotation(centerOfRotation);
	torusGraphicProperties->setMinorRadius(dgnTorusPipeDetail.m_minorRadius);
	torusGraphicProperties->setMajorRadius(dgnTorusPipeDetail.m_majorRadius);
	torusGraphicProperties->setSweepRadians(sweepRadians);

	PrimitiveGraphicProperties* primitiveGraphicProperties = new PrimitiveGraphicProperties();
	primitiveGraphicProperties->setTorusGraphicProperties(torusGraphicProperties);
	primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::TORUS);

	// calculate axis Z
	DVec3d vectorBaseZ;
	vectorBaseZ.CrossProduct(dgnTorusPipeDetail.m_vectorX, dgnTorusPipeDetail.m_vectorY);

	// set x,y,z axis in dectionary
	primitiveCommonGraphicProperties->setVectorAxisX(dgnTorusPipeDetail.m_vectorX);
	primitiveCommonGraphicProperties->setVectorAxisY(dgnTorusPipeDetail.m_vectorY);
	primitiveCommonGraphicProperties->setVectorAxisZ(vectorBaseZ);

	primitiveGraphicProperties->setPrimitiveCommonGraphicProperties(primitiveCommonGraphicProperties);
	pDictionaryProperties->getGraphicProperties()->addPrimitiveGraphicProperties(primitiveGraphicProperties);

}

PrimitiveCommonGraphicProperties* GraphicsProcessorEnhancer::PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive)
{
	std::ofstream outfile;
	double area, volume;
	DVec3d centroid;
	RotMatrix axes;
	DVec3d momentxyz;

	primitive.ComputePrincipalAreaMoments(area, centroid, axes, momentxyz);

	outfile.open(filePath, std::ios_base::app);

	outfile << std::fixed;
	outfile << std::endl;
	outfile << "Centroid1 [X] = " << centroid.x << std::endl;
	outfile << "Centroid1 [Y] = " << centroid.y << std::endl;
	outfile << "Centroid1 [Z] = " << centroid.z << std::endl;
	outfile << "Area1 = " << area << std::endl;

	outfile << std::endl;

	PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties = new PrimitiveCommonGraphicProperties();
	primitiveCommonGraphicProperties->setArea(area);
	primitiveCommonGraphicProperties->setCentroid(centroid);

	primitive.ComputePrincipalMoments(volume, centroid, axes, momentxyz);

	outfile << "Centroid2 [X] = " << centroid.x << std::endl;
	outfile << "Centroid2 [Y] = " << centroid.y << std::endl;
	outfile << "Centroid2 [Z] = " << centroid.z << std::endl;
	outfile << "Volume = " << volume << std::endl;
	outfile << "Area2 = " << area << std::endl;
	outfile << std::endl;

	outfile.close();
	primitiveCommonGraphicProperties->setVolume(volume);

	return primitiveCommonGraphicProperties;

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
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve);

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
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc);

		DEllipse3d ellipse;
		DPoint3d centerOUT, startPoint, endPoint, centroID;
		DVec3d directionX, directionY;
		double* pQuatXYZW = nullptr;
		double rx, ry, startAngle, sweepAngle, endAngle, length;

		/*DPoint4dP poleArray;
		DPoint3dP circlePoleArray;
		int maxPole;
		int* pNumPole = nullptr;
		int* pNumSpan = nullptr;*/

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
		/*ellipse.QuadricBezierPoles(poleArray, circlePoleArray, pNumPole, pNumSpan, maxPole);		
		
		ellipse.GetLimits(startAngle, endAngle);
		*/

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Arc --------" << std::endl;
		outfile << std::endl;
		outfile << "Is Circular: " << ellipse.IsCircular();

		/*outfile << "-------- " << pDictionaryProperties->getGeneralProperties()->getElementClassName() << " --------" << std::endl;
		
		outfile << std::endl;*/

		//outfile << "pQuatXYZW [X] = " << *pQuatXYZW << std::endl;
		

		/*if (pNumPole != nullptr) {
			outfile << "Number of Poles = " << *pNumPole << std::endl;
			outfile << std::endl;
		}
		
		outfile << "Max Poles = " << maxPole << std::endl;
		outfile << std::endl;

		if (pNumSpan != nullptr) {
			outfile << "Number of Span = " << *pNumSpan << std::endl;
			outfile << std::endl;
		}

		if (circlePoleArray != nullptr) {
			outfile << "circlePoleArray point [X] = " << circlePoleArray->x << std::endl;
			outfile << "circlePoleArray point [Y] = " << circlePoleArray->y << std::endl;
			outfile << "circlePoleArray point [Z] = " << circlePoleArray->z << std::endl;
			outfile << std::endl;
		}
		
		if (poleArray != nullptr) {
			DPoint3d rPoint;
			poleArray->GetProjectedXYZ(rPoint);

			outfile << "Normalized point [X] = " << rPoint.x << std::endl;
			outfile << "Normalized point [Y] = " << rPoint.y << std::endl;
			outfile << "Normalized point [Z] = " << rPoint.z << std::endl;
			outfile << std::endl;
		}*/

		/*outfile << "Center point [X] = " << centerOUT.x << std::endl;
		outfile << "Center point [Y] = " << centerOUT.y << std::endl;
		outfile << "Center point [Z] = " << centerOUT.z << std::endl;
		outfile << std::endl;

		outfile << "directionX [X] = " << directionX.x << std::endl;
		outfile << "directionX [Y] = " << directionX.y << std::endl;
		outfile << "directionX [Z] = " << directionX.z << std::endl;
		outfile << std::endl;

		outfile << "directionY [X] = " << directionY.x << std::endl;
		outfile << "directionY [Y] = " << directionY.y << std::endl;
		outfile << "directionY [Z] = " << directionY.z << std::endl;
		outfile << std::endl;

		outfile << "Start Angle = " << startAngle << std::endl;
		outfile << "Sweep Angle = " << sweepAngle << std::endl;
		outfile << std::endl;*/
		outfile.close();

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
	{
		BsplineGraphicProperties* curveGraphicProperties = new BsplineGraphicProperties();
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_BsplineCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		MSBsplineCurvePtr bSpline = curve->GetBsplineCurvePtr();
		DPoint3d startP, endP;
		bvector<DPoint3d> polesControlP;

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));

		if (bSpline != nullptr)
		{
			bSpline->ExtractEndPoints(startP, endP);

			outfile << "BsplineCurve Length: " << bSpline->Length() << std::endl;
			outfile << "BsplineCurve Order: " << bSpline->GetOrder() << std::endl;
			outfile << std::endl;

			outfile << "Start point [X] = " << startP.x << std::endl;
			outfile << "Start point [Y] = " << startP.y << std::endl;
			outfile << "Start point [Z] = " << startP.z << std::endl;
			outfile << std::endl;

			outfile << "End point [X] = " << endP.x << std::endl;
			outfile << "End point [Y] = " << endP.y << std::endl;
			outfile << "End point [Z] = " << endP.z << std::endl;
			outfile << std::endl;

			outfile << "Is Closed = " << bSpline->IsClosed() << std::endl;
			outfile << std::endl;

			bSpline->GetPoles(polesControlP);
			for (size_t k = 0; k < polesControlP.size(); k++)
			{
				/*outfile << "Control point " << k << " [X] = " << polesControlP[k].x << std::endl;
				outfile << "Control point " << k << " [Y] = " << polesControlP[k].y << std::endl;
				outfile << "Control point " << k << " [Z] = " << polesControlP[k].z << std::endl;
				outfile << std::endl;*/
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

			//return curveGraphicProperties;
			// need to check for the knots and the weights
		}
		else if ((bSpline = curve->GetMSBsplineCurvePtr()) != nullptr)
		{
			bSpline->ExtractEndPoints(startP, endP);
			outfile << "MSBsplineCurve Length: " << bSpline->Length() << std::endl;
			outfile << "MSBsplineCurve Order: " << bSpline->GetOrder() << std::endl;
			outfile << std::endl;

			outfile << "Start point [X] = " << startP.x << std::endl;
			outfile << "Start point [Y] = " << startP.y << std::endl;
			outfile << "Start point [Z] = " << startP.z << std::endl;
			outfile << std::endl;

			outfile << "End point [X] = " << endP.x << std::endl;
			outfile << "End point [Y] = " << endP.y << std::endl;
			outfile << "End point [Z] = " << endP.z << std::endl;
			outfile << std::endl;

			outfile << "Is Closed = " << bSpline->IsClosed() << std::endl;
			outfile << std::endl;

			bSpline->GetPoles(polesControlP);
			for (size_t k = 0; k < polesControlP.size(); k++)
			{
				/*outfile << "Control point " << k << " [X] = " << polesControlP[k].x << std::endl;
				outfile << "Control point " << k << " [Y] = " << polesControlP[k].y << std::endl;
				outfile << "Control point " << k << " [Z] = " << polesControlP[k].z << std::endl;
				outfile << std::endl;*/
			}

			curveGraphicProperties->setIsClosed(bSpline->IsClosed());
			curveGraphicProperties->setIsSelfIntersect(false);
			curveGraphicProperties->setControlPoints(polesControlP);
			curveGraphicProperties->setOrder(bSpline->GetOrder());

			// need to check for the knots and the weights
			//return curveGraphicProperties;

		}	

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
	{
		ICurveGraphicProperties* curveGraphicProperties = nullptr;
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_CurveVector --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetChildCurveVectorCP() != nullptr)
		{
			CurveVectorCP cPvector = curve->GetChildCurveVectorCP();
			for each (ICurvePrimitivePtr c in *cPvector)
			{
				// NEEDS TO BE CHECKED
				return processCurvePrimitives(c); 
			}
		}

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
	{
		InterpolationGraphicProperties* curveGraphicProperties = new InterpolationGraphicProperties();
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve);

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
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line);

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

			/*segment.ClosestApproachBounded(fraction0, fraction1, point0, point1, segment0, segment1);

			outfile << "==============================================" << std::endl;

			outfile << "ClosestApproachBounded: " << std::endl;
			outfile << std::endl;

			segment.WireCentroid(lineLength, centroid, fraction0, fraction1);

			outfile << std::fixed;
			outfile << std::endl;
			outfile << "Centroid [X] = " << centroid.x << std::endl;
			outfile << "Centroid [Y] = " << centroid.y << std::endl;
			outfile << "Centroid [Z] = " << centroid.z << std::endl;
			outfile << std::endl;

			outfile << "Wire centroid Line Length: " << lineLength << std::endl;
			outfile << std::endl;

			outfile << "==============================================" << std::endl;

			segment.ClosestApproachUnbounded(fraction0, fraction1, point0, point1, segment0, segment1);

			outfile << "==============================================" << std::endl;

			outfile << "ClosestApproachUnbounded: " << std::endl;
			outfile << std::endl;

			segment.WireCentroid(lineLength, centroid, fraction0, fraction1);

			outfile << std::fixed;
			outfile << std::endl;
			outfile << "Centroid [X] = " << centroid.x << std::endl;
			outfile << "Centroid [Y] = " << centroid.y << std::endl;
			outfile << "Centroid [Z] = " << centroid.z << std::endl;
			outfile << std::endl;

			outfile << "Wire centroid Line Length: " << lineLength << std::endl;
			outfile << std::endl;

			outfile << "==============================================" << std::endl;*/
			
		}

		outfile.close();

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: //Polyline
	{
		LineGraphicProperties* curveGraphicProperties = new LineGraphicProperties();
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString);

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

			/*segment.ClosestApproachBounded(fraction0, fraction1, point0, point1, segment0, segment1);

			outfile << "==============================================" << std::endl;

			outfile << "ClosestApproachBounded: " << std::endl;
			outfile << std::endl;

			segment.WireCentroid(lineLength, centroid, fraction0, fraction1);

			outfile << std::fixed;
			outfile << std::endl;
			outfile << "Centroid [X] = " << centroid.x << std::endl;
			outfile << "Centroid [Y] = " << centroid.y << std::endl;
			outfile << "Centroid [Z] = " << centroid.z << std::endl;
			outfile << std::endl;

			outfile << "Wire centroid Line Length: " << lineLength << std::endl;
			outfile << std::endl;

			outfile << "==============================================" << std::endl;

			segment.ClosestApproachUnbounded(fraction0, fraction1, point0, point1, segment0, segment1);

			outfile << "==============================================" << std::endl;

			outfile << "ClosestApproachUnbounded: " << std::endl;
			outfile << std::endl;

			segment.WireCentroid(lineLength, centroid, fraction0, fraction1);

			outfile << std::fixed;
			outfile << std::endl;
			outfile << "Centroid [X] = " << centroid.x << std::endl;
			outfile << "Centroid [Y] = " << centroid.y << std::endl;
			outfile << "Centroid [Z] = " << centroid.z << std::endl;
			outfile << std::endl;

			outfile << "Wire centroid Line Length: " << lineLength << std::endl;
			outfile << std::endl;

			outfile << "==============================================" << std::endl;*/

		}	

		outfile.close();		

		return curveGraphicProperties;
	}

	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
	{
		ICurveGraphicProperties* curveGraphicProperties = nullptr;
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PartialCurve --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetPartialCurveDetailCP() != nullptr)
		{
			// NEEDS TO BE CHECKED
			return processCurvePrimitives(curve->GetPartialCurveDetailCP()->parentCurve);
		}

		return curveGraphicProperties;
	}
	break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
	{
		ICurveGraphicProperties* curveGraphicProperties = new ICurveGraphicProperties();
		curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString);

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
		ICurveGraphicProperties* curveGraphicProperties = nullptr;
		//curveGraphicProperties->setCurvesTypeEnum(ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral);

		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
		outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Spiral --------" << std::endl;
		outfile << std::endl;

		outfile << "-------- " << pDictionaryProperties->getElementName() << " --------" << std::endl;
		outfile << std::endl;
		outfile.close();

		if (curve->GetSpiralPlacementCP() != nullptr)
		{
			//DSpiral2dPlacementCP spiralPlace = curve->GetSpiralPlacementCP();
		}
		return curveGraphicProperties;
	}
	break;
	default:
		break;
	}

	outfile.flush();

	//Handle the output for null pointer
	return nullptr;
}
#pragma warning (pop)
