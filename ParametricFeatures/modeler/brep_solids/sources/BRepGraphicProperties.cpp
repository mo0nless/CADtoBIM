#include "../headers/BRepGraphicProperties.h"


BRepGraphicProperties::BRepGraphicProperties()
{
	this->mSolidEntityVector = vector<SolidEntityGraphicProperties*>();
	this->mVertexLoopVector = vector<DPoint3d>();
	//this->mFacetTriangulatedVector = vector<vector<DPoint3d>>();
	this->mFaceIDVector = vector<tuple<int, int>>();
}

void BRepGraphicProperties::addSolidEntityGraphicProperties(SolidEntityGraphicProperties * solidGraphic)
{
	this->mSolidEntityVector.push_back(solidGraphic);
}

vector<SolidEntityGraphicProperties*> BRepGraphicProperties::getSolidEntityVector()
{
	return this->mSolidEntityVector;
}

void BRepGraphicProperties::addVertexLoop(DPoint3d loop)
{
	this->mVertexLoopVector.push_back(loop);
}

vector<DPoint3d> BRepGraphicProperties::getVertexLoopVector()
{
	return this->mVertexLoopVector;
}

void BRepGraphicProperties::addNodeIDFaceID(int idN, int idF)
{
	tuple<int, int> idNodeFace = { idN, idF };
	this->mFaceIDVector.push_back(idNodeFace);
}

vector<tuple<int, int>> BRepGraphicProperties::getNodeIDFaceIDVector()
{
	return this->mFaceIDVector;
}

void BRepGraphicProperties::setBRepTypeEnum(int solidBentleyType)
{
	this->mBRepType = BRepTypeEnumUtils::getBRepTypeEnumByInt(solidBentleyType);
}

BRepTypeEnum BRepGraphicProperties::getBRepTypeEnum()
{
	return this->mBRepType;
}

void BRepGraphicProperties::addBoundsPoints(BoundPoints *& newBound)
{
	this->mBoundsPoint.push_back(newBound);
}

vector<BoundPoints*> BRepGraphicProperties::getBoundsPoints()
{
	return this->mBoundsPoint;
}