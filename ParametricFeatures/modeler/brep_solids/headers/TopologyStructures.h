#pragma once

#include "../../properties/headers/GraphicProperties.h"
#include <vector>

namespace Modeler
{
	namespace BRepSolids
	{
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
	}
}