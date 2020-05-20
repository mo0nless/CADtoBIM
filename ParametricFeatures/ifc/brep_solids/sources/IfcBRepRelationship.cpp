#include "../headers/IfcBRepRelationship.h"


IfcBRepRelationship::IfcBRepRelationship()
{

}

void IfcBRepRelationship::processBRepEntityEdge(ShapesGraphicProperties * shapeGraphicProperties, Ifc4::IfcCurve * curveRepresentationItem)
{

	Ifc4::IfcVertexPoint* p0 = new Ifc4::IfcVertexPoint(
		IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(shapeGraphicProperties->getStartPoint())
	);
	Ifc4::IfcVertexPoint* p1 = new Ifc4::IfcVertexPoint(
		IfcOperationsEnhancer::buildIfcCartesianFromCoordsPoint3D(shapeGraphicProperties->getEndPoint())
	);

	Ifc4::IfcVertex* start(p0);
	Ifc4::IfcVertex* end(p1);

	//Check if the Edge is Closed or Continuos
	if (shapeGraphicProperties->getIsClosed())
	{
		//Ifc4::IfcIntersectionCurve()

		/*	IfcEdgeCurve RULES

		1	EdgeStart	IfcVertex	Start point (vertex) of the edge.
		2	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
		*/

		//Set start and end to the same vertex
		Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
			start,
			start,
			curveRepresentationItem,
			true
		);

		// SameSense: 
		// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
		// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
		Ifc4::IfcOrientedEdge* orientedEdge = new Ifc4::IfcOrientedEdge(edgeCurve, true);

		//Create a new SolidEdge
		SolidEdge* solidEdge = new SolidEdge();
		solidEdge->edge = orientedEdge;
		solidEdge->faceID = shapeGraphicProperties->getFacesBoundIDs();
		solidEdge->nodeID = shapeGraphicProperties->getNodeId();
		solidEdge->isClosed = shapeGraphicProperties->getIsClosed();
		solidEdge->ifcCurve = curveRepresentationItem;

		//Push it in the collection
		mSmartSolidEdgesCollection.push_back(solidEdge);
	}

	//It's a continuos edge
	else
	{
		ContinuosEdge* newContinuosEdge = new ContinuosEdge();
		newContinuosEdge->ifcCurve = curveRepresentationItem;
		newContinuosEdge->startDPoint3d = shapeGraphicProperties->getStartPoint();
		newContinuosEdge->endDPoint3d = shapeGraphicProperties->getEndPoint();
		newContinuosEdge->faceID = shapeGraphicProperties->getFacesBoundIDs();
		newContinuosEdge->nodeID = shapeGraphicProperties->getNodeId();

		newContinuosEdge->startVertex = start;
		newContinuosEdge->endVertex = end;
		newContinuosEdge->next = NULL;

		//Push it in the collection
		mContinuosEdgeList.push_back(newContinuosEdge);
	}
}


void IfcBRepRelationship::connectContinuosEdges()
{
	std::vector<ContinuosEdge*> connectedContinuosEdges = std::vector<ContinuosEdge*>();
	std::vector<ContinuosEdge*> newSetContinuosEdges = std::vector<ContinuosEdge*>();

	ContinuosEdge* headEdgeC = NULL;

	//for (auto it = mContinuosEdgeList.begin(); it != mContinuosEdgeList.end(); ++it)
	for (ContinuosEdge* edgeC: mContinuosEdgeList)
	{
		//ContinuosEdge* edgeC = *it;
		if (edgeC != NULL)
		{
			if (headEdgeC == NULL)
			{
				headEdgeC = edgeC;
				//mContinuosEdgeList.erase(it);
			}
			else if (processContinuosEdges(headEdgeC, edgeC))
				continue;
			//mContinuosEdgeList.erase(it);
			else
				newSetContinuosEdges.push_back(edgeC);
		}
		else break;
	}
	
	//Push the connected Edge to the list
	connectedContinuosEdges.push_back(headEdgeC);

	//[??] Double check for connection for 4 edges
	for (auto continuosEdge : connectedContinuosEdges)
	{
		/*	IfcEdgeCurve RULES

		1	EdgeStart	IfcVertex	Start point (vertex) of the edge.
		2	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
		*/
		ContinuosEdge * currentEdge = continuosEdge;
		while (currentEdge != NULL)
		{
			//Set start and end vertex
			Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
				currentEdge->startVertex,
				currentEdge->endVertex,
				currentEdge->ifcCurve,
				true
			);

			// SameSense: 
			// This logical flag indicates whether (TRUE), or not (FALSE) the senses of the edge and the curve defining the edge geometry are the same. 
			// The sense of an edge is from the edge start vertex to the edge end vertex; the sense of a curve is in the direction of increasing parameter.
			Ifc4::IfcOrientedEdge* orientedEdge = new Ifc4::IfcOrientedEdge(edgeCurve, true);

			currentEdge->edge = orientedEdge;

			currentEdge = currentEdge->next;
		}

		//Push it in the collection
		mSmartSolidEdgesCollection.push_back(continuosEdge);
	}

	//Update the global list with the remaining Edges
	mContinuosEdgeList = newSetContinuosEdges;

	//If we didn't connect all the Edges they belong to another ContinuosEdgesCollection
	if (!mContinuosEdgeList.empty())
		connectContinuosEdges();

}

bool IfcBRepRelationship::processContinuosEdges(ContinuosEdge*& head, ContinuosEdge *& newEdge)
{
	bool hadConnection = false;

	//Check if they belongs to the same ENTITY and the same FACE
	if ((head->nodeID == newEdge->nodeID) && (head->faceID == newEdge->faceID))
	{
		// Point temp to start 
		ContinuosEdge * currentEdge = head;
		ContinuosEdge * connectedEdge = NULL;

		bool startConnected, endConnected = false;			

		// Iterate till the loc 
		while (currentEdge != NULL)
		{
			//Check the equality of the Vertex Points of the EDGES
			startConnected = IfcOperationsEnhancer::areTripletsDoubleEqual<DPoint3d>(newEdge->startDPoint3d, currentEdge->endDPoint3d);
			endConnected = IfcOperationsEnhancer::areTripletsDoubleEqual<DPoint3d>(newEdge->endDPoint3d, currentEdge->startDPoint3d);

			if (startConnected) {
				//Connect the START Vertex of the new edge to the END Vertex of the current edge
				newEdge->startVertex = &*currentEdge->endVertex;
				connectedEdge = currentEdge;
			}
			if (endConnected) {
				//Connect the END Vertex of the new edge to the START Vertex of the current edge
				newEdge->endVertex = &*currentEdge->startVertex;
				connectedEdge = currentEdge;
			}

			//Get the next element
			currentEdge = currentEdge->next;

			//Check if there were any connection
			if (startConnected || endConnected)	{
				hadConnection = true;
				if (connectedEdge->next == NULL)
				{
					connectedEdge->next = newEdge;
				}
			}

		}
		
	}

	return hadConnection;
}

std::vector<SolidEdge*> IfcBRepRelationship::getSmartSolidEdgesCollection()
{
	return mSmartSolidEdgesCollection;
}
