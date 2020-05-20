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
				BRepSolidsKernelEntity* brepSolidsKernelEntity = dynamic_cast<BRepSolidsKernelEntity*>(graphicProperties);
				if (brepSolidsKernelEntity != nullptr)
				{
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildGeometricRepresentationBsplineSurface(brepSolidsKernelEntity, ifcElementBundle, file);
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

Ifc4::IfcGeometricRepresentationItem * IfcBRepSolidsEnhancer::buildGeometricRepresentationBsplineSurface(BRepSolidsKernelEntity* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file)
{
	IfcTemplatedEntityList<Ifc4::IfcFace>* tempIfcAdvancedFaceList = new IfcTemplatedEntityList<Ifc4::IfcFace>();
	
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

			//Ifc4::IfcCurveBoundedSurface* test;
			//IfcTemplatedEntityList<Ifc4::IfcBoundaryCurve>* boundsCurve = new IfcTemplatedEntityList<Ifc4::IfcBoundaryCurve>();

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
#if true
								//IfcOrientedEdge closed 
								IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>* singleOrientedEdge = new IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>();
								//Push the IfcOrientedEdge to the list
								singleOrientedEdge->push(solidEdge->edge);

								boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcOrientedEdge>> singleEdgeLoop(singleOrientedEdge);

								//Store it as a single IfcEdgeLoop and define the IfcFaceOuterBound
								Ifc4::IfcEdgeLoop* edgeLoop = new Ifc4::IfcEdgeLoop(singleEdgeLoop);
								//Ifc4::IfcFaceOuterBound* faceOuterBound = new Ifc4::IfcFaceOuterBound(edgeLoop, true);

								//Orientation: 
								// This indicated whether (TRUE) or not (FALSE) the loop has the same sense when used to bound the face as when first defined. 
								// If sense is FALSE the senses of all its component oriented edges are implicitly reversed when used in the face.
								Ifc4::IfcFaceBound* faceOuterBound = new Ifc4::IfcFaceBound(edgeLoop, false);

								//Add it to the IfcFaceOuterBound List for the currecnt face
								tempIfcFaceBoundList->push(faceOuterBound);
#endif
#if false
								IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>();
								Ifc4::IfcCompositeCurveSegment* compositeCurveItem = new Ifc4::IfcCompositeCurveSegment(
									Ifc4::IfcTransitionCode::IfcTransitionCode_CONTINUOUS,
									true,
									solidEdge->ifcCurve
								);

								tempEntityList->push(compositeCurveItem);

								boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>> curveShape(tempEntityList);

								Ifc4::IfcBoundaryCurve* item = new Ifc4::IfcBoundaryCurve(
									curveShape,
									false
								);

								boundsCurve->push(item);
#endif
							}
							else
							{
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
							}
							break;
						}
					}
				}
			}

			//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcBoundaryCurve>> boundstest(boundsCurve);
			//test = new Ifc4::IfcCurveBoundedSurface(bSplineSurface, boundstest, true);
			

			//collect all the IfcFaceBound in the list
			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFaceBound>> faceBoundsList(tempIfcFaceBoundList);

			//Create the face with all the bounds
			//Ifc4::IfcAdvancedFace* advanceFace = new Ifc4::IfcAdvancedFace(faceBoundsList, bSplineSurface, true);
			
			// SameSense: This flag indicates whether the sense of the surface normal agrees with (TRUE), or opposes (FALSE), 
			// the sense of the topological normal to the face.
			Ifc4::IfcFaceSurface* advanceFace = new Ifc4::IfcFaceSurface(faceBoundsList, bSplineSurface, true);

			tempIfcAdvancedFaceList->push(advanceFace);			
			
		}
	}

	//Collect all the faces created
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcFace>> advancedFaces(tempIfcAdvancedFaceList);

	//Create a closedShell from the advancedFaces list
	Ifc4::IfcClosedShell* closedShell = new Ifc4::IfcClosedShell(advancedFaces);
	//Ifc4::IfcConnectedFaceSet* closedShell = new Ifc4::IfcConnectedFaceSet(advancedFaces);
		
	//Create the IfcAdvancedBrep
	Ifc4::IfcAdvancedBrep* advanceBrep = new Ifc4::IfcAdvancedBrep(closedShell);
	//Ifc4::IfcFacetedBrep* advanceBrep = new Ifc4::IfcFacetedBrep(closedShell);
	
	//file.addEntity(advanceBrep);
	Ifc4::IfcSolidModel* solidModel(advanceBrep);
	
	Ifc4::IfcGeometricRepresentationItem * geomItem = solidModel;

	return geomItem;
}