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
				Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = nullptr;
				BRepGraphicProperties* brepSolidsKernelEntity = dynamic_cast<BRepGraphicProperties*>(graphicProperties);
				SolidEntityGraphicProperties* solidsKernelEntity = dynamic_cast<SolidEntityGraphicProperties*>(graphicProperties);

				if (brepSolidsKernelEntity != nullptr)
				{
					ifcRepresentationItem = buildGeometricRepresentationFacetBrep(brepSolidsKernelEntity, ifcElementBundle, file);
				}
				else if (solidsKernelEntity != nullptr)
				{
					ifcRepresentationItem = buildGeometricRepresentationBsplineSurface(solidsKernelEntity, ifcElementBundle, file);
				}

				if (ifcRepresentationItem != nullptr)
				{
					ifcElementBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(graphicProperties, ifcRepresentationItem));
				}
				
			}
		}
	}
}

#if false
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

					Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(tempCP.at(j));
					cartesianPointsUV.push_back(cP);
				}
				tempCartesianPointList->push(cartesianPointsUV);
			}

			//Collect all the UV IfcCartesianPoint for the surface
			boost::shared_ptr<IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>> controlPoints(tempCartesianPointList);


			/*Ifc4::IfcRationalBSplineSurfaceWithKnots* bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
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
			);*/

			/*Ifc4::IfcBSplineSurface* bSplineSurface = new Ifc4::IfcBSplineSurface(
				msBsplineGraphicProperties->getUDegree(),
				msBsplineGraphicProperties->getVDegree(),
				controlPoints,
				Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
				msBsplineGraphicProperties->getUIsCLosed(),
				msBsplineGraphicProperties->getVIsCLosed(),
				msBsplineGraphicProperties->getIsSelfIntersect()
			);*/

			Ifc4::IfcBSplineSurfaceWithKnots* bSplineSurface = new Ifc4::IfcBSplineSurfaceWithKnots(
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
			);

//Curves Edges of te Entity associated with faceID
#if false
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
#endif

//WORKS
#if true 
#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationBsplineSurface(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	IfcElementBundle* elm = new IfcElementBundle(-1, "");

	Ifc4::IfcGeometricRepresentationItem * geomItem = nullptr;

	IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcAdvancedFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();
	IfcEntityList* entityList = new IfcEntityList();

	//buildSolidEntityEdgeLoop(brepSolidsKernelEntity, file);
	
	for (MSBsplineSurfaceGraphicProperties* msBsplineGraphicProperties : brepSolidsKernelEntity->getBSplineSurfaceFacesVector())
	{
		if (msBsplineGraphicProperties != nullptr)
		{
			//Create IfcCartesianPoint List 
			IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>* tempCartesianPointList = new IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>();

			//Create a FaceBound list
			IfcTemplatedEntityList<Ifc4::IfcFaceBound>* tempIfcFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();

			//Get the control point UV of the FACE surface
			std::vector<std::vector<DPoint3d>> controlPointsPatch = msBsplineGraphicProperties->getControlPoints();
			for (auto vCP: controlPointsPatch)
			{
				std::vector<Ifc4::IfcCartesianPoint*> cartesianPointsUV;

				for (auto p: vCP)
				{
					Ifc4::IfcCartesianPoint * crtP = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(p);
					cartesianPointsUV.push_back(crtP);
				}
				tempCartesianPointList->push(cartesianPointsUV);
			}

			//Collect all the UV IfcCartesianPoint for the surface
			boost::shared_ptr<IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>> controlPoints(tempCartesianPointList);

			Ifc4::IfcBSplineSurface* bSplineSurface = nullptr;

			if (msBsplineGraphicProperties->hasValidKnots && msBsplineGraphicProperties->hasValidWeights)
				bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
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
			else if(msBsplineGraphicProperties->hasValidKnots)
				bSplineSurface = new Ifc4::IfcRationalBSplineSurfaceWithKnots(
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
			else
				bSplineSurface = new Ifc4::IfcBSplineSurface(
					msBsplineGraphicProperties->getUDegree(),
					msBsplineGraphicProperties->getVDegree(),
					controlPoints,
					Ifc4::IfcBSplineSurfaceForm::IfcBSplineSurfaceForm_UNSPECIFIED,
					msBsplineGraphicProperties->getUIsCLosed(),
					msBsplineGraphicProperties->getVIsCLosed(),
					msBsplineGraphicProperties->getIsSelfIntersect()
				);

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			bool addToIfcElementBundle = false;
			auto curveShape = msBsplineGraphicProperties->getSurfaceBoundaryShape();
			ifcShapesEnhancer->buildGeometricRepresentationShapes(curveShape, file, elm, addToIfcElementBundle);

			for (auto boundTypeIfcCurve : ifcShapesEnhancer->getCurvesShapeRepresentationVector())
			{
				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* orientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

				Ifc4::IfcCartesianPoint * cpStart = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(boundTypeIfcCurve->start);
				Ifc4::IfcCartesianPoint * cpEnd = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(boundTypeIfcCurve->end);				

				Ifc4::IfcVertexPoint* vpStart = new Ifc4::IfcVertexPoint(
					cpStart
				);
				Ifc4::IfcVertexPoint* vpEnd = new Ifc4::IfcVertexPoint(
					cpEnd
				);
							
				Ifc4::IfcVertex* start(vpStart);
				Ifc4::IfcVertex* end(vpEnd);

				if (IfcOperationsEnhancer::areTripletsDoubleEqual<DPoint3d>(boundTypeIfcCurve->start, boundTypeIfcCurve->end))
					end = start;

				//Ifc4::IfcSurfaceCurve* d = new Ifc4::IfcSurfaceCurve()
				/*	IfcEdgeCurve RULES
				*	1-	EdgeStart	IfcVertex	Start point (vertex) of the edge.
				*	2-	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
				*/
				Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
					start,
					end,
					boundTypeIfcCurve->ifcCurve,
					true
				);

				// SameSense: 
				// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
				// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
				Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);

				//Push the oriented edge
				orientedEdgesList->push(orientedEdgeT);

				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(orientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

				//Orientation: 
				// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
				// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.				
				Ifc4::IfcFaceBound* newfaceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, true);

				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(newfaceOuterBound);
			}
			

#if false			
			bool outerBoundCreated = false;
			for (auto boundTypeIfcCurve : ifcShapesEnhancer->getCurvesShapeRepresentationVector())
			{
				Ifc4::IfcVertexPoint* vpStart = new Ifc4::IfcVertexPoint(
					IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(boundTypeIfcCurve->vecPrimitivesCurves.front()->getStartPoint())
					//IfcOperationsEnhancer::buildIfcCartesian2DfromCoordsPoint3D(boundTypeIfcCurve->start)
				);
				Ifc4::IfcVertexPoint* vpEnd = new Ifc4::IfcVertexPoint(
					IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(boundTypeIfcCurve->vecPrimitivesCurves.front()->getEndPoint())
					//IfcOperationsEnhancer::buildIfcCartesian2DfromCoordsPoint3D(boundTypeIfcCurve->end)
				);

				Ifc4::IfcVertexPoint* startEnd = vpStart;

				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* orientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

				for (size_t i = 0; i < boundTypeIfcCurve->vecPrimitivesCurves.size(); i++)
				{
					auto primitiveCurve = boundTypeIfcCurve->vecPrimitivesCurves[i];
					auto ifcCurve = boundTypeIfcCurve->vecIfcCurves[i];

					Ifc4::IfcVertex* start = nullptr;
					Ifc4::IfcVertex* end = nullptr;

					if (i == 0) //start oriented edge
					{
						Ifc4::IfcVertex* s(vpStart);
						Ifc4::IfcVertex* e(vpEnd);
						start = s;
						end = e;
					}
					else
					{						
						vpStart = vpEnd;

						vpEnd = new Ifc4::IfcVertexPoint(
							IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(primitiveCurve->getEndPoint())
							//IfcOperationsEnhancer::buildIfcCartesian2DfromCoordsPoint3D(boundTypeIfcCurve->end)
						);

						Ifc4::IfcVertex* s(vpStart);
						start = s;

						//Last bound needs to have first vertex as end
						if (i == boundTypeIfcCurve->vecPrimitivesCurves.size()-1)
						{
							Ifc4::IfcVertex* e(startEnd);
							end = e;
						}
						else
						{
							Ifc4::IfcVertex* e(vpEnd);
							end = e;
						}
					}

					/*	IfcEdgeCurve RULES
					*	1-	EdgeStart	IfcVertex	Start point (vertex) of the edge.
					*	2-	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
					*/
					Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
						start,
						end,
						ifcCurve,
						true
					);

					// SameSense: 
					// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
					// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
					Ifc4::IfcOrientedEdge* orientedEdge = new Ifc4::IfcOrientedEdge(edgeCurve, true);
					
					//Push the oriented edge
					orientedEdgesList->push(orientedEdge);
				}

				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(orientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

				Ifc4::IfcFaceBound* newfaceOuterBound = nullptr;
				//Orientation: 
				// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
				// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
				if (boundTypeIfcCurve->boundary == CurvesBoundaryTypeEnum::INNER)
					newfaceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, true);
				else if (boundTypeIfcCurve->boundary == CurvesBoundaryTypeEnum::OUTER)
					if (!outerBoundCreated)
					{
						newfaceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);
						outerBoundCreated = true;
					}
					else
						newfaceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, true);
					

				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(newfaceOuterBound);
							

			}						
#endif

			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> faceBoundsList(tempIfcFaceBoundList);

			//Create the face with all the bounds			
			// SameSense: This flag indicates whether the sense of the surface normal agrees with (TRUE), or opposes (FALSE), 
			// the sense of the topological normal to the face.
			//Ifc4::IfcFaceSurface* advanceFace = new Ifc4::IfcFaceSurface(faceBoundsList, bSplineSurface, true);
			Ifc4::IfcAdvancedFace* advanceFace = new Ifc4::IfcAdvancedFace(faceBoundsList, bSplineSurface, true);

			tempIfcAdvancedFaceList->push(advanceFace);
		}
	}

	//Collect all the faces created
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advancedFaces(tempIfcAdvancedFaceList);

	//Create a closedShell from the advancedFaces list
	Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(advancedFaces);
	//Ifc4::IfcClosedShell* openShell = new Ifc4::IfcClosedShell(advancedFaces);

	entityList->push(openShell);

	boost::shared_ptr<IfcEntityList> shellModel(entityList);

	Ifc4::IfcShellBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcShellBasedSurfaceModel(shellModel);

	//Create the IfcAdvancedBrep
	//Ifc4::IfcAdvancedBrep* advanceBrep = new Ifc4::IfcAdvancedBrep(openShell);
	//Ifc4::IfcFacetedBrep* advanceBrep = new Ifc4::IfcFacetedBrep(closedShell);

	//Ifc4::IfcSolidModel* shellBasedSurfaceModel(advanceBrep);

	geomItem = shellBasedSurfaceModel;

	return geomItem;
}
#pragma warning (pop)
#endif

#if false
#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationBsplineSurface(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	Ifc4::IfcGeometricRepresentationItem * geomItem = nullptr;

	IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcAdvancedFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();
	IfcEntityList* entityList = new IfcEntityList();

	buildSolidEntityEdgeLoop(brepSolidsKernelEntity, file);

	//TODO[SB] entity needs to be checked
	for (MSBsplineSurfaceGraphicProperties* msBsplineGraphicProperties : brepSolidsKernelEntity->getBSplineSurfaceFacesVector())
	{
		msBsplineGraphicProperties->setNumberOfBounds(0);
		for (auto edge : this->solidEdges)
		{
			for (auto id : edge->faceIDs)
			{
				if (id == msBsplineGraphicProperties->getFaceId())
				{
					msBsplineGraphicProperties->setNumberOfBounds(1);// += 1;
				}
			}
		}
	}
	


	for (MSBsplineSurfaceGraphicProperties* msBsplineGraphicProperties : brepSolidsKernelEntity->getBSplineSurfaceFacesVector())
	{
		if (msBsplineGraphicProperties != nullptr)
		{
			//Create IfcCartesianPoint List 
			IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>* tempCartesianPointList = new IfcTemplatedEntityListList<Ifc4::IfcCartesianPoint>();

			//TODO[SB] Check the surface poles
			//Get the control point UV of the FACE surface
			std::vector<std::vector<DPoint3d>> controlPointsPatch = msBsplineGraphicProperties->getControlPoints();
			for (auto vCP : controlPointsPatch)
			{
				std::vector<Ifc4::IfcCartesianPoint*> cartesianPointsUV;

				for (auto p : vCP)
				{
					Ifc4::IfcCartesianPoint * crtP = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(p);
					cartesianPointsUV.push_back(crtP);
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

			//Create a FaceBound list
			IfcTemplatedEntityList<Ifc4::IfcFaceBound>* tempIfcFaceBoundList = new IfcTemplatedEntityList<Ifc4::IfcFaceBound>();

#if true
			for (auto edge : this->solidEdges)
			{
				for (auto id : edge->faceIDs)
				{
					if (id == msBsplineGraphicProperties->getFaceId())
					{
						Ifc4::IfcFaceBound* faceOuterBound = new Ifc4::IfcFaceBound(edge->edgeLoop, true);

						//Add it to the IfcFaceOuterBound List for the currecnt face
						tempIfcFaceBoundList->push(faceOuterBound);

						if (edge->isShared)
						{
							Ifc4::IfcVertexLoop* vLoop = new Ifc4::IfcVertexLoop(edge->startVertex);
							Ifc4::IfcFaceBound* faceBound = new Ifc4::IfcFaceBound(vLoop, true);

							Ifc4::IfcVertexLoop* vLoop2 = new Ifc4::IfcVertexLoop(edge->endVertex);
							Ifc4::IfcFaceBound* faceBound2 = new Ifc4::IfcFaceBound(vLoop2, true);

							tempIfcFaceBoundList->push(faceBound);
							tempIfcFaceBoundList->push(faceBound2);
						}
					}
				}
			}
#endif


#if false
			if (msBsplineGraphicProperties->mNumberOfBounds == 3)
			{
				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* orientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();
				
				std::vector<Ifc4::IfcVertex*> vertexVec;

				//Polyline Curve 3D
				IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* polyCurveEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();					
				
				for (auto edge : this->solidEdges)
				{
					for (auto id : edge->faceIDs)
					{
						if (id == msBsplineGraphicProperties->getFaceId())
						{
							//Inner Bound
							if (!edge->isSingleCurveClosedPath)
							{
								//Orientation: 
								// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
								// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
								Ifc4::IfcFaceBound* newfaceOuterBound = new Ifc4::IfcFaceBound(edge->edgeLoop, true);

								//Add it to the IfcFaceOuterBound List for the currecnt face
								tempIfcFaceBoundList->push(newfaceOuterBound);
							}
							//Outer Bound
							else
							{
								//Push the oriented edge
								orientedEdgesList->push(edge->orientedEdge);
								//set a point for the polyline
								polyCurveEntityList->push(edge->start); //TODO[SB] check Maybe it wants a new instance of cartesian point 
								//Set the vertex point
								vertexVec.push_back(edge->startVertex);
							}
						}
					}
				}

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(polyCurveEntityList);

				Ifc4::IfcPolyline* polyline = new Ifc4::IfcPolyline(polyControlPoints);
				
				//*	IfcEdgeCurve RULES
				//*	1-	EdgeStart	IfcVertex	Start point (vertex) of the edge.
				//*	2-	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
				//*
				Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
					vertexVec[0],
					vertexVec[1],
					polyline,
					true
				);

				// SameSense: 
				// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
				// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
				Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);
				Ifc4::IfcOrientedEdge* orientedEdgeF = new Ifc4::IfcOrientedEdge(edgeCurve, false);

				//Push the oriented edge
				orientedEdgesList->push(orientedEdgeT);
				orientedEdgesList->push(orientedEdgeF);
				
				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(orientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);
				Ifc4::IfcFaceOuterBound* faceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);

				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(faceOuterBound);
			}
			else if (msBsplineGraphicProperties->mNumberOfBounds == 2)
			{
				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* orientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

				std::vector<Ifc4::IfcVertex*> vertexVec;

				//Polyline Curve 3D
				IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* polyCurveEntityList = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();

				for (auto edge : this->solidEdges)
				{
					for (auto id : edge->faceIDs)
					{
						if (id == msBsplineGraphicProperties->getFaceId())
						{
							//Inner Bound
							if (!edge->isSingleCurveClosedPath)
							{
								for (auto oE: edge->sharedOrientedEdge)
									//Push the oriented edge
									orientedEdgesList->push(oE);

								//set a point for the polyline
								polyCurveEntityList->push(edge->start); //TODO[SB] check Maybe it wants a new instance of cartesian point 
																		//Set the vertex point
								vertexVec.push_back(edge->startVertex);
							}
							//Outer Bound
							else
							{
								//Push the oriented edge
								orientedEdgesList->push(edge->orientedEdge);
								//set a point for the polyline
								polyCurveEntityList->push(edge->start); //TODO[SB] check Maybe it wants a new instance of cartesian point 
																		//Set the vertex point
								vertexVec.push_back(edge->startVertex);
							}
						}
					}
				}

				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> polyControlPoints(polyCurveEntityList);

				Ifc4::IfcPolyline* polyline = new Ifc4::IfcPolyline(polyControlPoints);

				//*	IfcEdgeCurve RULES
				//*	1-	EdgeStart	IfcVertex	Start point (vertex) of the edge.
				//*	2-	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
				//*
				Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
					vertexVec[0],
					vertexVec[1],
					polyline,
					true
				);

				// SameSense: 
				// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
				// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
				Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);
				Ifc4::IfcOrientedEdge* orientedEdgeF = new Ifc4::IfcOrientedEdge(edgeCurve, false);

				//Push the oriented edge
				orientedEdgesList->push(orientedEdgeT);
				orientedEdgesList->push(orientedEdgeF);

				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(orientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);
				Ifc4::IfcFaceOuterBound* faceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);

				//Add it to the IfcFaceOuterBound List for the currecnt face
				tempIfcFaceBoundList->push(faceOuterBound);
			}
#endif
			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> faceBoundsList(tempIfcFaceBoundList);
			
			//Create the face with all the bounds			
			// SameSense: This flag indicates whether the sense of the surface normal agrees with (TRUE), or opposes (FALSE), 
			// the sense of the topological normal to the face.
			//Ifc4::IfcFaceSurface* advanceFace = new Ifc4::IfcFaceSurface(faceBoundsList, bSplineSurface, true);
			Ifc4::IfcAdvancedFace* advanceFace = new Ifc4::IfcAdvancedFace(faceBoundsList, bSplineSurface, true);

			tempIfcAdvancedFaceList->push(advanceFace);

			IfcTemplatedEntityList<Ifc4::IfcFace>* ifcAdvancedFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();
			ifcAdvancedFaceList->push(advanceFace);
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advFaces(ifcAdvancedFaceList);
			Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(advFaces);
			entityList->push(openShell);

		}
	}

	//Collect all the faces created
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advancedFaces(tempIfcAdvancedFaceList);

	//Create a closedShell from the advancedFaces list
	//Ifc4::IfcOpenShell* openShell = new Ifc4::IfcOpenShell(advancedFaces);
	//Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(advancedFaces);

	//entityList->push(openShell);

	boost::shared_ptr<IfcEntityList> shellModel(entityList);

	Ifc4::IfcShellBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcShellBasedSurfaceModel(shellModel);

	/*Ifc4::IfcConnectedFaceSet* closedShell = new Ifc4::IfcConnectedFaceSet(advancedFaces);
	IfcTemplatedEntityList<Ifc4::IfcConnectedFaceSet>* cFacesSet = new IfcTemplatedEntityList<Ifc4::IfcConnectedFaceSet>();
	cFacesSet->push(closedShell);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcConnectedFaceSet>> tempConnectedFaces(cFacesSet);
	Ifc4::IfcFaceBasedSurfaceModel* shellBasedSurfaceModel = new Ifc4::IfcFaceBasedSurfaceModel(tempConnectedFaces);*/

	//Create the IfcAdvancedBrep
	//Ifc4::IfcAdvancedBrep* advanceBrep = new Ifc4::IfcAdvancedBrep(closedShell);
	//Ifc4::IfcFacetedBrep* advanceBrep = new Ifc4::IfcFacetedBrep(closedShell);

	//Ifc4::IfcSolidModel* shellBasedSurfaceModel(advanceBrep);

	geomItem = shellBasedSurfaceModel;

	return geomItem;
}
#pragma warning (pop)
#endif

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4101)
#pragma warning( disable : 4189)
Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationFacetBrep(BRepGraphicProperties * bRepGraphicProperties, IfcElementBundle *& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcGeometricRepresentationItem * geomItem = nullptr;

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
				Ifc4::IfcCartesianPoint * cP = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(point);
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

void IfcBRepSolidsEnhancer::buildSolidEntityEdgeLoop(SolidEntityGraphicProperties * brepSolidsKernelEntity, IfcHierarchyHelper<Ifc4>& file)
{
	std::ofstream outfile;
	std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	bool addToIfcElementBundle = false;
	IfcElementBundle* elm = new IfcElementBundle(-1, "");
	
	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;
	outfile << "----Start Edge Processing-----" << std::endl;
	outfile.close();

	for (auto  bound: brepSolidsKernelEntity->getSurfaceBoundaryShapes())
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "Close bound" << std::endl;
		outfile.close();

		bool isShared = false;
		if (bound->getFacesBoundIDs().size() > 1)
			isShared = true;

		auto startP = bound->getStartPoint();
		auto endP = bound->getEndPoint();

		IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
		//ifcShapesEnhancer->dimension = IfcDimensionEnum::dim_2D;
		ifcShapesEnhancer->buildGeometricRepresentationShapes(bound, file, elm, addToIfcElementBundle);

		//Pick the first and only one
		BoundTypeIfcCurve* boundTypeIfcCurve = ifcShapesEnhancer->getCurvesShapeRepresentationVector().front();

		Ifc4::IfcCartesianPoint* p0 = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(bound->getStartPoint());
		Ifc4::IfcCartesianPoint* p1 = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(bound->getEndPoint());

		Ifc4::IfcVertexPoint* vp0 = new Ifc4::IfcVertexPoint(p0);
		Ifc4::IfcVertexPoint* vp1 = new Ifc4::IfcVertexPoint(p1);

		Ifc4::IfcVertex* start(vp0);
		Ifc4::IfcVertex* end(vp1);

		/*	IfcEdgeCurve RULES
		*	1-	EdgeStart	IfcVertex	Start point (vertex) of the edge.
		*	2-	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
		*/
		Ifc4::IfcEdgeCurve* edgeCurve = nullptr;
		Ifc4::IfcCurve* curveIfc = boundTypeIfcCurve->ifcCurve;

		if (bound->getIsClosed())
		{
			// SameSense: 
			// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
			// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
			//Set start and end to the same vertex
			edgeCurve = new Ifc4::IfcEdgeCurve(
				start,
				start,
				curveIfc,
				true
			);

			/*TRUE ORIENTED EDGE*/
			{
				Ifc4::IfcOrientedEdge* orientedEdge = new Ifc4::IfcOrientedEdge(edgeCurve, true);

				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* tempOrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

				//Push the oriented edge
				tempOrientedEdgesList->push(orientedEdge);

				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(tempOrientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

				EdgeIfcCurve* edgeIfcCurve = new EdgeIfcCurve();
				edgeIfcCurve->edgeLoop = edgeLoop;
				edgeIfcCurve->isShared = isShared;
				edgeIfcCurve->faceIDs = bound->getFacesBoundIDs();
				edgeIfcCurve->orientedEdge = orientedEdge;
				edgeIfcCurve->start = p0;
				edgeIfcCurve->end = p1;
				edgeIfcCurve->startVertex = start;
				edgeIfcCurve->endVertex = end;
				edgeIfcCurve->ifcEdgeCurve = nullptr;
				edgeIfcCurve->isSingleCurveClosedPath = true;
				edgeIfcCurve->startD3p = startP;
				edgeIfcCurve->endD3p = endP;

				this->solidEdges.push_back(edgeIfcCurve);
			}

			/*FALSE ORIENTED EDGE*/
			{
				Ifc4::IfcOrientedEdge* orientedEdge = new Ifc4::IfcOrientedEdge(edgeCurve, false);

				//IfcOrientedEdge list
				IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* tempOrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

				//Push the oriented edge
				tempOrientedEdgesList->push(orientedEdge);

				//The edges saved here are continuos 
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(tempOrientedEdgesList);

				//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
				Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

				EdgeIfcCurve* edgeIfcCurve = new EdgeIfcCurve();
				edgeIfcCurve->edgeLoop = edgeLoop;
				edgeIfcCurve->isShared = isShared;
				edgeIfcCurve->faceIDs = bound->getFacesBoundIDs();
				edgeIfcCurve->orientedEdge = orientedEdge;
				edgeIfcCurve->start = p0;
				edgeIfcCurve->end = p1;
				edgeIfcCurve->startVertex = start;
				edgeIfcCurve->endVertex = end;
				edgeIfcCurve->ifcEdgeCurve = nullptr;
				edgeIfcCurve->isSingleCurveClosedPath = true;
				edgeIfcCurve->startD3p = startP;
				edgeIfcCurve->endD3p = endP;

				//this->solidEdges.push_back(edgeIfcCurve);
			}

		}				
	}

	for (auto boundVector : brepSolidsKernelEntity->loopShapesBounds)
	{
		outfile.open(filePath, std::ios_base::app);
		outfile << std::endl;
		outfile << "Continuos bound" << std::endl;
		outfile.close();

		EdgeIfcCurve* true_EdgeIfcCurve = nullptr;
		EdgeIfcCurve* false_EdgeIfcCurve = nullptr;

		//IfcOrientedEdge list
		IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* true_OrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();
		IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* false_OrientedEdgesList = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();

		Ifc4::IfcCartesianPoint* p0 = nullptr;
		Ifc4::IfcCartesianPoint* p1 = nullptr;
		
		Ifc4::IfcVertexPoint* vp0 = nullptr;
		Ifc4::IfcVertexPoint* vp1 = nullptr;
		

		for (auto bound : boundVector)
		{
			bool isShared = false;
			if (bound->getFacesBoundIDs().size() > 1)
				isShared = true;			

			IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
			ifcShapesEnhancer->buildGeometricRepresentationShapes(bound, file, elm, addToIfcElementBundle);

			//Pick the first and only one
			BoundTypeIfcCurve* boundTypeIfcCurve = ifcShapesEnhancer->getCurvesShapeRepresentationVector().front();
			Ifc4::IfcCurve* curveIfc = boundTypeIfcCurve->ifcCurve;

			auto startP = boundTypeIfcCurve->start;
			auto endP = boundTypeIfcCurve->end;

			if (p0 == nullptr)
			{
				p0 = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(startP);
				vp0 = new Ifc4::IfcVertexPoint(p0);
			}

			if (p1 == nullptr)
			{
				p1 = IfcOperationsEnhancer::buildIfcCartesian3DfromCoordsPoint3D(endP);
				vp1 = new Ifc4::IfcVertexPoint(p1);
			}

			Ifc4::IfcVertex* start(vp0);
			Ifc4::IfcVertex* end(vp1);

			if (curveIfc->declaration().is(Ifc4::IfcTrimmedCurve::Class()))
			{
				Ifc4::IfcTrimmedCurve* temp = (Ifc4::IfcTrimmedCurve*)curveIfc;
				curveIfc = temp->BasisCurve();
			}

			Ifc4::IfcEdgeCurve* edgeCurve = nullptr;

			if (true_EdgeIfcCurve == nullptr || false_EdgeIfcCurve == nullptr)
			{
				// SameSense: 
				// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
				// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
				edgeCurve = new Ifc4::IfcEdgeCurve(
					start,
					end,
					curveIfc,
					true
				);

				/*TRUE ORIENTED EDGE*/
				{
					Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);
					true_OrientedEdgesList->push(orientedEdgeT);

					true_EdgeIfcCurve = new EdgeIfcCurve();

					true_EdgeIfcCurve->edgeLoop = nullptr;
					true_EdgeIfcCurve->isShared = isShared;
					true_EdgeIfcCurve->faceIDs = bound->getFacesBoundIDs();

					true_EdgeIfcCurve->continuosOrientedEdges.push_back(orientedEdgeT);

					true_EdgeIfcCurve->start = p0;
					true_EdgeIfcCurve->end = p1;
					true_EdgeIfcCurve->startVertex = start;
					true_EdgeIfcCurve->endVertex = end;
					true_EdgeIfcCurve->ifcEdgeCurve = nullptr;
					true_EdgeIfcCurve->isSingleCurveClosedPath = false;
					true_EdgeIfcCurve->startD3p = startP;
					true_EdgeIfcCurve->endD3p = endP;
				}

				/*FALSE ORIENTED EDGE*/
				{
					Ifc4::IfcOrientedEdge* orientedEdgeF = new Ifc4::IfcOrientedEdge(edgeCurve, false);
					false_OrientedEdgesList->push(orientedEdgeF);

					false_EdgeIfcCurve = new EdgeIfcCurve();

					false_EdgeIfcCurve->edgeLoop = nullptr;
					false_EdgeIfcCurve->isShared = isShared;
					false_EdgeIfcCurve->faceIDs = bound->getFacesBoundIDs();

					false_EdgeIfcCurve->continuosOrientedEdges.push_back(orientedEdgeF);

					false_EdgeIfcCurve->start = p0;
					false_EdgeIfcCurve->end = p1;
					false_EdgeIfcCurve->startVertex = start;
					false_EdgeIfcCurve->endVertex = end;
					false_EdgeIfcCurve->ifcEdgeCurve = nullptr;
					false_EdgeIfcCurve->isSingleCurveClosedPath = false;
					false_EdgeIfcCurve->startD3p = startP;
					false_EdgeIfcCurve->endD3p = endP;
				}

			}
			else
			{
				// SameSense: 
				// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
				// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
				edgeCurve = new Ifc4::IfcEdgeCurve(
					end,
					start,
					curveIfc,
					false
				);

				/*TRUE ORIENTED EDGE*/
				{					
					Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);
					//Ifc4::IfcOrientedEdge* orientedEdgeT = new Ifc4::IfcOrientedEdge(edgeCurve, true);

					true_OrientedEdgesList->push(orientedEdgeT);

					true_EdgeIfcCurve->continuosOrientedEdges.push_back(orientedEdgeT);
				}

				/*FALSE ORIENTED EDGE*/
				{

					Ifc4::IfcOrientedEdge* orientedEdgeF = new Ifc4::IfcOrientedEdge(edgeCurve, false);

					false_OrientedEdgesList->push(orientedEdgeF);

					false_EdgeIfcCurve->continuosOrientedEdges.push_back(orientedEdgeF);
				}
			}

		}
		
		/*TRUE ORIENTED EDGE*/
		{
			//The edges saved here are continuos 
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(true_OrientedEdgesList);

			//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
			Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

			true_EdgeIfcCurve->edgeLoop = edgeLoop;

			this->solidEdges.push_back(true_EdgeIfcCurve);
		}

		/*FALSE ORIENTED EDGE*/
		{
			//The edges saved here are continuos 
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> edgeLoopList(false_OrientedEdgesList);

			//Store them as a single IfcEdgeLoop and define the IfcFaceOuterBound
			Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(edgeLoopList);

			false_EdgeIfcCurve->edgeLoop = edgeLoop;

			//this->solidEdges.push_back(false_EdgeIfcCurve);
		}
	}

	outfile.open(filePath, std::ios_base::app);
	outfile << std::endl;
	outfile << "----End Edge Processing-----" << std::endl;
	outfile.close();
}
#pragma warning (pop)

