#include "../headers/BRepGraphicProperties.h"


BRepGraphicProperties::BRepGraphicProperties()
{
	this->mSolidEntityVector = std::vector<SolidEntityGraphicProperties*>();
	this->mVertexLoopVector = std::vector<DPoint3d>();
	//this->mFacetTriangulatedVector = std::vector<std::vector<DPoint3d>>();
	this->mFaceIDVector = std::vector<std::tuple<int, int>>();
}

void BRepGraphicProperties::addSolidEntityGraphicProperties(SolidEntityGraphicProperties * solidGraphic)
{
	this->mSolidEntityVector.push_back(solidGraphic);
}

std::vector<SolidEntityGraphicProperties*> BRepGraphicProperties::getSolidEntityVector()
{
	return this->mSolidEntityVector;
}

void BRepGraphicProperties::addVertexLoop(DPoint3d loop)
{
	this->mVertexLoopVector.push_back(loop);
}

std::vector<DPoint3d> BRepGraphicProperties::getVertexLoopVector()
{
	return this->mVertexLoopVector;
}

void BRepGraphicProperties::addNodeIDFaceID(int idN, int idF)
{
	std::tuple<int, int> idNodeFace = { idN, idF };
	this->mFaceIDVector.push_back(idNodeFace);
}

std::vector<std::tuple<int, int>> BRepGraphicProperties::getNodeIDFaceIDVector()
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

std::vector<BoundPoints*> BRepGraphicProperties::getBoundsPoints()
{
	return this->mBoundsPoint;
}