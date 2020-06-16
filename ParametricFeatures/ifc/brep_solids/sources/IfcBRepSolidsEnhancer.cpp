#include "../headers/IfcBRepSolidsEnhancer.h"

IfcBRepSolidsEnhancer::IfcBRepSolidsEnhancer()
{
}

void IfcBRepSolidsEnhancer::enhanceIfcBRepSolidsEnhancer(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	std::vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());
			for (GraphicProperties* graphicProperties : dictionaryProperties.getGraphicPropertiesVector())
			{
				//SolidEntityGraphicProperties* brepSolidsKernelEntity = dynamic_cast<SolidEntityGraphicProperties*>(graphicProperties);
				BRepGraphicProperties* brepSolidsKernelEntity = dynamic_cast<BRepGraphicProperties*>(graphicProperties);
				if (brepSolidsKernelEntity != nullptr)
				{
					//Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildGeometricRepresentationBsplineSurface(brepSolidsKernelEntity, ifcElementBundle, file);
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildGeometricRepresentationFacetBrep(brepSolidsKernelEntity, ifcElementBundle, file);
					if (ifcRepresentationItem != nullptr)
					{
						ifcElementBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(graphicProperties, ifcRepresentationItem));
						//ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}
}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationBsplineSurface(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcAdvancedFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();
	IfcEntityList* entityList = new IfcEntityList();
	Ifc4::IfcPolyLoop* polySharedLoop = nullptr;
	std::vector<Ifc4::IfcVertexLoop*> vertexLoopVec;
	/*for (auto point : brepSolidsKernelEntity->mVertexLoop)
	{
		Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
		Ifc4::IfcVertex* vertex(new Ifc4::IfcVertexPoint(cP));
		Ifc4::IfcVertexLoop* vLoop = new Ifc4::IfcVertexLoop(vertex);
		vertexLoopVec.push_back(vLoop);
	}*/
	
	for (MSBsplineSurfaceGraphicProperties* msBsplineGraphicProperties : brepSolidsKernelEntity->getBSplineSurfaceFacesVector())
	{
		if (msBsplineGraphicProperties != nullptr)
		{
			//Create IfcCartesianPoint List 
			IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>* tempCartesianPointList = new IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>();

			//Create a FaceBound list
			IfcTemplatedEntityList<Ifc4::IfcFaceBound>* tempIfcFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();


			//TODO[SB] Check the surface poles
			//Get the control point UV of the FACE surface
			std::vector<std::vector<DPoint3d>> controlPointsPatch = msBsplineGraphicProperties->getControlPoints();
			for (size_t i = 0; i < msBsplineGraphicProperties->getNumUPoles(); i++)
			{
				std::vector<Ifc4::IfcCartesianPoint*> cartesianPointsUV;
				std::vector<DPoint3d> tempCP = controlPointsPatch.at(i);

				for (size_t j = 0; j < msBsplineGraphicProperties->getNumVPoles(); j++)
				{

					Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(tempCP.at(j));
					cartesianPointsUV.push_back(cP);
				}
				tempCartesianPointList->push(cartesianPointsUV);
			}

			//Collect all the UV IfcCartesianPoint for the surface
			boost::shared_ptr<IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>> controlPoints(tempCartesianPointList);


			Ifc4::IfcRationalBSplineSurfaceWithKnots* bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
				msBsplineGraphicProperties->getUDegree(),
				msBsplineGraphicProperties->getVDegree(),
				controlPoints,
				Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				msBsplineGraphicProperties->getUIsCLosed(),
				msBsplineGraphicProperties->getVIsCLosed(),
				msBsplineGraphicProperties->getIsSelfIntersect(),
				msBsplineGraphicProperties->getUKnotsMultiplicity(),
				msBsplineGraphicProperties->getVKnotsMultiplicity(),
				msBsplineGraphicProperties->getUKnots(),
				msBsplineGraphicProperties->getVKnots(),
				Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED,
				msBsplineGraphicProperties->getWeights()
			);

			/*Ifc4::IfcBSplineSurface* bSplineSurface = new Ifc4::IfcBSplineSurface(
				msBsplineGraphicProperties->getUDegree(),
				msBsplineGraphicProperties->getVDegree(),
				controlPoints,
				Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				msBsplineGraphicProperties->getUIsCLosed(),
				msBsplineGraphicProperties->getVIsCLosed(),
				msBsplineGraphicProperties->getIsSelfIntersect()
			);*/

			/*Ifc4::IfcBSplineSurfaceWithKnots* bSplineSurface = new Ifc4::IfcBSplineSurfaceWithKnots(
				msBsplineGraphicProperties->getUDegree(),
				msBsplineGraphicProperties->getVDegree(),
				controlPoints,
				Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				msBsplineGraphicProperties->getUIsCLosed(),
				msBsplineGraphicProperties->getVIsCLosed(),
				msBsplineGraphicProperties->getIsSelfIntersect(),
				msBsplineGraphicProperties->getUKnotsMultiplicity(),
				msBsplineGraphicProperties->getVKnotsMultiplicity(),
				msBsplineGraphicProperties->getUKnots(),
				msBsplineGraphicProperties->getVKnots(),
				Ifc4::IfcKnotType::IfcKnotType_UNSPECIFIED
			);*/

//Curves Edges of te Entity associated with faceID
#if true
			IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* continuosOrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();
			
			//Get the correct edges based on the faceID
			for (SolidEdge* solidEdge: ifcElementBundle->getSolidEdgesCollection())
			{
				//Check if they belongs to the same entity
				if (solidEdge->nodeID == msBsplineGraphicProperties->getNodeId())
				{
					//Check both faces if they exist
					for (auto id : solidEdge->faceID)
					{
						if (id == msBsplineGraphicProperties->getFaceId())
						{
							/*	IfcEdgeLoop RULES

								1 IsClosed		The start vertex of the first edge shall be the same as the end vertex of the last edge. 
												This ensures that the path is closed to form a loop.
								2 IsContinuous	The end vertex of each edge shall be the same as the start vertex of its successor.
							*/
							if (solidEdge->isClosed)
							{

								//IfcOrientedEdge closed 
								IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* singleOrientedEdge = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();
								//Push the IfcOrientedEdge to the list
								singleOrientedEdge->push(solidEdge->edge);

								boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> singleEdgeLoop(singleOrientedEdge);

								//Store it as a single IfcEdgeLoop and define the IfcFaceOuterBound
								Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(singleEdgeLoop);

								if(solidEdge->type == 2)//(int)CurvesBoundaryTypeEnum::OUTER)
								{
									Ifc4::IfcFaceOuterBound* faceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);			
									//Add it to the IfcFaceOuterBound List for the currecnt face
									tempIfcFaceBoundList->push(faceOuterBound);
								}
								else if (solidEdge->type == 3)//(int)CurvesBoundaryTypeEnum::INNER)
								{
									//Orientation: 
									// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
									// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
									Ifc4::IfcFaceBound* faceBound = new Ifc4::IfcFaceBound(edgeLoop, true);

									//Add it to the IfcFaceOuterBound List for the currecnt face
									tempIfcFaceBoundList->push(faceBound);
								}							

							}
							else
							{
//Pointer SolidEge nested Blocks
#if false
								Ifc4::IfcEdgeLoop* edgeLoop = nullptr;
								ContinuosEdge* head = (ContinuosEdge*)solidEdge;

								if (head->edgeLoop == NULL)
								{
									//IfcOrientedEdge list
									IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* tempOrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

									ContinuosEdge* temp = head;
									while (temp != NULL)
									{
										//Push the IfcOrientedEdge to the list
										tempOrientedEdgesList->push(temp->edge);
										temp = temp->next;
									}

									//The edges saved here are continuos 
									boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(tempOrientedEdgesList);

									//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
									edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

									//Save the same IfcEdgeLoop instance to avoid duplicates loop creation
									head->edgeLoop = edgeLoop;
								}
								else
									edgeLoop = head->edgeLoop;
								
								//Ifc4::IfcFaceOuterBound* faceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);

								//Orientation: 
								// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
								// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
								Ifc4::IfcFaceBound* faceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, false);

								//Add it to the IfcFaceOuterBound List for the currecnt face
								tempIfcFaceBoundList->push(faceOuterBound);
#endif
								continuosOrientedEdgesList->push(solidEdge->edge);
							}
							break;
						}
					}
				}
			}

			//The edges saved here are continuos 
			//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(continuosOrientedEdgesList);

			////Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
			//Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

			////Orientation: 
			//// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
			//// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
			//Ifc4::IfcFaceBound* faceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, false);

			////Add it to the IfcFaceOuterBound List for the currecnt face
			//tempIfcFaceBoundList->push(faceOuterBound);
#endif

//Use of the poly loop For internal bounds MSBSplineSurface
#if false
			for (auto bound : msBsplineGraphicProperties->getBoundsVectorPoints())
			{
				//Create IfcCartesianPoint List 
				IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
				for (DPoint3d point : bound)
				{
					Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
					cartesianPointList->push(cP);
				}

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(cartesianPointList);
				Ifc4::IfcPolyLoop* polyLoop = new Ifc4::IfcPolyLoop(polyControlPoints);

				//Orientation: 
				// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
				// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
				Ifc4::IfcFaceBound* newfaceOuterBound = new Ifc4::IfcFaceBound(polyLoop, false);
				//Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polyLoop, true);


				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(newfaceOuterBound);
			}
#endif

//Edges of solid on poly loop representation
#if false			
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* sharedCartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
			for (auto boundPoints : brepSolidsKernelEntity->getBoundsPoints())
			{
				//Check if they belongs to the same entity
				if (boundPoints->nodeID == msBsplineGraphicProperties->getNodeId())
				{
					if (boundPoints->isShared)
					{
						if (!boundPoints->isCreated)
						{
							//Check both faces if they exist
							for (auto id : boundPoints->faceID)
							{
								if (id == msBsplineGraphicProperties->getFaceId())
								{
									//Create IfcCartesianPoint List 
									for (DPoint3d point : boundPoints->pointsVector)
									{
										Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
										sharedCartesianPointList->push(cP);
									}
									boundPoints->isCreated = true;
								}
							}
						}
					}
					else
					{
						for (auto id : boundPoints->faceID)
						{
							if (id == msBsplineGraphicProperties->getFaceId())
							{
								if (boundPoints->isClosed)
								{
									//Create IfcCartesianPoint List 
									IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
									for (DPoint3d point : boundPoints->pointsVector)
									{
										Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
										cartesianPointList->push(cP);
									}

									boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(cartesianPointList);
									Ifc4::IfcPolyLoop* polyLoop = new Ifc4::IfcPolyLoop(polyControlPoints);

									//Orientation: 
									// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
									// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
									//Ifc4::IfcFaceBound* faceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, false);
									Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polyLoop, true);


									//Add it to the IfcFaceOuterBound List for the currecnt face
									tempIfcFaceBoundList->push(newfaceOuterBound);
								}
							}
						}
					}
				}
			}

			if (polySharedLoop == nullptr)
			{
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(sharedCartesianPointList);
				polySharedLoop = new Ifc4::IfcPolyLoop(polyControlPoints);
			}
			//Orientation: 
			// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
			// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
			//Ifc4::IfcFaceBound* newfaceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, false);
			Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polySharedLoop, true);


			//Add it to the IfcFaceOuterBound List for the currecnt face
			tempIfcFaceBoundList->push(newfaceOuterBound);

#endif

//Vertex Loop of the entity
#if false
			for (auto v : vertexLoopVec)
			{
				Ifc4::IfcFaceBound* newOuterBound = new Ifc4::IfcFaceBound(v, true);
				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(newOuterBound);
			}
#endif
			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> faceBoundsList(tempIfcFaceBoundList);

			//Create the face with all the bounds			
			// SameSense: This flag indicates whether the sense of the surface normal agrees with (TRUE), or opposes (FALSE), 
			// the sense of the topological normal to the face.

			//Ifc4::IfcFace* advanceFace = new Ifc4::IfcFace(faceBoundsList);
			Ifc4::IfcFaceSurface* advanceFace = new Ifc4::IfcFaceSurface(faceBoundsList, bSplineSurface, true);
			//Ifc4::IfcAdvancedFace* advanceFace = new Ifc4::IfcAdvancedFace(faceBoundsList, bSplineSurface, true);

			tempIfcAdvancedFaceList->push(advanceFace);	

			//single face as shell
			/*ifcSingleFaceList->push(advanceFace);
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advancedFaces(ifcSingleFaceList);
			Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(advancedFaces);
			entityList->push(openShell);*/
		}
	}

	//Collect all the faces created
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advancedFaces(tempIfcAdvancedFaceList);

	//Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(advancedFaces);
	Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(advancedFaces);

	entityList->push(closedShell);
	//entityList->push(openShell);
	boost::shared_ptr<IfcEntityList> shellModel(entityList);

	Ifc4::IfcShellBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcShellBasedSurfaceModel(shellModel);


	//Create a closedShell from the advancedFaces list
	//Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(advancedFaces);
	
	//Ifc4::IfcConnectedFaceSet* closedShell = new Ifc4::IfcConnectedFaceSet(advancedFaces);
		
	//Create the IfcAdvancedBrep
	//Ifc4::IfcAdvancedBrep* advanceBrep = new Ifc4::IfcAdvancedBrep(closedShell);
	//Ifc4::IfcFacetedBrep* advanceBrep = new Ifc4::IfcFacetedBrep(closedShell);
	
	//file.addEntity(advanceBrep);
	//Ifc4::IfcSolidModel* shellBasedSurfaceModel(advanceBrep);
	
	Ifc4::IfcGeometricRepresentationItem * geomItem = shellBasedSurfaceModel;

	return geomItem;
}
#pragma warning (pop)

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationFacetBrep(BRepGraphicProperties * bRepGraphicProperties, IfcElementBundle *& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcGeometricRepresentationItem * geomItem = nullptr;

#if false
	IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();

	//Shared Boundaries map
	std::vector<std::map<int, Ifc4::IfcPolyLoop*>> sharedClosedPolyLoops;
	std::map<int, IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>*> continuosCartesianPoints;
	std::map<int, Ifc4::IfcPolyLoop*> sharedOpenPolyLoops;

	for (auto faceNodePair : bRepGraphicProperties->getNodeIDFaceIDVector())
	{
		//Store the FaceID of the shared Bounds Not Closed
		std::vector<int> sharedBoundFaceID;

		int nodeID = std::get<0>(faceNodePair);
		int face = std::get<1>(faceNodePair);

		//Create a FaceBound list
		IfcTemplatedEntityList<Ifc4::IfcFaceBound>* tempIfcFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();
		for (auto boundPoints : bRepGraphicProperties->getBoundsPoints())
		{
			if (nodeID == boundPoints->nodeID)
			{
				if (boundPoints->isClosed) //Check if it's closed
				{
					if (boundPoints->isShared)
					{
						if (!boundPoints->isCreated)
						{
							//Create IfcCartesianPoint List 
							IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
							for (DPoint3d point : boundPoints->pointsVector)
							{
								Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
								cartesianPointList->push(cP);
							}

							boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(cartesianPointList);
							Ifc4::IfcPolyLoop* polyLoop = new Ifc4::IfcPolyLoop(polyControlPoints);
							Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polyLoop, true);

							//Add it to the IfcFaceOuterBound List for the current face
							tempIfcFaceBoundList->push(newfaceOuterBound);

							boundPoints->isCreated = true;

							for (auto fID : boundPoints->faceID)
							{
								//Don't add the one from the face just created
								if (fID != face)
								{
									std::map<int, Ifc4::IfcPolyLoop*> pLoopPair;
									pLoopPair.insert({ fID, polyLoop });
									sharedClosedPolyLoops.push_back(pLoopPair);
								}
							}
						}
						else
						{
							for (auto polyPair : sharedClosedPolyLoops)
							{
								if (searchOnMap(polyPair, face) != NULL)
								{
									Ifc4::IfcPolyLoop* polyLoop = searchOnMap(polyPair, face);
									Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polyLoop, true);

									//Add it to the IfcFaceOuterBound List for the current face
									tempIfcFaceBoundList->push(newfaceOuterBound);
									//Remove to avoid repetition the one from the face just created
									polyPair.erase(face);
								}
							}
						}
					}
					else if (boundPoints->faceID.front() == face) //It's not shared, so only 1 face
					{
						//Create IfcCartesianPoint List 
						IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
						for (DPoint3d point : boundPoints->pointsVector)
						{
							Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
							cartesianPointList->push(cP);
						}

						boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(cartesianPointList);
						Ifc4::IfcPolyLoop* polyLoop = new Ifc4::IfcPolyLoop(polyControlPoints);
						Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polyLoop, true);

						//Add it to the IfcFaceOuterBound List for the current face
						tempIfcFaceBoundList->push(newfaceOuterBound);
					}
				}
				else //if (boundPoints->isShared)
				{
					if (!boundPoints->isCreated)
					{
						if (searchOnMap(continuosCartesianPoints, face) != NULL)
						{
							auto sharedCartesianPointList = searchOnMap(continuosCartesianPoints, face);
							for (DPoint3d point : boundPoints->pointsVector)
							{
								Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
								sharedCartesianPointList->push(cP);
							}

							boundPoints->isCreated = true;
						}
						else
						{
							IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* sharedCartesianPointList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
							//Create IfcCartesianPoint List 
							for (DPoint3d point : boundPoints->pointsVector)
							{
								Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
								sharedCartesianPointList->push(cP);
							}

							boundPoints->isCreated = true;

							for (auto fID : boundPoints->faceID)
							{
								continuosCartesianPoints.insert({ fID, sharedCartesianPointList });
								sharedBoundFaceID.push_back(fID);
							}
						}
					}
				}
			}
		}

		//Search for the Continuos loop generated
		if (searchOnMap(continuosCartesianPoints, face) != NULL)
		{
			Ifc4::IfcPolyLoop* polySharedLoop = nullptr;
			if (searchOnMap(sharedOpenPolyLoops, face) == NULL)
			{
				auto sharedCartesianPointList = continuosCartesianPoints.at(face);
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(sharedCartesianPointList);
				polySharedLoop = new Ifc4::IfcPolyLoop(polyControlPoints);

				for (auto fID : sharedBoundFaceID)
				{
					//Don't add the one from the face just created
					if(fID != face)
						sharedOpenPolyLoops.insert({ fID, polySharedLoop });
				}
			}
			else
				polySharedLoop = sharedOpenPolyLoops.at(face);

			if(polySharedLoop != nullptr)
				Ifc4::IfcFaceOuterBound* newfaceOuterBound = new Ifc4::IfcFaceOuterBound(polySharedLoop, true);

			continuosCartesianPoints.erase(face);
		}

		//collect all the IfcFaceBound in the list
		boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> faceBoundsList(tempIfcFaceBoundList);

		//Create the face with all the bounds			
		// SameSense: This flag indicates whether the sense of the surface normal agrees with (TRUE), or opposes (FALSE), the sense of the topological normal to the face.
		Ifc4::IfcFace* ifcFace = new Ifc4::IfcFace(faceBoundsList);
		tempIfcFaceList->push(ifcFace);

	}

	//Parse all the solid inside the Faceted BRep
	for (auto solidKernelEntity: bRepGraphicProperties->getSolidEntityVector())
	{
		//Triangulated (NOT SURE ALL) faces to Fill the BRep
		for (auto face : solidKernelEntity->getFacetTriangulated())
		{
			//Create IfcCartesianPoint List 
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cPList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
			for (DPoint3d point : face)
			{
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
				cPList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyCP(cPList);
			Ifc4::IfcPolyLoop* pLoop = new Ifc4::IfcPolyLoop(polyCP);
			Ifc4::IfcFaceOuterBound* facet = new Ifc4::IfcFaceOuterBound(pLoop, false);

			//Create a FaceBound list
			IfcTemplatedEntityList<Ifc4::IfcFaceBound>* trFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();
			trFaceBoundList->push(facet);

			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> trBoundsList(trFaceBoundList);

			//Create the face with all the bounds
			Ifc4::IfcFace* trFace = new Ifc4::IfcFace(trBoundsList);
			tempIfcFaceList->push(trFace);
		}
	}
		
			
	//Collect all the faces created
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> temFacesList(tempIfcFaceList);

	if (bRepGraphicProperties->getBRepTypeEnum() == BRepTypeEnum::SOLID)
	{
		Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(temFacesList);
		Ifc4::IfcFacetedBrep* facetedBrep = new Ifc4::IfcFacetedBrep(closedShell);
		Ifc4::IfcSolidModel* solidModel(facetedBrep);
		geomItem = solidModel;
	}
	else if (bRepGraphicProperties->getBRepTypeEnum() == BRepTypeEnum::SHEET)
	{
		Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(temFacesList);

		IfcEntityList* entityList = new IfcEntityList();
		entityList->push(openShell);
		boost::shared_ptr<IfcEntityList> shellModel(entityList);

		Ifc4::IfcShellBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcShellBasedSurfaceModel(shellModel);
		geomItem = shellBasedSurfaceModel;
	}

#endif

	IfcEntityList* solidEntityList = new IfcEntityList();
	//Parse all the solid inside the Faceted BRep
	for (auto solidKernelEntity : bRepGraphicProperties->getSolidEntityVector())
	{
		IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();

		//Triangulated (NOT SURE ALL) faces to Fill the BRep
		for (auto face : solidKernelEntity->getFacetTriangulated())
		{
			//Create IfcCartesianPoint List 
			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* cPList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
			for (DPoint3d point : face)
			{
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(point);
				cPList->push(cP);
			}

			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyCP(cPList);
			Ifc4::IfcPolyLoop* pLoop = new Ifc4::IfcPolyLoop(polyCP);
			Ifc4::IfcFaceOuterBound* facet = new Ifc4::IfcFaceOuterBound(pLoop, false);

			//Create a FaceBound list
			IfcTemplatedEntityList<Ifc4::IfcFaceBound>* trFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();
			trFaceBoundList->push(facet);

			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> trBoundsList(trFaceBoundList);

			//Create the face with all the bounds
			Ifc4::IfcFace* trFace = new Ifc4::IfcFace(trBoundsList);
			tempIfcFaceList->push(trFace);
		}

		//Collect all the faces created
		boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> temFacesList(tempIfcFaceList);

		if (solidKernelEntity->getBRepTypeEnum() == BRepTypeEnum::SOLID)
		{
			Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(temFacesList);
			solidEntityList->push(closedShell);
		}
		else if (solidKernelEntity->getBRepTypeEnum() == BRepTypeEnum::SHEET)
		{
			Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(temFacesList);
			solidEntityList->push(openShell);
		}
	}

	boost::shared_ptr<IfcEntityList> shellModel(solidEntityList);

	Ifc4::IfcShellBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcShellBasedSurfaceModel(shellModel);
	geomItem = shellBasedSurfaceModel;
	

	return geomItem;
}
#pragma warning (pop)

