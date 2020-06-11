#include "../headers/BRepGraphicProperties.h"


BRepGraphicProperties::BRepGraphicProperties()
{
	this->mSolidEntityVector = std::vector<SolidEntityGraphicProperties*>();
	this->mVertexLoopVector = std::vector<DPoint3d>();
	//this->mFacetTriangulatedVector = std::vector<std::vector<DPoint3d>>();
	this->mFaceIDVector = std::vector<int>();
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

//void BRepGraphicProperties::addFacetTriangulated(std::vector<DPoint3d> face)
//{
//	this->mFacetTriangulatedVector.push_back(face);
//}
//
//std::vector<std::vector<DPoint3d>> BRepGraphicProperties::getFacetTriangulated()
//{
//	return this->mFacetTriangulatedVector;
//}

void BRepGraphicProperties::addFaceID(int id)
{
	this->mFaceIDVector.push_back(id);
}

std::vector<int> BRepGraphicProperties::getFaceIDVector()
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