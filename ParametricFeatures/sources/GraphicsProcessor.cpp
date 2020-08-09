#include "../headers/GraphicsProcessor.h"

GraphicsProcessor::GraphicsProcessor()	
{
	filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	//filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

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
		
	return SUCCESS;
}
#pragma warning( pop ) 


//! Collect output as a bspline surface.
//! @param[in] surface The bspline surface data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
BentleyStatus GraphicsProcessor::_ProcessSurface(MSBsplineSurfaceCR surface)
{	
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << "-------------------------------- MSBsplineSurfaceCR surface --------------------------------" << std::endl;
	outfile << std::endl;
	outfile << std::endl;
	outfile.close();

	//mGraphicsProcessorEnhancer.processMSBsplineSurface(surface);

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
	outfile <<"_ProcessBody"<< std::endl;
	outfile << std::fixed;
	outfile.close();

	//SolidUtil::Debug::DumpEntity(entity, L"DumpEntity");
	//SolidUtil::Debug::DumpSubEntity(entity, L"DumpSubEntity");

		
	DictionaryProperties* dictionaryProperties = mGraphicsProcessorEnhancer.getDictionaryProperties();
	dictionaryProperties->setIsSmartSolid(true);

		auto entityType = entity.GetEntityType();
		switch (entityType)
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
				outfile.open(filePath, std::ios_base::app);
				outfile << "In SolidKernel Entity is: Sheet " << ISolidKernelEntity::KernelEntityType::EntityType_Sheet << std::endl;
				outfile << std::endl;
				outfile.close();
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

			default:
				break;
		}
// Element is getting parsed as BRep Faceted
#if false 
		if (mGraphicsProcessorEnhancer.processEntityAsFacetedBRep(entity))
		{
			outfile.open(filePath, std::ios_base::app);
			outfile << "Element or Entity Processed Correctly" << std::endl;
			outfile << std::endl;
			outfile.close();
		}
#endif

#if true
		if (entityType == ISolidKernelEntity::KernelEntityType::EntityType_Solid || entityType == ISolidKernelEntity::KernelEntityType::EntityType_Sheet)
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


			outfile.open(filePath, std::ios_base::app);
			outfile << "Entity------------ " << std::endl;
			outfile << "Edges Entity: " << nEdges << std::endl;
			outfile << "Faces Entity: " << nFaces << std::endl;
			outfile << "Vertices Entity: " << nVertices << std::endl;
			outfile << std::endl;
			outfile.close();

			SolidUtil::Debug::DumpEntity(entity, L"DumpEntity");

			SolidEntityGraphicProperties* solidKernelEntity = new SolidEntityGraphicProperties();
			solidKernelEntity->setBRepTypeEnum((int)entityType);

			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- Processing BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile.close();

			//Mesh Polyface converter WORKING REPRESENTATION
#if false
			//mGraphicsProcessorEnhancer.ProcessAsMeshElement(solidKernelEntity);

			outfile.open(filePath, std::ios_base::app);
			outfile << "Faceted BREP / ShellBased with Mesh Polyface" << std::endl;
			outfile << std::endl;
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

				outfile.open(filePath, std::ios_base::app);
				outfile << "EDGE Sub Entity: " << std::endl;
				outfile << std::endl;
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
					
					outfile.open(filePath, std::ios_base::app);
					outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
					outfile << std::endl;
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
			std::vector<std::vector<ShapesGraphicProperties*>> subShapesLoopVec = std::vector<std::vector<ShapesGraphicProperties*>>();

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

							outfile.open(filePath, std::ios_base::app);
							outfile << "-------- EDGE Sub Entity: " << std::endl;
							outfile << std::endl;
							outfile.close();

							bool addToDictionary = false;
							mGraphicsProcessorEnhancer.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties, addToDictionary);

							curveEdgesEval->AreStartEndAlmostEqual();

							DVec3d cDX, cDY, cDZ;

							cDX = shapesGraphicProperties->getVectorAxisX();
							cDY = shapesGraphicProperties->getVectorAxisY();
							cDZ = shapesGraphicProperties->getVectorAxisZ();

							outfile.open(filePath, std::ios_base::app);
							outfile << std::endl;
							outfile << "Curve XY Plane: " << std::endl;
							outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
							outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
							outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
							outfile.close();
						}
						else
							parseEdgeLoop = true;
					}

					//Clear the previous stored faces
					subEntitiesFaces.clear();

					//Get te faces of the current edge
					SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

					std::vector<ShapesGraphicProperties*> loopVector;

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
												outfile.open(filePath, std::ios_base::app);
												outfile << "loopAleadyParsed = true" << std::endl;
												outfile << std::endl;
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
								outfile.open(filePath, std::ios_base::app);
								outfile << "-------- EDGE LOOP Sub Entities: " << std::endl;
								outfile << std::endl;
								outfile.close();

								for (auto edgeLoop : edgeLoopSubEntities)
								{
									ISubEntityCR edgeRefLoop = *edgeLoop;
									CurveVectorPtr loopEval;

									outfile.open(filePath, std::ios_base::app);
									outfile << std::endl;
									outfile << "Curve of the loop: " << std::endl;
									outfile << std::endl;
									outfile.close();

									shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

									if (SolidUtil::Convert::SubEntityToCurveVector(loopEval, edgeRefLoop) == SUCCESS)
									{
										bool addToDictionary = false;
										mGraphicsProcessorEnhancer.processShapesCurvesVector(*loopEval, false, &*shapesGraphicProperties, addToDictionary);

										DVec3d cDX, cDY, cDZ;

										cDX = shapesGraphicProperties->getVectorAxisX();
										cDY = shapesGraphicProperties->getVectorAxisY();
										cDZ = shapesGraphicProperties->getVectorAxisZ();

										outfile.open(filePath, std::ios_base::app);
										outfile << std::endl;
										outfile << "Curve XY Plane: " << std::endl;
										outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
										outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
										outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
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

						outfile.open(filePath, std::ios_base::app);
						outfile << "FACE of the Edge: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
						outfile << std::endl;
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

				outfile.open(filePath, std::ios_base::app);
				outfile << "--------- FACE Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
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

						//msBsplineSurfaceGraphicProperties->setFaceId(faceID);
						msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
						msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

						mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

						//Add the face to the solidKernelEntity
						solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
					}
					break;
					case IGeometry::GeometryType::SolidPrimitive:
					{
						outfile.open(filePath, std::ios_base::app);
						outfile << "---------------- IGeometry::GeometryType::SolidPrimitive ----------------" << std::endl;
						outfile << std::endl;
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

				outfile.open(filePath, std::ios_base::app);
				outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
				outfile << std::endl;
				outfile.close();

				bvector<double> uParams, vParams;
				bvector<DPoint2d> uvParams;
				bvector<DPoint3d> gridPoints;

				
				if (SolidUtil::Convert::SubEntityToGeometry(geomFacesEval, faceRef, *dgnModelRef) == SUCCESS)
				{
					switch (geomFacesEval->GetGeometryType())
					{
					case IGeometry::GeometryType::BsplineSurface:
					{
						MSBsplineSurfaceCR msBspline = *geomFacesEval->GetAsMSBsplineSurface();
						msBspline.EvaluateUniformGrid(msBspline.GetNumUPoles(), msBspline.GetNumVPoles(), uvParams, gridPoints);
						gridPoints.clear();
						msBspline.EvaluateUniformGrid(msBspline.GetNumUPoles(), msBspline.GetNumVPoles(), uParams, vParams, gridPoints);
						MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = new MSBsplineSurfaceGraphicProperties();

						msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
						msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

						bool addToDictionary = false;
						mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, *&msBsplineSurfaceGraphicProperties, addToDictionary);

						outfile.open(filePath, std::ios_base::app, sizeof(std::string));
						outfile << "uParams: " << uParams.size() << std::endl;
						outfile << "vParams: " << vParams.size() << std::endl;
						outfile << "uvParams: " << uvParams.size() << std::endl;
						outfile << "gridPoints: " << gridPoints.size() << std::endl;
						outfile << std::endl;
						outfile.close();

						//Add the face to the solidKernelEntity
						solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
					}
					break;
					case IGeometry::GeometryType::SolidPrimitive:
					{
						outfile.open(filePath, std::ios_base::app);
						outfile << "IGeometry::GeometryType::SolidPrimitive: " << (int)IGeometry::GeometryType::SolidPrimitive << std::endl;
						outfile << std::endl;
						outfile.close();
						ISolidPrimitiveR  prim = *geomFacesEval->GetAsISolidPrimitive();
						_ProcessSolidPrimitive(prim);
					}
					break;
					case IGeometry::GeometryType::Polyface:
					{
						outfile.open(filePath, std::ios_base::app);
						outfile << "IGeometry::GeometryType::Polyface: " << (int)IGeometry::GeometryType::Polyface << std::endl;
						outfile << std::endl;
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

			//Edges start dependences BSpline Surface 
#if false
			//Clear the faces store previously
			subEntitiesFaces.clear();
			subEntitiesVertices.clear();

			std::vector<std::vector<ShapesGraphicProperties*>> subShapesLoopVec = std::vector<std::vector<ShapesGraphicProperties*>>();
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

						outfile.open(filePath, std::ios_base::app);
						outfile << "-------- EDGE Sub Entity: " << std::endl;
						outfile << std::endl;
						outfile.close();

						bool addToDictionary = false;
						mGraphicsProcessorEnhancer.processShapesCurvesVector(*curveEdgesEval, false, &*shapesGraphicProperties, addToDictionary);

						//ADD ???
						//curveEdgesEval->FixupXYOuterInner(true);

						curveEdgesEval->AreStartEndAlmostEqual();

						DVec3d cDX, cDY, cDZ;

						cDX = shapesGraphicProperties->getVectorAxisX();
						cDY = shapesGraphicProperties->getVectorAxisY();
						cDZ = shapesGraphicProperties->getVectorAxisZ();

						outfile.open(filePath, std::ios_base::app);
						outfile << std::endl;
						outfile << "Curve XY Plane: " << std::endl;
						outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
						outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
						outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
						outfile.close();
					}
					else
						parseEdgeLoop = true;
				}	
				
				//Clear the previous stored faces
				subEntitiesFaces.clear();

				//Get te faces of the current edge
				SolidUtil::GetEdgeFaces(subEntitiesFaces, edgeRef);

				std::vector<ShapesGraphicProperties*> loopVector;

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
											outfile.open(filePath, std::ios_base::app);
											outfile << "loopAleadyParsed = true" << std::endl;
											outfile << std::endl;
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
							outfile.open(filePath, std::ios_base::app);
							outfile << "-------- EDGE LOOP Sub Entities: " << std::endl;
							outfile << std::endl;
							outfile.close();

							for (auto edgeLoop : edgeLoopSubEntities)
							{
								ISubEntityCR edgeRefLoop = *edgeLoop;
								CurveVectorPtr loopEval;

								outfile.open(filePath, std::ios_base::app);
								outfile << std::endl;
								outfile << "Curve of the loop: " << std::endl;
								outfile << std::endl;
								outfile.close();

								shapesGraphicProperties = new ShapesGraphicProperties(ShapesTypeEnum::SHAPE);

								if (SolidUtil::Convert::SubEntityToCurveVector(loopEval, edgeRefLoop) == SUCCESS)
								{
									//ADD ???
									//loopEval->FixupXYOuterInner(true);

									bool addToDictionary = false;
									mGraphicsProcessorEnhancer.processShapesCurvesVector(*loopEval, false, &*shapesGraphicProperties, addToDictionary);

									DVec3d cDX, cDY, cDZ;

									cDX = shapesGraphicProperties->getVectorAxisX();
									cDY = shapesGraphicProperties->getVectorAxisY();
									cDZ = shapesGraphicProperties->getVectorAxisZ();

									outfile.open(filePath, std::ios_base::app);
									outfile << std::endl;
									outfile << "Curve XY Plane: " << std::endl;
									outfile << "Direction [X] = " << cDX.x << ", " << cDX.y << ", " << cDX.z << std::endl;
									outfile << "Direction [Y] = " << cDY.x << ", " << cDY.y << ", " << cDY.z << std::endl;
									outfile << "Direction [Z] = " << cDZ.x << ", " << cDZ.y << ", " << cDZ.z << std::endl;
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

					outfile.open(filePath, std::ios_base::app);
					outfile << "FACE of the Edge: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
					outfile << std::endl;
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

				outfile.open(filePath, std::ios_base::app);
				outfile << "--------- FACE Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
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

						//msBsplineSurfaceGraphicProperties->setFaceId(faceID);
						msBsplineSurfaceGraphicProperties->setFaceId(faceID.entityId);
						msBsplineSurfaceGraphicProperties->setNodeId(faceID.nodeId);

						mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

						//Add the face to the solidKernelEntity
						solidKernelEntity->addBSplineSurfaceFace(msBsplineSurfaceGraphicProperties);
					}
					break;
					case IGeometry::GeometryType::SolidPrimitive:
					{
						outfile.open(filePath, std::ios_base::app);
						outfile << "---------------- IGeometry::GeometryType::SolidPrimitive ----------------" << std::endl;
						outfile << std::endl;
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


				outfile.open(filePath, std::ios_base::app);
				outfile << "EDGE Sub Entity: " << std::endl;
				outfile << std::endl;
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
								outfile.open(filePath, std::ios_base::app, sizeof(std::string));
								outfile << "Point [X]: " << vertexPoint.x << std::endl;
								outfile << "Point [Y]: " << vertexPoint.y << std::endl;
								outfile << "Point [Z]: " << vertexPoint.z << std::endl;
								outfile << std::endl;
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

					outfile.open(filePath, std::ios_base::app);
					outfile << "--------- FACE -------- Entity: " << faceID.nodeId << " ID: " << faceID.entityId << std::endl;
					outfile << std::endl;
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

								mGraphicsProcessorEnhancer.processMSBsplineSurface(msBspline, msBsplineSurfaceGraphicProperties);

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
									outfile.open(filePath, std::ios_base::app, sizeof(std::string));
									outfile << "Vertex Point [X]: " << vertexPoint.x << std::endl;
									outfile << "Vertex Point [Y]: " << vertexPoint.y << std::endl;
									outfile << "Vertex Point [Z]: " << vertexPoint.z << std::endl;
									outfile << std::endl;
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
			outfile.open(filePath, std::ios_base::app);
			outfile << "-------------------------------- End BREP Entiy --------------------------------" << std::endl;
			outfile << std::endl;
			outfile << std::endl;
			outfile.close();

			subEntitiesEdges.clear();
			subEntitiesFaces.clear();

			//dictionaryProperties->addGraphicProperties(solidKernelEntity);
			this->mGraphicsProcessorEnhancer.getElementBundle()->setGraphicProperties(*solidKernelEntity);
		}
#endif

	return SUCCESS;
}

//! Collect output for surfaces and solids as facets.
//! @param[in] meshData The indexed polyface data.
//! @param[in] isFilled The wireframe display of the mesh has opaque fill.
//! @remarks Only called if _ProcessAsFacets returns true.
//! @return SUCCESS if handled.
BentleyStatus GraphicsProcessor::_ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) 
{
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);
	outfile << "-------------------------------- PolyfaceQueryCR - meshData --------------------------------" << std::endl;

	//std::vector<double> colourVector;

	////FloatRgb* colour = const_cast<FloatRgb*>(colour1);
	//auto color2 = meshData.GetColorIndexCP();
	//auto color3 = meshData.GetDoubleColorCP();
	//auto color4 = meshData.GetFloatColorCP();
	////if (colour2 != nullptr) {
	////	colourVector.push_back(static_cast<double>(colour->red));
	////	colourVector.push_back(static_cast<double>(colour->green));
	////	colourVector.push_back(static_cast<double>(colour->blue));
	////}

	//if (color3!=nullptr) {
	//	colourVector.push_back(static_cast<double>(color3->red));
	//	colourVector.push_back(static_cast<double>(color3->green));
	//	colourVector.push_back(static_cast<double>(color3->blue));
	//}

	//if (color4!=nullptr) {
	//	colourVector.push_back(static_cast<double>(color4->red));
	//	colourVector.push_back(static_cast<double>(color4->green));
	//	colourVector.push_back(static_cast<double>(color4->blue));
	//}
	//if (!colourVector.empty()) {
	//	outfile << "color0 " << colourVector.at(0) << std::endl;
	//}
	//outfile << "color1 " << color2 << std::endl;


	outfile << std::endl;
	outfile << std::endl;
	outfile.close();

	DictionaryProperties* dictionaryProperties = mGraphicsProcessorEnhancer.getDictionaryProperties();

	bvector<PolyfaceHeaderPtr> meshes;
	PolyfaceHeaderPtr header = PolyfaceHeader::CreateVariableSizeIndexed();
	header->CopyFrom(meshData);
	header->Transform(m_currentTransform);
	meshes.push_back(header);

	BRepGraphicProperties* bRepGraphicProperties = new BRepGraphicProperties();

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
		bRepGraphicProperties->addSolidEntityGraphicProperties(solidKernelEntity);
	}
	
	//dictionaryProperties->addGraphicProperties(bRepGraphicProperties);
	this->mGraphicsProcessorEnhancer.getElementBundle()->setGraphicProperties(*bRepGraphicProperties);

	return SUCCESS;
}

//! Collect output as a solid primitive.
//! @param[in] primitive The solid primitive data.
//! @return SUCCESS if handled, return ERROR to output according to _ProcessBody, _ProcessFacets, and _ProcessCurveVector rules.
#pragma warning( push )
#pragma warning( disable : 4267)
#pragma warning( disable : 4700)
BentleyStatus GraphicsProcessor::_ProcessSolidPrimitive(ISolidPrimitiveCR primitive)
{
	mGraphicsProcessorEnhancer.processSolidPrimitives(primitive);

	return SUCCESS;
}

void GraphicsProcessor::_AnnounceElemDisplayParams(ElemDisplayParamsCR displayParams)
{

	//ElemDisplayParamsCR d = displayParams;
	//ElemDisplayParamsCP d = &displayParams;

	this->mGraphicsProcessorEnhancer.getElementBundle()->setElemDisplayParamsCR(displayParams);
	this->mGraphicsProcessorEnhancer.getElementBundle()->setColor(displayParams.GetLineColorTBGR());
	this->mGraphicsProcessorEnhancer.getElementBundle()->setTransparency(displayParams.GetTransparency());

	std::string filepath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);

	UInt32 color;

	color = displayParams.GetLineColorTBGR();
	int blue1 = (color >> 16) & 0xFF;
	int green1 = (color >> 8) & 0xFF;
	int red1 = color & 0xFF;

	outfile << "RGB1 =" << red1 << "," << green1 << "," << blue1 << std::endl;
	//outfile.close();


	outfile << "transparency =" << displayParams.GetTransparency() << std::endl;

	auto level = displayParams.GetLevel();

	auto model = ISessionMgr::GetActiveDgnModelRefP();
	UInt colorOut;
	bool ov;
	mdlLevel_getColor(&colorOut, &ov, model, level);
	outfile << "level " << level << " , " << &colorOut << std::endl;
	outfile << "level color"<< colorOut<<" , "<<& colorOut << std::endl;

		int blue3 = (colorOut >> 16) & 0xFF;
		int green3 = (colorOut >> 8) & 0xFF;
		int red3 = colorOut & 0xFF;

		outfile << "colorOut RGB =" << red3 << "," << green3 << "," << blue3 << std::endl;

	outfile << "level  =" << displayParams.GetLevel() << std::endl;
	//displayParams.GetMaterial()->

	//if (!displayParams.IsLineColorTBGR()) {
	//	color = displayParams.GetLineColorTBGR();
	//	int blue3 = (color >> 16) & 0xFF;
	//	int green3 = (color >> 8) & 0xFF;
	//	int red3 = color & 0xFF;

	//	outfile << "RGB3 =" << red3 << "," << green3 << "," << blue3 << std::endl;
	//}
	//else {
	//	color = displayParams.GetLineColor();
	//	auto rez = ISessionMgr::GetActiveDgnFile()->GetColorMapP();

	//	auto colorDefinition = rez->GetColor(color);
	//	auto rgbColorDefinition = colorDefinition.m_rgb;
	//	int blue2 = rgbColorDefinition.blue & 0xFF;
	//	int green2 = rgbColorDefinition.green & 0xFF;
	//	int red2 = rgbColorDefinition.red & 0xFF;

	//	outfile << "RGB2 =" << red2 << "," << green2 << "," << blue2 << std::endl;
	//}
	outfile.close();
}

void GraphicsProcessor::_AnnounceTransform(TransformCP trans)
{
	if (trans)
		m_currentTransform = *trans;
	else
		m_currentTransform.InitIdentity();
}

