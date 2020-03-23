#include "../headers/GraphicsProcessorUtilities.h"


GraphicsProcessorUtilities::GraphicsProcessorUtilities()
{
	//filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
}

void GraphicsProcessorUtilities::setDictionaryProperties(DictionaryProperties& newDictionaryProperties)
{
	this->mDictionaryProperties = newDictionaryProperties;
}

DictionaryProperties * GraphicsProcessorUtilities::getDictionaryProperties()
{
	return &this->mDictionaryProperties;
}

void GraphicsProcessorUtilities::setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail)
{
	// set slab properties
	SlabGraphicProperties* slabProperties = new SlabGraphicProperties();
	slabProperties->setLength(dgnBoxDetail.m_topX);
	slabProperties->setWidth(dgnBoxDetail.m_topY);
	slabProperties->setHeight(mDictionaryProperties.getGraphicProperties()->getVolume() / (dgnBoxDetail.m_topX * dgnBoxDetail.m_topY));

	// set slab properties in graphic properties
	PrimitiveGraphicProperties* primitiveGraphicProperties;
	mDictionaryProperties.getGraphicProperties()->tryGetPrimitiveGraphicProperties(primitiveGraphicProperties);
	primitiveGraphicProperties->setSlabProperties(slabProperties);
}

void GraphicsProcessorUtilities::setConeGraphicProperties(DgnConeDetail cgnConeDetail)
{
	double height = (3 * mDictionaryProperties.getGraphicProperties()->getVolume()) / (PI*(pow(cgnConeDetail.m_radiusA, 2) + cgnConeDetail.m_radiusA*cgnConeDetail.m_radiusB + pow(cgnConeDetail.m_radiusB, 2)));

	PrimitiveGraphicProperties* primitiveGraphicProperties;
	mDictionaryProperties.getGraphicProperties()->tryGetPrimitiveGraphicProperties(primitiveGraphicProperties);

	if (primitiveGraphicProperties->getPrimitiveTypeEnum() == PrimitiveTypeEnum::CYLINDER ||
		(primitiveGraphicProperties->getPrimitiveTypeEnum() == PrimitiveTypeEnum::CONE &&  cgnConeDetail.m_radiusA == cgnConeDetail.m_radiusB))
	{

		// overwrite primitive type enum value
		primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::CYLINDER);

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		cylinderGraphicProperties->setRadius(cgnConeDetail.m_radiusA);
		cylinderGraphicProperties->setHeight(height);

		primitiveGraphicProperties->setCylinderGraphicProperties(cylinderGraphicProperties);

	}
	else if (primitiveGraphicProperties->getPrimitiveTypeEnum() == PrimitiveTypeEnum::CONE) {

		if (cgnConeDetail.m_radiusB > 0 && cgnConeDetail.m_radiusA != cgnConeDetail.m_radiusB) {
			// overrite primitive type enum value
			primitiveGraphicProperties->setPrimitiveTypeEnum(PrimitiveTypeEnum::TRUNCATED_CONE);
		}

		ConeGraphicProperties* coneGraphicProperties = new ConeGraphicProperties();

		if (cgnConeDetail.m_radiusA > cgnConeDetail.m_radiusB)
		{
			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusA);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerB);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerA);
		}
		else {
			// inverse the axes to handle a trimmed cone where the top radius is bigger than the base radius
			mDictionaryProperties.getGraphicProperties()->setVectorAxisX(-1 * mDictionaryProperties.getGraphicProperties()->getVectorAxisX());
			mDictionaryProperties.getGraphicProperties()->setVectorAxisY(-1 * mDictionaryProperties.getGraphicProperties()->getVectorAxisY());
			mDictionaryProperties.getGraphicProperties()->setVectorAxisZ(-1 * mDictionaryProperties.getGraphicProperties()->getVectorAxisZ());

			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusA);
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerA);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerB);
		}

		coneGraphicProperties->setHeight(height);

		primitiveGraphicProperties->setConeGraphicProperties(coneGraphicProperties);
	}
}

void GraphicsProcessorUtilities::setSphereGraphicProperties()
{
	SphereGraphicProperties* sphereGraphicProperties = new SphereGraphicProperties();

	double radius = pow(((mDictionaryProperties.getGraphicProperties()->getVolume() / M_PI)*(3. / 4.)), 1. / 3.);
	sphereGraphicProperties->setRadius(radius);

	PrimitiveGraphicProperties* primitiveGraphicProperties;
	mDictionaryProperties.getGraphicProperties()->tryGetPrimitiveGraphicProperties(primitiveGraphicProperties);
	primitiveGraphicProperties->setSphereGraphicProperties(sphereGraphicProperties);
}

void GraphicsProcessorUtilities::setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians)
{
	TorusGraphicProperties* torusGraphicProperties = new TorusGraphicProperties();
	torusGraphicProperties->setMinorRadius(dgnTorusPipeDetail.m_minorRadius);
	torusGraphicProperties->setMajorRadius(dgnTorusPipeDetail.m_majorRadius);
	torusGraphicProperties->setSweepRadians(sweepRadians);

	PrimitiveGraphicProperties* primitiveGraphicProperties;
	mDictionaryProperties.getGraphicProperties()->tryGetPrimitiveGraphicProperties(primitiveGraphicProperties);
	primitiveGraphicProperties->setTorusGraphicProperties(torusGraphicProperties);
}

void GraphicsProcessorUtilities::PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive)
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
	outfile << "Centroid [X] = " << centroid.x << std::endl;
	outfile << "Centroid [Y] = " << centroid.y << std::endl;
	outfile << "Centroid [Z] = " << centroid.z << std::endl;
	outfile << std::endl;

	primitive.ComputePrincipalMoments(volume, centroid, axes, momentxyz);

	outfile << "Volume = " << volume << std::endl;
	outfile << "Area = " << area << std::endl;
	outfile << std::endl;

	outfile.close();

	// set properties in the dictionary
	this->mDictionaryProperties.getGraphicProperties()->setArea(area);
	this->mDictionaryProperties.getGraphicProperties()->setVolume(volume);
	this->mDictionaryProperties.getGraphicProperties()->setCentroid(centroid);
}

void GraphicsProcessorUtilities::PrintPrincipalProperties(DRange3d& range, DVec3d& vectorRotation, DPoint4d& qRotation, Transform& localToWorld)
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
void GraphicsProcessorUtilities::CurveParser(CurveVectorCP curvesVector)
{
	std::ofstream outfile;

	for each (ICurvePrimitivePtr curve in *curvesVector)
	{
		switch (curve->GetCurvePrimitiveType())
		{
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
		{
		
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_AkimaCurve --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
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
			}
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc:
		{	
			DEllipse3d ellipse;
			DPoint3d centerOUT;
			DVec3d directionX, directionY;
			double* pQuatXYZW = nullptr; 
			double rx, ry, startAngle, sweepAngle;	

			if (!curve->TryGetArc(ellipse))
				break;

			ellipse.GetDGNFields3d(centerOUT, pQuatXYZW, directionX, directionY, rx, ry, startAngle, sweepAngle);

			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Arc --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
		
			//outfile << "pQuatXYZW [X] = " << *pQuatXYZW << std::endl;
			
			outfile << "Center point [X] = " << centerOUT.x << std::endl;
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
			outfile << std::endl;
			outfile.close();	

		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_BsplineCurve --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			MSBsplineCurvePtr bSpline = curve->GetBsplineCurvePtr();
			DPoint3d startP, endP;
			bvector<DPoint3d> polesControlP;

			//CurveGraphicProperties* curveGraphicsProperty = new CurveGraphicProperties();

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

				/*curveGraphicsProperty->setIsClosed(bSpline->IsClosed());
				curveGraphicsProperty->setIsSelfIntersect(false);
				curveGraphicsProperty->setControlPoints(polesControlP);*/

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

				/*curveGraphicsProperty->setIsClosed(bSpline->IsClosed());
				curveGraphicsProperty->setIsSelfIntersect(false);
				curveGraphicsProperty->setControlPoints(polesControlP);*/

				// need to check for the knots and the weights

			}
			outfile.close();

			//dictionaryProperties.getGraphicProperties()->setCurveGraphicsProperties(curveGraphicsProperty);

		
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_CurveVector --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curve->GetChildCurveVectorCP() != nullptr)
			{
				CurveVectorCR cPvector = *curve->GetChildCurveVectorCP();
				CurveParser(&cPvector);
			}
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_InterpolationCurve --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curve->GetInterpolationCurveCP() != nullptr)
			{
				outfile.open(filePath, std::ios_base::app, sizeof(std::string));

				curve->GetInterpolationCurveCP()->GetOrder();
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

				outfile.close();
			}
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Line --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			DSegment3d segment, segment0, segment1;
			DPoint3d tangent, originStartPoint0, point0, point1, centroid;
			double fraction0, fraction1, lineLength;
		
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));

			if (curve->TryGetLine(segment))
			{
				outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
				outfile << std::endl;

				outfile << "Start Point [X]: " << segment.point[0].x << std::endl;
				outfile << "Start Point [Y]: " << segment.point[0].y << std::endl;
				outfile << "Start Point [Z]: " << segment.point[0].z << std::endl;
				outfile << std::endl;

				outfile << "End Point [X]: " << segment.point[1].x << std::endl;
				outfile << "End Point [Y]: " << segment.point[1].y << std::endl;
				outfile << "End Point [Z]: " << segment.point[1].z << std::endl;
				outfile << std::endl;

				segment.FromOriginAndDirection(originStartPoint0, tangent);

				outfile << "FromOriginAndDirection" << std::endl;
				outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
				outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
				outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
				outfile << std::endl;

				outfile << "Tangent [X]: " << tangent.x << std::endl;
				outfile << "Tangent [Y]: " << tangent.y << std::endl;
				outfile << "Tangent [Z]: " << tangent.z << std::endl;
				outfile << std::endl;

				outfile << "Curve Line String Length: " << segment.Length() << std::endl;
				outfile << std::endl;

				segment.ClosestApproachBounded(fraction0, fraction1, point0, point1, segment0, segment1);

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

				outfile << "==============================================" << std::endl;
			}
		
			curve->GetStartEnd(point0, point1);
		
			if (curve->GetLineCP() != nullptr)
			{
				outfile << "Components --------" << curve->NumComponent() << std::endl;
				outfile << std::endl;

				outfile << "point 0 " << " [X] = " << curve->GetLineCP()->point[0].x << std::endl;
				outfile << "point 0 " << " [Y] = " << curve->GetLineCP()->point[0].y << std::endl;
				outfile << "point 0 " << " [Z] = " << curve->GetLineCP()->point[0].z << std::endl;
				outfile << std::endl;

				outfile << "point 1 " << " [X] = " << curve->GetLineCP()->point[1].x << std::endl;
				outfile << "point 1 " << " [Y] = " << curve->GetLineCP()->point[1].y << std::endl;
				outfile << "point 1 " << " [Z] = " << curve->GetLineCP()->point[1].z << std::endl;
				outfile << std::endl;
				
			}

			outfile.close();
		
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString: //Polyline
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_LineString --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			DSegment3d segment, segment0, segment1;
			size_t startPointIndex = 0;
			DPoint3d tangent, originStartPoint0, point0, point1, centroid;
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

				segment.FromOriginAndDirection(originStartPoint0, tangent);

				outfile << "FromOriginAndDirection" << std::endl;
				outfile << "Starting Point [X]: " << originStartPoint0.x << std::endl;
				outfile << "Starting Point [Y]: " << originStartPoint0.y << std::endl;
				outfile << "Starting Point [Z]: " << originStartPoint0.z << std::endl;
				outfile << std::endl;

				outfile << "Tangent [X]: " << tangent.x << std::endl;
				outfile << "Tangent [Y]: " << tangent.y << std::endl;
				outfile << "Tangent [Z]: " << tangent.z << std::endl;
				outfile << std::endl;

				outfile << "Curve Line String Length: " << segment.Length() << std::endl;
				outfile << std::endl;

				segment.ClosestApproachBounded(fraction0, fraction1, point0, point1, segment0, segment1);

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

				outfile << "==============================================" << std::endl;

			}

			curve->GetStartEnd(point0, point1);

			if (curve->GetLineStringCP() != nullptr)
			{
				outfile << "Components --------" << curve->NumComponent() << std::endl;

				for (size_t k = 0; k < curve->GetLineStringCP()->size(); k++)
				{
					DPoint3d point = curve->GetLineStringCP()->at(k);

					outfile << std::endl;
					outfile << "point " << k << " [X] = " << point.x << std::endl;
					outfile << "point " << k << " [Y] = " << point.y << std::endl;
					outfile << "point " << k << " [Z] = " << point.z << std::endl;
					outfile << std::endl;
				}

			}
			outfile.close();
		
		}

		break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PartialCurve --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curve->GetPartialCurveDetailCP() != nullptr)
			{
				//CurveParser(curve->GetPartialCurveDetailCP()->parentCurve);
			}
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_PointString --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curve->GetPointStringCP() != nullptr)
			{
				outfile.open(filePath, std::ios_base::app, sizeof(std::string));

				for (size_t k = 0; k < curve->GetPointStringCP()->size(); k++)
				{
					outfile << "point " << k << " [X] = " << curve->GetPointStringCP()->at(k).x << std::endl;
					outfile << "point " << k << " [Y] = " << curve->GetPointStringCP()->at(k).y << std::endl;
					outfile << "point " << k << " [Z] = " << curve->GetPointStringCP()->at(k).z << std::endl;
					outfile << std::endl;				
				}

				outfile.close();
			}
		}
			break;
		case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
		{
			outfile.open(filePath, std::ios_base::app, sizeof(std::string));
			outfile << "--------CurveParser: CURVE_PRIMITIVE_TYPE_Spiral --------" << std::endl;
			outfile << std::endl;

			outfile << "-------- " << mDictionaryProperties.getGeneralProperties()->getElementClassName() << " --------" << std::endl;
			outfile << std::endl;
			outfile.close();

			if (curve->GetSpiralPlacementCP() != nullptr)
			{
				//DSpiral2dPlacementCP spiralPlace = curve->GetSpiralPlacementCP();
			}
		}
			break;
		default:
			break;
		}	
	}
	
	outfile.flush(); 
}
#pragma warning (pop)
