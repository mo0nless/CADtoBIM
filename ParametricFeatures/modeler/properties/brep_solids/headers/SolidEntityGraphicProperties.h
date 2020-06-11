#pragma once

#include "../../headers/GraphicProperties.h"
#include <vector>
#include "MSBsplineSurfaceGraphicProperties.h"
#include "../../../../common/utils/headers/BRepTypeEnumUtils.h"


struct BoundPoints
{
	int boundID;
	bool isClosed;
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

	//TODO[SB] Reset to a single one
	void addBSplineSurfaceFace(MSBsplineSurfaceGraphicProperties*& newFace);
	std::vector<MSBsplineSurfaceGraphicProperties*> getBSplineSurfaceFacesVector();
	
	void addFacetTriangulated(std::vector<DPoint3d> face);
	std::vector<std::vector<DPoint3d>> getFacetTriangulated();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();
		
	std::vector<int> faceID;
private:
	std::vector<MSBsplineSurfaceGraphicProperties*> mBrepFaces;
	std::vector<std::vector<DPoint3d>> mFacetTriangulatedVector;
	BRepTypeEnum mBRepType;
};

