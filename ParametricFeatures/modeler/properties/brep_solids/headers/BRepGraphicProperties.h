#pragma once

#include "../../headers/GraphicProperties.h"
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

	void addFaceID(int id);
	std::vector<int> getFaceIDVector();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();

	void addBoundsPoints(BoundPoints*& newBound);
	std::vector<BoundPoints*> getBoundsPoints();

private:
	std::vector<SolidEntityGraphicProperties*> mSolidEntityVector;
	std::vector<DPoint3d> mVertexLoopVector;
	std::vector<int> mFaceIDVector;
	BRepTypeEnum mBRepType;
	std::vector<BoundPoints*> mBoundsPoint;
};