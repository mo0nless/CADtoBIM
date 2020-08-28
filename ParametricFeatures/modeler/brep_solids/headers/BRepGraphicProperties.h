#pragma once

#include "../../properties/headers/GraphicProperties.h"
#include "SolidEntityGraphicProperties.h"
#include <vector>

using namespace std;

class BRepGraphicProperties : public GraphicProperties
{
public:
	BRepGraphicProperties();

	void addSolidEntityGraphicProperties(SolidEntityGraphicProperties* solidGraphic);
	vector<SolidEntityGraphicProperties*> getSolidEntityVector();

	void addVertexLoop(DPoint3d loop);
	vector<DPoint3d> getVertexLoopVector();

	void addNodeIDFaceID(int idN, int idF);
	vector<tuple<int, int>> getNodeIDFaceIDVector();

	void setBRepTypeEnum(int solidBentleyType);
	BRepTypeEnum getBRepTypeEnum();

	void addBoundsPoints(BoundPoints*& newBound);
	vector<BoundPoints*> getBoundsPoints();

private:
	vector<SolidEntityGraphicProperties*> mSolidEntityVector;
	vector<DPoint3d> mVertexLoopVector;
	vector<tuple<int,int>> mFaceIDVector;
	BRepTypeEnum mBRepType;
	vector<BoundPoints*> mBoundsPoint;
};