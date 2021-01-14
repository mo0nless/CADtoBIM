#pragma once

#include "../../properties/headers/GraphicProperties.h"
#include <ifcparse\Ifc4.h>
#include <vector>

using namespace Modeler::Properties;

namespace Modeler
{
	namespace Topology
	{
		struct EdgeIfcCurve
		{
			Ifc4::IfcVertex* startVertex;
			Ifc4::IfcVertex* endVertex;
			Ifc4::IfcCartesianPoint* start;
			Ifc4::IfcCartesianPoint* end;
			Ifc4::IfcEdgeCurve* ifcEdgeCurve;
			Ifc4::IfcOrientedEdge* orientedEdge;
			vector<Ifc4::IfcOrientedEdge*> continuosOrientedEdges;
			bool isShared = false;
			vector<int> faceIDs;
			Ifc4::IfcEdgeLoop* edgeLoop;
			bool isSingleCurveClosedPath = false;

			DPoint3d startD3p, endD3p;
		};

		struct BoundPoints
		{
			int boundID;
			bool isClosed = false;
			bool isCreated = false;
			bool isShared;
			vector<int> faceID;
			int nodeID;
			int boundType;

			vector<DPoint3d> pointsVector;
			vector<int> connectedBoundIDs;
		};

		struct MeshTriangles
		{
			vector<vector<DPoint3d>> facesTriangulatedVector;
		};


		struct SolidEdge {
			Ifc4::IfcCurve* ifcCurve;
			vector<int> faceID;
			Ifc4::IfcOrientedEdge* edge = nullptr;

			int type;
			int nodeID;
			bool isClosed = false;
		};

		struct ContinuosEdge : public SolidEdge
		{
			DPoint3d startDPoint3d;
			DPoint3d endDPoint3d;

			Ifc4::IfcVertex* startVertex = nullptr;
			Ifc4::IfcVertex* endVertex = nullptr;

			Ifc4::IfcEdgeLoop* edgeLoop = NULL;

			ContinuosEdge* next = NULL;
		};
	}
}