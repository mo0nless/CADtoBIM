#include "../headers/GraphicsProcessor.h"

GraphicsProcessor::GraphicsProcessor()	
{
	//filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	WString myString;
	myString.Sprintf(L"Starting Processig the Graphics Component...");
	mdlOutput_messageCenter(DgnPlatform::OutputMessagePriority::Debug, myString.c_str(), myString.c_str(), DgnPlatform::OutputMessageAlert::None);

	this->mGraphicsProcessorEnhancer = GraphicsProcessorEnhancer();
}

GraphicsProcessorEnhancer* GraphicsProcessor::getGraphicsProcessorEnhancer()
{
	return &this->mGraphicsProcessorEnhancer;
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
BentleyStatus GraphicsProcessor::_ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled){	return ERROR; }

//! Collect output as a CurveVector.
//! @param[in] curves The curve data.
//! @param[in] isFilled A closed path or region should have opaque fill.
//! @return SUCCESS if handled, ERROR to output individual curves through _ProcessCurvePrimitive.
#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
BentleyStatus GraphicsProcessor::_ProcessCurveVector(CurveVectorCR curves, bool isFilled)
{
	mGraphicsProcessorEnhancer.processShapesCurvesVector(curves, isFilled);
		
	return ERROR;
}
#pragma warning( pop ) 


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
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4101)
BentleyStatus GraphicsProcessor::_ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) 
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << std::fixed;
	outfile.close();
	
	DictionaryProperties* dictionaryProperties = mGraphicsProcessorEnhancer.getDictionaryProperties();
	dictionaryProperties->setIsSmartSolid(true);

	if (!dictionaryProperties->getIsPrimitiveSolid())
	{
		switch (entity.GetEntityType())
		{

		case ISolidKernelEntity::KernelEntityType::EntityType_Solid:
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "In SolidKernel Entity is: Solid " << ISolidKernelEntity::KernelEntityType::EntityType_Solid << std::endl;
			outfile << std::endl;
			outfile.close();
		}
		break;
		case ISolidKernelEntity::KernelEntityType::EntityType_Sheet: // Is different from a solid IfcShellBasedSurfaceModel
		{
			bvector<ISubEntityPtr> subEntitiesFaces;
			bvector<ISubEntityPtr> subEntitiesEdges;
			bvector<ISubEntityPtr> subEntitiesVertices;

			IGeometryPtr geomFacesEval;
			CurveVectorPtr curveEdgesEval;
			CurveVectorPtr curveVerticesEval;

			outfile.open(filePath, std::ios_base::app);
			outfile << "In SolidKernel Entity is: Sheet " << ISolidKernelEntity::KernelEntityType::EntityType_Sheet << std::endl;
			outfile << std::endl;
			outfile.close();

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

			BRepSolidsKernelEntity* brepEntity = new BRepSolidsKernelEntity();

			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- Processing BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile.close();

//Vertices start dependences 
#if false 
			//The edges that result closed no needs to be considered
			for (auto edge : subEntitiesEdges)
			{
				ISubEntityCR edgeRef = *edge;
				if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
				{
					//If it's a closed remove it from the edges
					if (curveEdgesEval->IsClosedPath() || curveEdgesEval->IsPhysicallyClosedPath())
					{
						nEdges--;
					}
				}
			}

			int faceCreated = 0;
			int edgeCreated = 0;

			for (auto vertex : subEntitiesVertices)
			{					
				ISubEntityCR vertexRef = *vertex;
				VertexId vertexID;
				SolidUtil::TopologyID::IdFromVertex(vertexID, vertexRef, true);
				SolidUtil::Debug::DumpSubEntity(vertexRef, L"DumpSubEntity Vertex");
								
				/*for (auto f : vertexID.faces)
				{
					outfile.open(filePath, std::ios_base::app);
					outfile << "--------- Vertex -------- Entity: " << f.nodeId << " ID: " << f.entityId << std::endl;
					outfile << std::endl;
					outfile.close();
				}*/

				//Clear the Edges and Faces store previously
				subEntitiesFaces.clear();
				subEntitiesEdges.clear();

				//Get the Edges from the Vertex
				SolidUtil::GetVertexEdges(subEntitiesEdges, vertexRef);
				for (auto edge : subEntitiesEdges)
				{	
					//Check if they were already created
					if (edgeCreated < nEdges)
					{
						ISubEntityCR edgeRef = *edge;
						EdgeId edgeID;
						SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);

						for (auto f : edgeID.faces)
						{
							outfile.open(filePath, std::ios_base::app);
							outfile << "--------- Vertex's EDGE -------- Entity: " << f.nodeId << " ID: " << f.entityId << std::endl;
							outfile << std::endl;
							outfile.close();
						}

					
						CurvesShapesGraphicProperties* shapesGraphicProperties = new CurvesShapesGraphicProperties();

						if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
						{
							mGraphicsProcessorEnhancer.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties);
						}

						//Get the faces of the current edge
						SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);
						for (auto face : subEntitiesFaces)
						{
							ISubEntityCR faceRef = *face;
							FaceId faceID;
							SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

							outfile.open(filePath, std::ios_base::app);
							outfile << "--------- Edge's FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
							
							bvector<ISubEntityPtr> subEdges;
							SolidUtil::GetFaceEdges(subEdges, faceRef);
							outfile << "Number of Edges from the face: " << subEdges.size() << std::endl;

							outfile << std::endl;
							outfile.close();

							//Save the faceID to the Curve 
							shapesGraphicProperties->setFaceBoundID(faceID.entityId);
							shapesGraphicProperties->setNodeId(faceID.nodeId);

							if (faceCreated < nFaces)
							{
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

										mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

										//Add the face to the BrepEntity
										brepEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
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
								}

								faceCreated++;
							}
						}

						//Clear the faces store previously
						subEntitiesFaces.clear();

						edgeCreated++;
					}
				}					
			}

#endif

//Faces start dependences 
#if true
			for (auto face : subEntitiesFaces)
			{
				if (face == NULL)
					continue;

				ISubEntityCR faceRef = *face;
				FaceId faceID;
				SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

				outfile.open(filePath, std::ios_base::app);
				outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
				outfile << std::endl;
				outfile.close();

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

						mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

						//Add the face to the BrepEntity
						brepEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
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

					//SolidUtil::GetFaceVertices(subEntitiesVertices, faceRef);
					//for (auto vertex : subEntitiesVertices)
					//{
					//	ISubEntityCR vertexRef = *vertex;
					//	VertexId vertexID;
					//	SolidUtil::TopologyID::IdFromVertex(vertexID, vertexRef, true);
					//	
					//	DPoint3d vertexPoint;
					//	if (SolidUtil::EvaluateVertex(vertexRef, vertexPoint) == SUCCESS)
					//	{
					//		outfile.open(filePath, std::ios_base::app, sizeof(std::string));
					//		outfile << "Vertex Point [X]: " << vertexPoint.x << std::endl;
					//		outfile << "Vertex Point [Y]: " << vertexPoint.y << std::endl;
					//		outfile << "Vertex Point [Z]: " << vertexPoint.z << std::endl;
					//		outfile << std::endl;
					//		outfile.close();
					//	}
					//}

					////Clear the previous vertices
					//subEntitiesVertices.clear();
					//
				}
			}
#endif

//Edges start dependences 
#if false
			//Clear the faces store previously
			subEntitiesFaces.clear();
			subEntitiesVertices.clear();

			int facesCreated = 0;
			int vertexCreated = 0;
			for (auto edge : subEntitiesEdges)
			{

				ISubEntityCR edgeRef = *edge;
				EdgeId edgeID;
				SolidUtil::TopologyID::IdFromEdge(edgeID, edgeRef, true);
				SolidUtil::Debug::DumpSubEntity(edgeRef, L"DumpSubEntity Edge");

				outfile.open(filePath, std::ios_base::app);
				outfile << "EDGE Sub Entity: " << std::endl;
				outfile << std::endl;
				outfile.close();

				CurvesShapesGraphicProperties* shapesGraphicProperties = new CurvesShapesGraphicProperties();

				if (SolidUtil::Convert::SubEntityToCurveVector(curveEdgesEval, edgeRef) == SUCCESS)
				{
					mGraphicsProcessorEnhancer.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties);
				}

				//Get te faces of the current edge
				SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);
				for (auto face : subEntitiesFaces)
				{
					if (face == NULL)
						continue;

					ISubEntityCR faceRef = *face;
					FaceId faceID;
					SolidUtil::TopologyID::IdFromFace(faceID, faceRef, true);

					outfile.open(filePath, std::ios_base::app);
					outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
					outfile << std::endl;
					outfile.close();

					//Save the faceID to the Curve edge
					shapesGraphicProperties->setFaceBoundID(faceID.entityId);
					shapesGraphicProperties->setNodeId(faceID.nodeId);

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

								mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

								//Add the face to the BrepEntity
								brepEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
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

								/*for (auto f : vertexID.faces)
								{
									outfile.open(filePath, std::ios_base::app);
									outfile << "--------- Vertex FACE -------- Entity: " << f.nodeId << " ID: " << f.entityId << std::endl;
									outfile << std::endl;
									outfile.close();
								}*/

								DPoint3d vertexPoint;
								if (SolidUtil::EvaluateVertex(vertexRef, vertexPoint) == SUCCESS)
								{
									outfile.open(filePath, std::ios_base::app, sizeof(std::string));
									outfile << "Vertex Point [X]: " << vertexPoint.x << std::endl;
									outfile << "Vertex Point [Y]: " << vertexPoint.y << std::endl;
									outfile << "Vertex Point [Z]: " << vertexPoint.z << std::endl;
									outfile << std::endl;
									outfile.close();

									if (vertexCreated < nVertices)
									{
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
				
			}
#endif

			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- End BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile << std::endl;
			outfile.close();

			subEntitiesEdges.clear();
			subEntitiesFaces.clear();

			dictionaryProperties->addGraphicProperties(brepEntity);

		}
		break;

		default:
		{

		}

		break;
		case ISolidKernelEntity::KernelEntityType::EntityType_Wire:
			outfile.open(filePath, std::ios_base::app);
			outfile << "In SolidKernel Entity is: Wire " << ISolidKernelEntity::KernelEntityType::EntityType_Wire << std::endl;

			outfile << std::endl;
			outfile.close();
			break;
		case  ISolidKernelEntity::KernelEntityType::EntityType_Minimal:
			outfile.open(filePath, std::ios_base::app);
			outfile << "In SolidKernel Entity is: Minimal " << ISolidKernelEntity::KernelEntityType::EntityType_Wire << std::endl;

			outfile << std::endl;
			outfile.close();
			break;
		}
	}

	return ERROR; 
}

//! Collect output for surfaces and solids as facets.
//! @param[in] meshData The indexed polyface data.
//! @param[in] isFilled The wireframe display of the mesh has opaque fill.
//! @remarks Only called if _ProcessAsFacets returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) 
{
	/*std::ofstream outfile;

	DictionaryProperties* dictionaryProperties = mGraphicsProcessorEnhancer.getDictionaryProperties();

	outfile.open(filePath, std::ios_base::app);
	outfile << dictionaryProperties->getElementId() << " -------- " << dictionaryProperties->getElementDescriptor() <<"  Color index RGB --------" << std::endl;
	if (meshData.GetDoubleColorCP() != NULL)
	{
		outfile << "Red " << meshData.GetDoubleColorCP()->red << std::endl;
		outfile << "Green " << meshData.GetDoubleColorCP()->green << std::endl;
		outfile << "Blue " << meshData.GetDoubleColorCP()->blue << std::endl;
	}
	outfile.close();
	

	 */
	return ERROR;
}

//! Collect output as a solid primitive.
//! @param[in] primitive The solid primitive data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
#pragma warning( push )
#pragma warning( disable : 4267)
#pragma warning( disable : 4700)
BentleyStatus GraphicsProcessor::_ProcessSolidPrimitive(ISolidPrimitiveCR primitive)
{
	DictionaryProperties* dictionaryProperties = mGraphicsProcessorEnhancer.getDictionaryProperties();	
	std::ofstream outfile;

	dictionaryProperties->setIsPrimitiveSolid(true);

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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			boxDetails.GetCorners(corners);
			boxDetails.GetRange(range);
			boxDetails.GetNonUniformTransform(localToWorld, ax, ay, bx, by);

			boxDetails.TryGetConstructiveFrame(locTWor, worldToLocal);

			localToWorld.Matrix().GetRotationAngleAndVector(vectorRotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);


			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, vectorRotation, qRotation, localToWorld);

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

			// get local to world class to get the X,Y,Z axes 
			boxDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);

			BoxGraphicProperties* boxGraphicProperties = new BoxGraphicProperties();

			// set centroid, area and volume
			mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)boxGraphicProperties);

			// set X,Y,Z axes
			DVec3d columnVectorX, columnVectorY, columnVectorZ;

			columnVectorX = boxDetails.ParameterizationSign() * boxDetails.m_vectorX;
			columnVectorY = boxDetails.ParameterizationSign() * boxDetails.m_vectorY;

			columnVectorZ.CrossProduct(boxDetails.m_vectorX, boxDetails.m_vectorY);
			columnVectorZ = boxDetails.ParameterizationSign() * columnVectorZ;

			boxGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
			mGraphicsProcessorEnhancer.setBoxGraphicProperties(boxDetails, boxGraphicProperties);


		}

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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			coneDetails.GetRange(range);
			coneDetails.GetTransforms(localToWorld, worldToLocal, radiusA, radiusB);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);

			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

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

			// get local to world class to get the X,Y,Z axes 
			coneDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			mGraphicsProcessorEnhancer.processConeAndCylinder(primitive);
		}

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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			extrusionDetails.GetRange(range);
			extrusionDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			extrusionDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);


			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

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

		//mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive);
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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			rotSweepDetails.GetRange(range);
			rotSweepDetails.GetTransforms(localToWorld, worldToLocal);
			rotSweepDetails.TryGetRotationAxis(centerRotation, rotationAxes, sweepRadians);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);
			rotSweepDetails.m_baseCurve->GetStartEnd(curveStart, curveEnd);
						

			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, localToWorld);
			
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

		//mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive);
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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			ruledSweepDetails.GetRange(range);
			ruledSweepDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);


			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

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

		//mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive);
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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			sphereDetails.GetRange(range);
			sphereDetails.m_localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			sphereDetails.m_localToWorld.Matrix().GetQuaternion(qRotation, false);


			primitive.ClosestPoint(sphereDetails.m_localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, sphereDetails.m_localToWorld);

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

			SphereGraphicProperties* sphereGraphicProperties = new SphereGraphicProperties();

			// set centroid, area and volume
			mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)sphereGraphicProperties);
			
			// set spehere properties
			mGraphicsProcessorEnhancer.setSphereGraphicProperties(sphereGraphicProperties);
		}		

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
			outfile << "-------- " << dictionaryProperties->getElementDescriptor() << " --------" << std::endl;
			outfile.close();

			torusDetails.GetRange(range);
			torusDetails.TryGetFrame(centerRotation, rotationAxes, radiusA, radiusB, sweepRadians);
			torusDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);
			localToWorld.Matrix().GetRotationAngleAndVector(rotation);
			localToWorld.Matrix().GetQuaternion(qRotation, false);
			rotationAxes.GetQuaternion(axesQuatRotation, false);


			primitive.ClosestPoint(localToWorld.Origin(), this->mSolidDetails);

			mGraphicsProcessorEnhancer.PrintPrincipalProperties(range, rotation, qRotation, localToWorld);

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

			// get local to world class to get the X,Y,Z axes 
			torusDetails.TryGetConstructiveFrame(localToWorld, worldToLocal);

			TorusGraphicProperties* torusGraphicProperties = new TorusGraphicProperties();

			// set centroid, area and volume
			mGraphicsProcessorEnhancer.PrintPrincipalAreaMoments(primitive, (GraphicProperties*&)torusGraphicProperties);

			// set X,Y,Z axes
			DVec3d columnVectorX, columnVectorY, columnVectorZ;

			columnVectorX = torusDetails.ParameterizationSign() * torusDetails.m_vectorX;
			columnVectorY = torusDetails.ParameterizationSign() * torusDetails.m_vectorY;

			columnVectorZ.CrossProduct(torusDetails.m_vectorX, torusDetails.m_vectorY);
			columnVectorZ = torusDetails.ParameterizationSign() * columnVectorZ;

			torusGraphicProperties->setVectorAxis(columnVectorX, columnVectorY, columnVectorZ);
			mGraphicsProcessorEnhancer.setTorusGraphicProperties(torusDetails, sweepRadians, centerRotation, torusGraphicProperties);
		}

	}
	break;

	case SolidPrimitiveType::SolidPrimitiveType_None:
	{
		outfile.open(filePath, std::ios_base::app);

		outfile << std::fixed;
		outfile << "None Primitives type" << std::endl;
		outfile << "None Primitives type" << std::endl;
		outfile << "None Primitives type" << std::endl;

		outfile.close();
	}

	default:
		// set PrimitiveGraphicProperties to nullptr,because the primitive was not identified
		//dictionaryProperties->getGraphicProperties()->setPrimitiveGraphicProperties(nullptr);
		break;
	}

	return ERROR;
}

