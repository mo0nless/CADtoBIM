#pragma once

#include "../../properties/headers/GraphicProperties.h"
#include "SolidEntityGraphicProperties.h"
#include <vector>

class BRepGraphicProperties : public GraphicProperties
{
public:
	BRepGraphicProperties();

	void addSolidEntityGraphicProperties(SolidEntityGraphicProperties* solidGraphic);
	std::vector<SolidEntityGraphicProperties*> getSolidEntityVector();

	void addVertexLoop(DPoint3d loop);
	std::vector<DPoint3d> getVertexLoopVector();

	void addNodeIDFaceID(int idN, int idF);
	std::vector<std::tuple<int, int>> getNodeIDFaceIDVector();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();

	void addBoundsPoints(BoundPoints*& newBound);
	std::vector<BoundPoints*> getBoundsPoints();

private:
	std::vector<SolidEntityGraphicProperties*> mSolidEntityVector;
	std::vector<DPoint3d> mVertexLoopVector;
	std::vector<std::tuple<int,int>> mFaceIDVector;
	BRepTypeEnum mBRepType;
	std::vector<BoundPoints*> mBoundsPoint;
};