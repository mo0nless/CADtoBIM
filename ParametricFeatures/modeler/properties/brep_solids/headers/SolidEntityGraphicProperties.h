#pragma once

#include "../../headers/GraphicProperties.h"
#include <vector>
#include "MSBsplineSurfaceGraphicProperties.h"
#include "../../../../common/utils/headers/BRepTypeEnumUtils.h"


struct BoundPoints
{
	int boundID;
	bool isClosed = false;
	bool isCreated = false;
	bool isShared;
	std::vector<int> faceID;
	int nodeID;
	int boundType;

	std::vector<DPoint3d> pointsVector;
	std::vector<int> connectedBoundIDs;
};

class SolidEntityGraphicProperties: public GraphicProperties
{
public:
	SolidEntityGraphicProperties();

	void addSurfaceFace(GraphicProperties*& newFace);
	std::vector<GraphicProperties*> getSurfaceFacesVector();

	void addFaceBoundaryShape(ShapesGraphicProperties* bound);
	std::vector<ShapesGraphicProperties*> getSurfaceBoundaryShapes();
	
	void addFacetTriangulated(std::vector<DPoint3d> face);
	std::vector<std::vector<DPoint3d>> getFacetTriangulated();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();
		
	std::vector<int> faceID;
	std::vector<std::vector<ShapesGraphicProperties*>> loopShapesBounds;

private:
	std::vector<ShapesGraphicProperties*> mFaceBoundaries;
	std::vector<GraphicProperties*> mBrepFaces;
	std::vector<std::vector<DPoint3d>> mFacetTriangulatedVector;
	std::vector<std::tuple<int, int>> mFaceIDVector;
	BRepTypeEnum mBRepType;
};

