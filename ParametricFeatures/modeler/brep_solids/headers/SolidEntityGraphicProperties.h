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

class SolidEntityGraphicProperties: public GraphicProperties
{
public:
	SolidEntityGraphicProperties();

	void addSurfaceFace(GraphicProperties*& newFace);
	vector<GraphicProperties*> getSurfaceFacesVector();

	void addFaceBoundaryShape(ShapesGraphicProperties* bound);
	vector<ShapesGraphicProperties*> getSurfaceBoundaryShapes();
	
	void addFacetTriangulated(vector<DPoint3d> face);
	vector<vector<DPoint3d>> getFacetTriangulated();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();
		
	vector<int> faceID;
	vector<vector<ShapesGraphicProperties*>> loopShapesBounds;

private:
	vector<ShapesGraphicProperties*> mFaceBoundaries;
	vector<GraphicProperties*> mBrepFaces;
	vector<vector<DPoint3d>> mFacetTriangulatedVector;
	vector<tuple<int, int>> mFaceIDVector;
	BRepTypeEnum mBRepType;
};

