#pragma once

#include "../../properties/headers/GraphicProperties.h"
#include <vector>
#include "MSBsplineSurfaceGraphicProperties.h"
#include "../../../common/utils/headers/BRepTypeEnumUtils.h"

using namespace std;

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

class SolidEntityGraphicProperties: public GraphicProperties
{
public:
	SolidEntityGraphicProperties();

	void addSolidOrSurfaceFace(GraphicProperties*& newFace);
	vector<GraphicProperties*> getSurfaceFacesVector();

	void addFaceBoundaryShape(ShapesGraphicProperties* bound);
	vector<ShapesGraphicProperties*> getSurfaceBoundaryShapes();
	
	void addMeshTriangulated(MeshTriangles* mesh);
	vector<MeshTriangles*> getMeshTriangulated();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();
		
	vector<int> faceID;
	vector<vector<ShapesGraphicProperties*>> loopShapesBounds;

	bool meshProcessing = false;

private:
	vector<ShapesGraphicProperties*> mFaceBoundaries;
	vector<GraphicProperties*> mBrepFaces;
	vector<MeshTriangles*> mMeshTriangulatedVector;
	vector<tuple<int, int>> mFaceIDVector;
	BRepTypeEnum mBRepType;
};

