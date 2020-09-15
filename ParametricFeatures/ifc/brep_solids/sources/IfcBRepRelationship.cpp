#include "../headers/IfcBRepRelationship.h"


IfcBRepRelationship::IfcBRepRelationship()
{

}

void IfcBRepRelationship::processBRepEntityEdge(ShapesGraphicProperties * shapeGraphicProperties, vector<Ifc4::IfcCurve*> curveRepresentationVec, int boundType)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

//Bspline Surface Edges as Single preimitives
#if true
	int index = 0;

	for (auto curve : shapeGraphicProperties->getCurvesPrimitivesContainerVector())
	{
		if (index > 0)
			continue;

		//bool closed = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(curve->getStartPoint(), curve->getEndPoint());
		bool closed = shapeGraphicProperties->getIsClosed();

		//Check if the Edge is Closed or Continuos
		if (closed)
		{
			Ifc4::IfcVertexPoint* p0 = new Ifc4::IfcVertexPoint(
				IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(curve->getStartPoint())
			);

			Ifc4::IfcVertex* start(p0);

			/*	IfcEdgeCurve RULES

			1	EdgeStart	IfcVertex	Start point (vertex) of the edge.
			2	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
			*/

			//Set start and end to the same vertex
			Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
				start,
				start,
				curveRepresentationVec[index],
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
			solidEdge->isClosed = true;//shapeGraphicProperties->getIsClosed();
			solidEdge->ifcCurve = curveRepresentationVec[0];
			solidEdge->type = boundType;

			//Push it in the collection
			mSmartSolidEdgesCollection.push_back(solidEdge);
		}

		//It's a continuos edge
		else
		{		
			Ifc4::IfcVertexPoint* p0 = new Ifc4::IfcVertexPoint(
				IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(curve->getStartPoint())
			);
			Ifc4::IfcVertexPoint* p1 = new Ifc4::IfcVertexPoint(
				IfcOperationsHelper::buildIfcCartesian3DfromCoordsPoint3D(curve->getEndPoint())
			);

			Ifc4::IfcVertex* start(p0);
			Ifc4::IfcVertex* end(p1);
			
			ContinuosEdge* newContinuosEdge = new ContinuosEdge();
			newContinuosEdge->ifcCurve = curveRepresentationVec[index];
			newContinuosEdge->startDPoint3d = curve->getStartPoint();
			newContinuosEdge->endDPoint3d = curve->getEndPoint();
			newContinuosEdge->faceID = shapeGraphicProperties->getFacesBoundIDs();
			newContinuosEdge->nodeID = shapeGraphicProperties->getNodeId();

			newContinuosEdge->startVertex = start;
			newContinuosEdge->endVertex = end;
			newContinuosEdge->next = NULL;
			newContinuosEdge->type = boundType;

			//Push it in the collection
			mContinuosEdgeList.push_back(newContinuosEdge);			
		}

		index++;
	}
#endif

#if false

	bool closed = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(shapeGraphicProperties->getStartPoint(), shapeGraphicProperties->getEndPoint());

	//Check if the Edge is Closed or Continuos
	if (closed)
	{
		Ifc4::IfcVertexPoint* p0 = new Ifc4::IfcVertexPoint(
			IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(shapeGraphicProperties->getStartPoint())
		);

		Ifc4::IfcVertex* start(p0);

		/*	IfcEdgeCurve RULES

		1	EdgeStart	IfcVertex	Start point (vertex) of the edge.
		2	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
		*/

		//Set start and end to the same vertex
		Ifc4::IfcEdgeCurve* edgeCurve = new Ifc4::IfcEdgeCurve(
			start,
			start,
			curveRepresentationVec[0],
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
		solidEdge->isClosed = true;//shapeGraphicProperties->getIsClosed();
		solidEdge->ifcCurve = curveRepresentationVec[0];
		solidEdge->type = boundType;

		//Push it in the collection
		mSmartSolidEdgesCollection.push_back(solidEdge);
	}

	//It's a continuos edge
	else
	{
		Ifc4::IfcVertexPoint* p0 = new Ifc4::IfcVertexPoint(
			IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(shapeGraphicProperties->getStartPoint())
		);
		Ifc4::IfcVertexPoint* p1 = new Ifc4::IfcVertexPoint(
			IfcOperationsHelper::buildIfcCartesianFromCoordsPoint3D(shapeGraphicProperties->getEndPoint())
		);

		Ifc4::IfcVertex* start(p0);
		Ifc4::IfcVertex* end(p1);

		ContinuosEdge* newContinuosEdge = new ContinuosEdge();
		newContinuosEdge->ifcCurve = curveRepresentationVec[0];
		newContinuosEdge->startDPoint3d = shapeGraphicProperties->getStartPoint();
		newContinuosEdge->endDPoint3d = shapeGraphicProperties->getEndPoint();
		newContinuosEdge->faceID = shapeGraphicProperties->getFacesBoundIDs();
		newContinuosEdge->nodeID = shapeGraphicProperties->getNodeId();

		newContinuosEdge->startVertex = start;
		newContinuosEdge->endVertex = end;
		newContinuosEdge->next = NULL;
		newContinuosEdge->type = boundType;

		//Push it in the collection
		mContinuosEdgeList.push_back(newContinuosEdge);
	}
#endif
}


void IfcBRepRelationship::connectContinuosEdges()
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

#if false

	vector<ContinuosEdge*> connectedContinuosEdges = vector<ContinuosEdge*>();
	vector<ContinuosEdge*> newSetContinuosEdges = vector<ContinuosEdge*>();

	ContinuosEdge* headEdgeC = NULL;

	for (ContinuosEdge* edgeC: mContinuosEdgeList)
	{
		//ContinuosEdge* edgeC = *it;
		if (edgeC != NULL)
		{
			if (headEdgeC == NULL)
			{
				headEdgeC = edgeC;
			}
			else if (processContinuosEdges(headEdgeC, edgeC))
				continue;
			else
				newSetContinuosEdges.push_back(edgeC);
		}
		else break;
	}
	

	if (headEdgeC != NULL)
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
#endif

	for (ContinuosEdge*& newEdge : mContinuosEdgeList)
	{		
		for (ContinuosEdge*& currentEdge : mContinuosEdgeList)
		{
			bool startConnected, endConnected = false;

			if (newEdge == currentEdge)
				continue;

			//Check the equality of the Vertex Points of the EDGES
			startConnected = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(newEdge->startDPoint3d, currentEdge->endDPoint3d);
			endConnected = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(newEdge->endDPoint3d, currentEdge->startDPoint3d);

			if (startConnected) {
				//Connect the START Vertex of the new edge to the END Vertex of the current edge
				newEdge->startVertex = &*currentEdge->endVertex;
			}
			if (endConnected) {
				//Connect the END Vertex of the new edge to the START Vertex of the current edge
				newEdge->endVertex = &*currentEdge->startVertex;
			}
		}
	}

	for (auto currentEdge : mContinuosEdgeList)
	{
		/*	IfcEdgeCurve RULES

		1	EdgeStart	IfcVertex	Start point (vertex) of the edge.
		2	EdgeEnd		IfcVertex	End point (vertex) of the edge. The same vertex can be used for both EdgeStart and EdgeEnd.
		*/

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
		
		//Push it in the collection
		mSmartSolidEdgesCollection.push_back(currentEdge);
	}
}

bool IfcBRepRelationship::processContinuosEdges(ContinuosEdge*& head, ContinuosEdge *& newEdge)
{
	_logger->logDebug(__FILE__, __LINE__, __FUNCTION__);

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
			startConnected = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(newEdge->startDPoint3d, currentEdge->endDPoint3d);
			endConnected = IfcOperationsHelper::areTripletsDoubleEqual<DPoint3d>(newEdge->endDPoint3d, currentEdge->startDPoint3d);

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

vector<SolidEdge*> IfcBRepRelationship::getSmartSolidEdgesCollection()
{
	return mSmartSolidEdgesCollection;
}
