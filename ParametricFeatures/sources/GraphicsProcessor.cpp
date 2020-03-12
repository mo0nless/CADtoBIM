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
	this->dictionaryProperties->getGraphicProperties()->setArea(area);
	this->dictionaryProperties->getGraphicProperties()->setVolume(volume);
	this->dictionaryProperties->getGraphicProperties()->setCentroid(centroid);
}

inline void GraphicsProcessor::PrintPrincipalProperties(DRange3d& range, DVec3d& vectorRotation, DPoint4d& qRotation, Transform& localToWorld)
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

inline void GraphicsProcessor::setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail)
{
	// set slab properties
	SlabGraphicProperties* slabProperties = new SlabGraphicProperties();
	slabProperties->setLength(dgnBoxDetail.m_topX);
	slabProperties->setWidth(dgnBoxDetail.m_topY);
	slabProperties->setHeight(dictionaryProperties->getGraphicProperties()->getVolume() / (dgnBoxDetail.m_topX * dgnBoxDetail.m_topY));

	// set slab properties in graphic properties
	dictionaryProperties->getGraphicProperties()->setSlabProperties(slabProperties);
}

inline void GraphicsProcessor::setConeGraphicProperties(DgnConeDetail cgnConeDetail)
{
	double height = (3 * dictionaryProperties->getGraphicProperties()->getVolume()) / (PI*(pow(cgnConeDetail.m_radiusA, 2) + cgnConeDetail.m_radiusA*cgnConeDetail.m_radiusB + pow(cgnConeDetail.m_radiusB, 2)));


	if (dictionaryProperties->getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER ||
		(dictionaryProperties->getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE &&  cgnConeDetail.m_radiusA == cgnConeDetail.m_radiusB))
	{

		// overrite primitive type enum value
		dictionaryProperties->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER);

		CylinderGraphicProperties* cylinderGraphicProperties = new CylinderGraphicProperties();
		cylinderGraphicProperties->setRadius(cgnConeDetail.m_radiusA);
		cylinderGraphicProperties->setHeight(height);

		dictionaryProperties->getGraphicProperties()->setCylinderGraphicProperties(cylinderGraphicProperties);

	}
	else if (dictionaryProperties->getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {

		if (cgnConeDetail.m_radiusB > 0 && cgnConeDetail.m_radiusA != cgnConeDetail.m_radiusB) {
			// overrite primitive type enum value
			dictionaryProperties->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE);
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
			dictionaryProperties->getGraphicProperties()->setVectorAxisX(-1 * dictionaryProperties->getGraphicProperties()->getVectorAxisX());
			dictionaryProperties->getGraphicProperties()->setVectorAxisY(-1 * dictionaryProperties->getGraphicProperties()->getVectorAxisY());
			dictionaryProperties->getGraphicProperties()->setVectorAxisZ(-1 * dictionaryProperties->getGraphicProperties()->getVectorAxisZ());

			coneGraphicProperties->setBaseRadius(cgnConeDetail.m_radiusB);
			coneGraphicProperties->setTopRadius(cgnConeDetail.m_radiusA);
			coneGraphicProperties->setTopOrigin(cgnConeDetail.m_centerA);
			coneGraphicProperties->setBaseOrigin(cgnConeDetail.m_centerB);
		}

		coneGraphicProperties->setHeight(height);

		dictionaryProperties->getGraphicProperties()->setConeGraphicProperties(coneGraphicProperties);
	}
}

inline void GraphicsProcessor::setSphereGraphicProperties()
{
	SphereGraphicProperties* sphereGraphicProperties = new SphereGraphicProperties();

	double radius = pow(((dictionaryProperties->getGraphicProperties()->getVolume() / M_PI)*(3. / 4.)), 1. / 3.);
	sphereGraphicProperties->setRadius(radius);

	dictionaryProperties->getGraphicProperties()->setSphereGraphicProperties(sphereGraphicProperties);
}

inline void GraphicsProcessor::setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians)
{
	TorusGraphicProperties* torusGraphicProperties = new TorusGraphicProperties();
	torusGraphicProperties->setMinorRadius(dgnTorusPipeDetail.m_minorRadius);
	torusGraphicProperties->setMajorRadius(dgnTorusPipeDetail.m_majorRadius);
	torusGraphicProperties->setSweepRadians(sweepRadians);

	dictionaryProperties->getGraphicProperties()->setTorusGraphicProperties(torusGraphicProperties);
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
#pragma warning( push )
#pragma warning( disable : 4267)
BentleyStatus GraphicsProcessor::_ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) 
{
	outfile.open(filePath, std::ios_base::app);
	outfile << std::fixed;

	switch (entity.GetEntityType())
	{
	case ISolidKernelEntity::KernelEntityType::EntityType_Solid:
	{
		bvector<ISolidKernelEntityPtr> outSKpointer;
		bvector<ISubEntityPtr> subEntitiesFaces;
		bvector<ISubEntityPtr> subEntitiesEdges;
		bvector<ISubEntityPtr> subEntitiesVertices;

		CurveVectorPtr curveFacesEval;
		CurveVectorPtr curveEdgesEval;
		CurveVectorPtr curveVerticesEval;

		/*DPoint3d point;*/
		/*DVec3d normal, uDir, vDir;*/
		
		//size_t nFaces = SolidUtil::GetBodyFaces(&subEntitiesFaces, entity);

		//mdlSolid_closestPointToSurface
		//DPoint3d mdlSolid_clstPt;
		//DPoint3d mdlSolid_normal;
		//DPoint2d mdlSolid_param;
		//DPoint3d mdlSolid_point;
						

		//if ( nFaces != 0 ) 
		//{
		//	for ( size_t i = 0; i < nFaces; i++ )
		//	{
		//		SolidUtil::Debug::DumpSubEntity(dynamic_cast<ISubEntityCR>(*subEntitiesFaces.at(i)), L" ");
		//		
		//		if ( subEntitiesFaces.at(i).IsValid() ) 
		//		{
		//			DPoint2d uvP = this->solidDetails.GetUV();
		//			SolidUtil::EvaluateFace(dynamic_cast<ISubEntityCR>(*subEntitiesFaces.at(i)), point, normal, uDir, vDir, uvP);

		//			SolidUtil::GetFaceEdges(subEntitiesEdges, dynamic_cast<ISubEntityCR>(*subEntitiesFaces.at(i)));

		//			outfile << "Faces Point " << i << " X : " << point.x << std::endl;
		//			outfile << "Faces Point " << i << " Y : " << point.y << std::endl;
		//			outfile << "Faces Point " << i << " Z : " << point.z << std::endl;

					/*outfile << "Faces Point " << i << " X : " << point.x << std::endl;
					outfile << "Faces Point " << i << " Y : " << point.y << std::endl;
					outfile << "Faces Point " << i << " Z : " << point.z << std::endl;*/

		//					outfile << "Vertex Point " << k << " X : " << point.x << std::endl;
		//					outfile << "Vertex Point " << k << " Y : " << point.y << std::endl;
		//					outfile << "Vertex Point " << k << " Z : " << point.z << std::endl;

							/*outfile << "Vertex Point " << k << " X : " << point.x << std::endl;
							outfile << "Vertex Point " << k << " Y : " << point.y << std::endl;
							outfile << "Vertex Point " << k << " Z : " << point.z << std::endl;*/

		//					SolidUtil::EvaluateFace(dynamic_cast<ISubEntityCR>(*subEntitiesFaces.at(i)), point, normal, uDir, vDir, mdlSolid_param);
		//				}
		//			}
		//		}
		//	}			
		//}

	}
	break;

	case ISolidKernelEntity::KernelEntityType::EntityType_Sheet:
		outfile << elemClassName << "IS Sheet" << ISolidKernelEntity::KernelEntityType::EntityType_Sheet << std::endl;
		break;
	case ISolidKernelEntity::KernelEntityType::EntityType_Wire:
		outfile << elemClassName << "IS Wire" << ISolidKernelEntity::KernelEntityType::EntityType_Wire << std::endl;
		break;
	case  ISolidKernelEntity::KernelEntityType::EntityType_Minimal:
		outfile << elemClassName << "IS minimal" << ISolidKernelEntity::KernelEntityType::EntityType_Wire << std::endl;
		break;

	default:
		break;
	}

	outfile << std::endl;
	return ERROR; 
}

//! Collect output for surfaces and solids as facets.
//! @param[in] meshData The indexed polyface data.
//! @param[in] isFilled The wireframe display of the mesh has opaque fill.
//! @remarks Only called if _ProcessAsFacets returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) 
{

	return ERROR; 
}

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
		DVec3d vectorRotation;
		DPoint4d qRotation;

		Transform localToWorld, locTWor, worldToLocal;
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

			boxDetails.TryGetConstructiveFrame(locTWor, worldToLocal);
					
			localToWorld.Matrix().GetRotationAngleAndVector(vectorRotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);
			

			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

			PrintPrincipalProperties(range, vectorRotation, qRotation, localToWorld);

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

			

			// calculate axis Z
			DVec3d vectorBaseZ;
			vectorBaseZ.CrossProduct(boxDetails.m_vectorX, boxDetails.m_vectorY);

			// set x,y,z axis in dectionary
			dictionaryProperties->getGraphicProperties()->setVectorAxisX(boxDetails.m_vectorX);
			dictionaryProperties->getGraphicProperties()->setVectorAxisY(boxDetails.m_vectorY);
			dictionaryProperties->getGraphicProperties()->setVectorAxisZ(vectorBaseZ);

			outfile << "Vector of BASE plane Z [X] = " << vectorBaseZ.x << std::endl;
			outfile << "Vector of BASE plane Z [Y] = " << vectorBaseZ.y << std::endl;
			outfile << "Vector of BASE plane Z [Z] = " << vectorBaseZ.z << std::endl;
			outfile << std::endl;

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

		// set slab graphic properties
		setSlabGraphicProperties(boxDetails);
		
		


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


			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

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


			DVec3d vectorBaseZ;
			vectorBaseZ.CrossProduct(coneDetails.m_vector0, coneDetails.m_vector90);

			dictionaryProperties->getGraphicProperties()->setVectorAxisX(coneDetails.m_vector0);
			dictionaryProperties->getGraphicProperties()->setVectorAxisY(coneDetails.m_vector90);
			dictionaryProperties->getGraphicProperties()->setVectorAxisZ(vectorBaseZ);

			outfile << "0 Degree Vector of BASE circle Z [X] = " << vectorBaseZ.x << std::endl;
			outfile << "0 Degree Vector of BASE circle Z [Y] = " << vectorBaseZ.y << std::endl;
			outfile << "0 Degree Vector of BASE circle Z [Z] = " << vectorBaseZ.z << std::endl;
			outfile << std::endl;
			

			outfile << "Radius at BASE = " << coneDetails.m_radiusA << std::endl;
			outfile << "Radius at TOP = " << coneDetails.m_radiusB << std::endl;
			outfile << std::endl;

			outfile << "True if the end cap is enabled = " << coneDetails.m_capped << std::endl;

			outfile.close();
		}

		PrintPrincipalAreaMoments(primitive);

		// set cone graphic properties
		setConeGraphicProperties(coneDetails);

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


			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

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

		PrintPrincipalAreaMoments(primitive);
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


			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

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

		PrintPrincipalAreaMoments(primitive);
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


			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

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

		PrintPrincipalAreaMoments(primitive);
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


			primitive.ClosestPoint(sphereDetails.m_localToWorld.Origin(), this->solidDetails);

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

		PrintPrincipalAreaMoments(primitive);

		setSphereGraphicProperties();


	

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


			primitive.ClosestPoint(localToWorld.Origin(), this->solidDetails);

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

			DVec3d vectorBaseZ;
			vectorBaseZ.CrossProduct(torusDetails.m_vectorX, torusDetails.m_vectorY);

			outfile << "Vector Z [X] = " << vectorBaseZ.x << std::endl;
			outfile << "Vector Z [Y] = " << vectorBaseZ.y << std::endl;
			outfile << "Vector Z [Z] = " << vectorBaseZ.z << std::endl;
			outfile << std::endl;

			// set x,y,z axis in dectionary
			dictionaryProperties->getGraphicProperties()->setVectorAxisX(torusDetails.m_vectorX);
			dictionaryProperties->getGraphicProperties()->setVectorAxisY(torusDetails.m_vectorY);
			dictionaryProperties->getGraphicProperties()->setVectorAxisZ(vectorBaseZ);

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

		PrintPrincipalAreaMoments(primitive);

		//set torus graphic properties
		setTorusGraphicProperties(torusDetails, sweepRadians);

		//GraphicPropertiesMapper::mapPrincipalMomentsToGraphicProperties(primitive, *dictionaryProperties->getGraphicProperties());
	}
	break;
	default:
		break;
	}

	return ERROR;
}

