#include "../headers/GraphicsProcessor.h"

GraphicsProcessor::GraphicsProcessor(std::ofstream &mOutfile, std::string& mFilePath)
	: outfile(mOutfile), filePath(mFilePath)
{
	myString.Sprintf(L"Starting Processig the Graphics Component...");
	mdlOutput_messageCenter(DgnPlatform::OutputMessagePriority::Debug, myString.c_str(), myString.c_str(), DgnPlatform::OutputMessageAlert::None);
}


void GraphicsProcessor::setPropertiesDictionary(DictionaryProperties* newDictionaryProperties)
{
	this->dictionaryProperties = newDictionaryProperties;
}

void GraphicsProcessor::updateClassAndID(std::string elemClName, Int64 elmID)
{
	this->elemClassName = elemClName;
	this->elementID = elmID;
}

inline void GraphicsProcessor::PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive)
{
	double area, volume, radius;
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

	radius = pow(((volume / M_PI)*(3. / 4.)), 1. / 3.);

	outfile << "Volume = " << volume << std::endl;
	outfile << "Area = " << area << std::endl;
	outfile << "Radius = " << radius << std::endl;
	outfile << std::endl;

	outfile.close();

	dictionaryProperties->getGraphicProperties()->setArea(area);
	dictionaryProperties->getGraphicProperties()->setVolume(volume);
	dictionaryProperties->getGraphicProperties()->setRadius(radius);
	dictionaryProperties->getGraphicProperties()->setCentroid(centroid);


	//propsDictionary->addGraphicProperty(
	//	PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//		elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::AREA),
	//	PropertyTypeValue("double", area)
	//);

	//propsDictionary->addGraphicProperty(
	//	PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//		elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::RADIUS),
	//	PropertyTypeValue("double", radius)
	//);

	//propsDictionary->addGraphicProperty(
	//	PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//		elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::VOLUME),
	//	PropertyTypeValue("double", volume)
	//);

}

inline void GraphicsProcessor::PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld)
{
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

	outfile << "Euler Rotation ?" << std::endl;
	outfile << "Rotation [X] = " << rotation.x << std::endl;
	outfile << "Rotation [Y] = " << rotation.y << std::endl;
	outfile << "Rotation [Z] = " << rotation.z << std::endl;
	outfile << std::endl;

	outfile << "Origin [X] = " << localToWorld.Origin().x << std::endl;
	outfile << "Origin [Y] = " << localToWorld.Origin().y << std::endl;
	outfile << "Origin [Z] = " << localToWorld.Origin().z << std::endl;
	outfile << std::endl;

	outfile.close();
	
	//propsDictionary->addGraphicProperty(PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//	elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::RANGE),
	//	PropertyTypeValue("DRange3d", range)
	//);

	//propsDictionary->addGraphicProperty(PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//	elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::ORIGIN),
	//	PropertyTypeValue("DPoint3d", localToWorld.Origin())
	//);

	//propsDictionary->addGraphicProperty(PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//	elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::EULER_ROTATION),
	//	PropertyTypeValue("DVec3d", rotation)
	//);

	//propsDictionary->addGraphicProperty(PropertyObjAttribute<GraphicProperties2::GraphicPropertiesEnum>(
	//	elementID, elemClassName, GraphicProperties2::GraphicPropertiesEnum::QUATERNION_ROTATION),
	//	PropertyTypeValue("DPoint4d", qRotation)
	//);
}

//! Collect output as text.
//! @param[in] text The text data.
//! @return SUCCESS if handled, ERROR to output glyph graphics through _ProcessCurveVector.
BentleyStatus GraphicsProcessor::_ProcessTextString(TextStringCR text) { return SUCCESS; } // Don't export glyph geometry...

//! Collect output as a single curve component.
//! @param[in] curve The curve data.
//! @param[in] isClosed The data is from a closed path or region instead of a physically closed path.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @remarks All curve geometry can be handled through _ProcessCurveVector.
//! @see _ProcessCurveVector.
BentleyStatus GraphicsProcessor::_ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled)
{
	switch (curve.GetCurvePrimitiveType())
	{
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_AkimaCurve:
			break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Arc:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_BsplineCurve:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_CurveVector:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_InterpolationCurve:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Line:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_LineString:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PartialCurve:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_PointString:
		break;
	case ICurvePrimitive::CURVE_PRIMITIVE_TYPE_Spiral:
		break;
	}
	return ERROR;
}

//! Collect output as a CurveVector.
//! @param[in] curves The curve data.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @return SUCCESS if handled, ERROR to output individual curves through _ProcessCurvePrimitive.
BentleyStatus GraphicsProcessor::_ProcessCurveVector(CurveVectorCR curves, bool isFilled)
{
	return ERROR;
}

//! Process surfaces and solids not handled directly or are clipped through _ProcessFaceta.
//! @param[in] isPolyface facets are from a call to DrawPolyface, ex. mesh element.
//! @return true to output facets for surface and solid geometry. If returning false,
//! edge and face isoline curves will be output through _ProcessCurveVector.
//! @remarks When both _ProcessAsFacets and _ProcessAsBody return true, _ProcessAsBody has precedence.
//! @note When returning true you also need to implement _ProcessFacets.
bool GraphicsProcessor::_ProcessAsFacets(bool isPolyface) const { return true; }

//! Process surfaces and solids not handled directly or are clipped through _ProcessBody.
//! @param[in] isCurved Graphics output would contain non-linear edge and/or non-planar face geometry.
//! @return true to output solid kernel entities for surface and solid geometry. If returning false,
//! facets will be output if _ProcessAsFacets returns true, otherwise edge and face isoline curves will
//! be output through _ProcessCurveVector.
//! @remarks Requires host implementation of SolidsKernelAdmin methods that take or return a ISolidKernelEntity.
//! @note When returning true you also need to implement _ProcessBody.
//! @see DgnPlatformLib::Host::SolidsKernelAdmin
bool GraphicsProcessor::_ProcessAsBody(bool isCurved) const { return true; }

//! Collect output as a bspline surface.
//! @param[in] surface The bspline surface data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
BentleyStatus GraphicsProcessor::_ProcessSurface(MSBsplineSurfaceCR surface)
{
	return ERROR;
}

//! Collect output for surfaces and solids using a solid kernel entity.
//! @param[in] entity The solid kernel entity.
//! @param[in] attachments Optional face color/material attachment information.
//! @note Requires host implementation of SolidsKernelAdmin methods that take or return a ISolidKernelEntity.
//! @remarks Only called if _ProcessAsBody returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) { return ERROR; }

//! Collect output for surfaces and solids as facets.
//! @param[in] meshData The indexed polyface data.
//! @param[in] isFilled The wireframe display of the mesh has opaque fill.
//! @remarks Only called if _ProcessAsFacets returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) { return ERROR; }

//! Collect output as a solid primitive.
//! @param[in] primitive The solid primitive data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
BentleyStatus GraphicsProcessor::_ProcessSolidPrimitive(ISolidPrimitiveCR primitive)
{
	switch (primitive.GetSolidPrimitiveType())
	{
	case SolidPrimitiveType::SolidPrimitiveType_DgnBox:
	{
		DgnBoxDetail boxDetails;
		bvector<DPoint3d> corners;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		Transform localToWorld;
		double ax;
		double ay;
		double bx;
		double by;

		if (primitive.TryGetDgnBoxDetail(boxDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			boxDetails.GetCorners(corners);
			boxDetails.GetRange(range);
			boxDetails.GetNonUniformTransform(localToWorld, ax, ay, bx, by);
			

			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;

			
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			for (size_t i = 1; i <= corners.size(); i++)
			{
				outfile << "Corner [" << i << "] - " << "[X] = " << corners.at(i - 1).x << std::endl;
				outfile << "Corner [" << i << "] - " << "[Y] = " << corners.at(i - 1).y << std::endl;
				outfile << "Corner [" << i << "] - " << "[Z] = " << corners.at(i - 1).z << std::endl;
				outfile << std::endl;
			}

			outfile << "Vector of BASE plane X [X] = " << boxDetails.m_vectorX.x << std::endl;
			outfile << "Vector of BASE plane X [Y] = " << boxDetails.m_vectorX.y << std::endl;
			outfile << "Vector of BASE plane X [Z] = " << boxDetails.m_vectorX.z << std::endl;
			outfile << std::endl;


			outfile << "Vector of BASE plane Y [X] = " << boxDetails.m_vectorY.x << std::endl;
			outfile << "Vector of BASE plane Y [Y] = " << boxDetails.m_vectorY.y << std::endl;
			outfile << "Vector of BASE plane Y [Z] = " << boxDetails.m_vectorY.z << std::endl;
			outfile << std::endl;

			dictionaryProperties->getGraphicProperties()->setVectorBaseX(boxDetails.m_vectorX);
			dictionaryProperties->getGraphicProperties()->setVectorBaseY(boxDetails.m_vectorY);

			// calculate base vector Z
			DVec3d vectorBaseZ;
			vectorBaseZ.CrossProduct(boxDetails.m_vectorX, boxDetails.m_vectorY);
			dictionaryProperties->getGraphicProperties()->setVectorBaseZ(vectorBaseZ);

			outfile << "Base Rectangel is from Origin to (ax,ay,0). Top is from (0,0,1) to (ax,ay,1)" << std::endl;
			outfile << "AX base rectangle x size = " << ax << std::endl;
			outfile << "AY top rectangle y size = " << ay << std::endl;
			outfile << "BX top rectangle x size = " << bx << std::endl;
			outfile << "BY top rectangle y size = " << by << std::endl;
			outfile << std::endl;

			outfile << "Origin of BASE rectangle [X] = " << boxDetails.m_baseOrigin.x << std::endl;
			outfile << "Origin of BASE rectangle [Y] = " << boxDetails.m_baseOrigin.y << std::endl;
			outfile << "Origin of BASE rectangle [Z] = " << boxDetails.m_baseOrigin.z << std::endl;
			outfile << std::endl;

			outfile << "Origin of TOP rectangle [X] = " << boxDetails.m_topOrigin.x << std::endl;
			outfile << "Origin of TOP rectangle [Y] = " << boxDetails.m_topOrigin.y << std::endl;
			outfile << "Origin of TOP rectangle [Z] = " << boxDetails.m_topOrigin.z << std::endl;
			outfile << std::endl;

			outfile << "Size at the BASE [X] = " << boxDetails.m_baseX << std::endl;
			outfile << "Size at the BASE [Y] = " << boxDetails.m_baseY << std::endl;
			outfile << std::endl;

			outfile << "Size at the TOP [X] = " << boxDetails.m_topX << std::endl;
			outfile << "Size at the TOP [Y] = " << boxDetails.m_topY << std::endl;
			
			outfile << std::endl;

			outfile << "True if the end cap is enabled = " << boxDetails.m_capped << std::endl;

			outfile.close();
		};

		PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
		dictionaryProperties->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum::BOX);

		dictionaryProperties->getGraphicProperties()->setSlabLength( boxDetails.m_topX);
		dictionaryProperties->getGraphicProperties()->setSlabWidth( boxDetails.m_topY);
		dictionaryProperties->getGraphicProperties()->setSlabHeight( dictionaryProperties->getGraphicProperties()->getVolume() / (boxDetails.m_topX*boxDetails.m_topY));
		


	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnCone:
	{
		DgnConeDetail coneDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		Transform localToWorld;
		Transform worldToLocal;
		double radiusA;
		double radiusB;

		if (primitive.TryGetDgnConeDetail(coneDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			coneDetails.GetRange(range);
			coneDetails.GetTransforms(localToWorld, worldToLocal, radiusA, radiusB);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Center of BASE Circle [X] = " << coneDetails.m_centerA.x << std::endl;
			outfile << "Center of BASE Circle [Y] = " << coneDetails.m_centerA.y << std::endl;
			outfile << "Center of BASE Circle [Z] = " << coneDetails.m_centerA.z << std::endl;
			outfile << std::endl;

			outfile << "Center of TOP Circle [X] = " << coneDetails.m_centerB.x << std::endl;
			outfile << "Center of TOP Circle [Y] = " << coneDetails.m_centerB.y << std::endl;
			outfile << "Center of TOP Circle [Z] = " << coneDetails.m_centerB.z << std::endl;
			outfile << std::endl;

			outfile << "0 Degree Vector of BASE circle (vector 0 Degree) [X] = " << coneDetails.m_vector0.x << std::endl;
			outfile << "0 Degree Vector of BASE circle (vector 0 Degree) [Y] = " << coneDetails.m_vector0.y << std::endl;
			outfile << "0 Degree Vector of BASE circle (vector 0 Degree) [Z] = " << coneDetails.m_vector0.z << std::endl;
			outfile << std::endl;

			outfile << "0 Degree Vector of BASE circle (vector 90 Degree) [X] = " << coneDetails.m_vector90.x << std::endl;
			outfile << "0 Degree Vector of BASE circle (vector 90 Degree) [Y] = " << coneDetails.m_vector90.y << std::endl;
			outfile << "0 Degree Vector of BASE circle (vector 90 Degree) [Z] = " << coneDetails.m_vector90.z << std::endl;
			outfile << std::endl;

			outfile << "Radius at BASE = " << coneDetails.m_radiusA << std::endl;
			outfile << "Radius at TOP = " << coneDetails.m_radiusB << std::endl;
			outfile << std::endl;

			outfile << "True if the end cap is enabled = " << coneDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
		dictionaryProperties->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum::CONE);
	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnExtrusion:
	{
		DgnExtrusionDetail extrusionDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		Transform localToWorld;
		Transform worldToLocal;
		DVec3d curveStart;
		DVec3d curveEnd;

		if (primitive.TryGetDgnExtrusionDetail(extrusionDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			extrusionDetails.GetRange(range);
			extrusionDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			extrusionDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			outfile << "Vector of Extrusion [X] = " << extrusionDetails.m_extrusionVector.x << std::endl;
			outfile << "Vector of Extrusion [Y] = " << extrusionDetails.m_extrusionVector.y << std::endl;
			outfile << "Vector of Extrusion [Z] = " << extrusionDetails.m_extrusionVector.z << std::endl;
			outfile << std::endl;

			outfile << "Curve Start Point of Extrusion [X] = " << curveStart.x << std::endl;
			outfile << "Curve Start Point of Extrusion [Y] = " << curveStart.y << std::endl;
			outfile << "Curve Start Point of Extrusion [Z] = " << curveStart.z << std::endl;
			outfile << std::endl;

			outfile << "Curve End Point of Extrusion [X] = " << curveEnd.x << std::endl;
			outfile << "Curve End Point of Extrusion [Y] = " << curveEnd.y << std::endl;
			outfile << "Curve End Point of Extrusion [Z] = " << curveEnd.z << std::endl;
			outfile << std::endl;

			outfile << "True if the curve element has a single element and it's a primitive = " << extrusionDetails.m_baseCurve->HasSingleCurvePrimitive() << std::endl;
			outfile << std::endl;
			outfile << "True if the end cap is enabled = " << extrusionDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnRotationalSweep:
	{
		DgnRotationalSweepDetail rotSweepDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		Transform localToWorld;
		Transform worldToLocal;

		DVec3d curveStart;
		DVec3d curveEnd;

		DVec3d rotationAxes;
		double sweepRadians;
		DPoint3d centerRotation;

		if (primitive.TryGetDgnRotationalSweepDetail(rotSweepDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			rotSweepDetails.GetRange(range);
			rotSweepDetails.GetTransforms(localToWorld, worldToLocal);
			rotSweepDetails.TryGetRotationAxis(centerRotation, rotationAxes, sweepRadians);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);
			rotSweepDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			outfile << "Center Point Rotation [X] = " << centerRotation.x << std::endl;
			outfile << "Center Point Rotation [Y] = " << centerRotation.y << std::endl;
			outfile << "Center Point Rotation [Z] = " << centerRotation.z << std::endl;
			outfile << std::endl;

			outfile << "Axes Rotation [X] = " << rotationAxes.x << std::endl;
			outfile << "Axes Rotation [Y] = " << rotationAxes.y << std::endl;
			outfile << "Axes Rotation [Z] = " << rotationAxes.z << std::endl;
			outfile << std::endl;

			outfile << "Axes of Rotation Direction (Ray3D) [X] = " << rotSweepDetails.m_axisOfRotation.direction.x << std::endl;
			outfile << "Axes of Rotation Direction (Ray3D) [Y] = " << rotSweepDetails.m_axisOfRotation.direction.y << std::endl;
			outfile << "Axes of Rotation Direction (Ray3D) [Z] = " << rotSweepDetails.m_axisOfRotation.direction.z << std::endl;
			outfile << std::endl;

			outfile << "Axes of Rotation Origin (Ray3D) [X] = " << rotSweepDetails.m_axisOfRotation.origin.x << std::endl;
			outfile << "Axes of Rotation Origin (Ray3D) [Y] = " << rotSweepDetails.m_axisOfRotation.origin.y << std::endl;
			outfile << "Axes of Rotation Origin (Ray3D) [Z] = " << rotSweepDetails.m_axisOfRotation.origin.z << std::endl;
			outfile << std::endl;

			outfile << "Curve Start Point of Swept [X] = " << curveStart.x << std::endl;
			outfile << "Curve Start Point of Swept [Y] = " << curveStart.y << std::endl;
			outfile << "Curve Start Point of Swept [Z] = " << curveStart.z << std::endl;
			outfile << std::endl;

			outfile << "Curve End Point of Swept [X] = " << curveEnd.x << std::endl;
			outfile << "Curve End Point of Swept [Y] = " << curveEnd.y << std::endl;
			outfile << "Curve End Point of Swept [Z] = " << curveEnd.z << std::endl;
			outfile << std::endl;

			outfile << "Sweep Radians = " << sweepRadians << std::endl;
			outfile << "Major Circle Sweep Angle = " << rotSweepDetails.m_sweepAngle << std::endl;
			outfile << "Number of 'v' Rules (Radial Around) to Display in Wireframe = " << rotSweepDetails.m_numVRules << std::endl;
			outfile << std::endl;

			outfile << "Is it a closed volume = " << rotSweepDetails.IsClosedVolume() << std::endl;
			outfile << "True if the end cap is enabled = " << rotSweepDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnRuledSweep:
	{
		DgnRuledSweepDetail ruledSweepDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		Transform localToWorld;
		Transform worldToLocal;
		int countCurves = 1;

		if (primitive.TryGetDgnRuledSweepDetail(ruledSweepDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			ruledSweepDetails.GetRange(range);
			ruledSweepDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			for (CurveVectorPtr cv : ruledSweepDetails.m_sectionCurves)
			{
				DVec3d curveStart;
				DVec3d curveEnd;

				cv->GetStartEnd(curveStart, curveEnd);

				outfile << countCurves << "° " << "Curve Start Point of Swept [X] = " << curveStart.x << std::endl;
				outfile << countCurves << "° " << "Curve Start Point of Swept [Y] = " << curveStart.y << std::endl;
				outfile << countCurves << "° " << "Curve Start Point of Swept [Z] = " << curveStart.z << std::endl;
				outfile << std::endl;

				outfile << countCurves << "° " << "Curve End Point of Swept [X] = " << curveEnd.x << std::endl;
				outfile << countCurves << "° " << "Curve End Point of Swept [Y] = " << curveEnd.y << std::endl;
				outfile << countCurves << "° " << "Curve End Point of Swept [Z] = " << curveEnd.z << std::endl;
				outfile << std::endl;

				countCurves += 1;
			}

			outfile << "True if the end cap is enabled = " << ruledSweepDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnSphere:
	{
		DgnSphereDetail sphereDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		if (primitive.TryGetDgnSphereDetail(sphereDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			sphereDetails.GetRange(range);
			sphereDetails.m_localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			sphereDetails.m_localToWorld.Matrix().GetQuaternion(qRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, sphereDetails.m_localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "Start Latitude LatitudeToVFraction = " << sphereDetails.LatitudeToVFraction(sphereDetails.m_startLatitude) << std::endl;
			outfile << "latitudeSweep LatitudeToVFraction = " << sphereDetails.LatitudeToVFraction(sphereDetails.m_latitudeSweep) << std::endl;
			outfile << std::endl;

			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			outfile << "Origin is SPHERE Center. Columns x,y to Equator at 0 and 90 Degrees Latitude. Column z is to north pole." << std::endl;
			outfile << "Latitude for Truncation Plane Parallel to the Equator." << std::endl;
			outfile << "Start Latitude = " << sphereDetails.m_startLatitude << std::endl;
			outfile << "Latitude Difference from Start Truncation Plane to end Truncation Plane." << std::endl;
			outfile << "Latitude Sweep = " << sphereDetails.m_latitudeSweep << std::endl;
			outfile << std::endl;

			outfile << "True if the end cap is enabled = " << sphereDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
		dictionaryProperties->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE);
	}
	break;
	case SolidPrimitiveType::SolidPrimitiveType_DgnTorusPipe:
	{
		DgnTorusPipeDetail torusDetails;
		DRange3d range;
		DVec3d rotation;
		DPoint4d qRotation;

		DPoint4d axesQuatRotation;

		RotMatrix rotationAxes;
		double sweepRadians;
		DPoint3d centerRotation;

		Transform localToWorld;
		Transform worldToLocal;
		double radiusA;
		double radiusB;

		if (primitive.TryGetDgnTorusPipeDetail(torusDetails))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------- "<< elemClassName <<" --------" << std::endl;
			outfile.close();

			torusDetails.GetRange(range);
			torusDetails.TryGetFrame(centerRotation, rotationAxes, radiusA, radiusB, sweepRadians);
			torusDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);
			rotationAxes.GetQuaternion(axesQuatRotation, false);

			PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

			outfile.open(filePath, std::ios_base::app);

			outfile << std::fixed;
			outfile << "Range High = " << range.high.x << std::endl;
			outfile << "Range Low = " << range.low.x << std::endl;
			outfile << "DiagonalDistanceXY = " << range.DiagonalDistanceXY() << std::endl;
			outfile << "DiagonalDistance = " << range.DiagonalDistance() << std::endl;
			outfile << "Range Difference = " << abs(range.high.x) - abs(range.low.x) << std::endl;

			outfile << "Axes Coordinates Axes, XY in major Plane, Z through hole" << std::endl;
			outfile << "Axes Rotation (Quaternion) [X] = " << axesQuatRotation.x << std::endl;
			outfile << "Axes Rotation (Quaternion) [Y] = " << axesQuatRotation.y << std::endl;
			outfile << "Axes Rotation (Quaternion) [Z] = " << axesQuatRotation.z << std::endl;
			outfile << "Axes Rotation (Quaternion) [W] = " << axesQuatRotation.w << std::endl;
			outfile << std::endl;

			outfile << "Center Point Rotation [X] = " << centerRotation.x << std::endl;
			outfile << "Center Point Rotation [Y] = " << centerRotation.y << std::endl;
			outfile << "Center Point Rotation [Z] = " << centerRotation.z << std::endl;
			outfile << std::endl;

			outfile << "Center [X] = " << torusDetails.m_center.x << std::endl;
			outfile << "Center [Y] = " << torusDetails.m_center.y << std::endl;
			outfile << "Center [Z] = " << torusDetails.m_center.z << std::endl;
			outfile << std::endl;

			outfile << "Vector X [X] = " << torusDetails.m_vectorX.x << std::endl;
			outfile << "Vector X [Y] = " << torusDetails.m_vectorX.y << std::endl;
			outfile << "Vector X [Z] = " << torusDetails.m_vectorX.z << std::endl;
			outfile << std::endl;

			outfile << "Vector Y [X] = " << torusDetails.m_vectorY.x << std::endl;
			outfile << "Vector Y [Y] = " << torusDetails.m_vectorY.y << std::endl;
			outfile << "Vector Y [Z] = " << torusDetails.m_vectorY.z << std::endl;
			outfile << std::endl;

			outfile << "Major Radius = " << torusDetails.m_majorRadius << std::endl;
			outfile << "Minor Radius = " << torusDetails.m_minorRadius << std::endl;
			outfile << "Sweep Angle = " << torusDetails.m_sweepAngle << std::endl;
			outfile << "Sweep Radians = " << sweepRadians << std::endl;
			outfile << std::endl;

			outfile << "Radius Major (Elbow Radius) = " << radiusA << std::endl;
			outfile << "Radius Minor (Pipe Diameter) = " << radiusB << std::endl;
			outfile << std::endl;

			outfile << "True if the end cap is enabled = " << torusDetails.m_capped << std::endl;

			outfile.close();
		}

		//PrintPrincipalAreaMoments(primitive);
		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
	}
	break;
	default:
		break;
	}

	return ERROR;
}