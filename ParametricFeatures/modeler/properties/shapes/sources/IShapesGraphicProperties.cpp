#include "../headers/IShapesGraphicProperties.h"


IShapesGraphicProperties::IShapesGraphicProperties(ShapesTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<ICurveGraphicProperties*>();
	this->mNormal = DVec3d();
	this->mFaceBoundIdentifier = std::vector<int>();
	this->mNodeId = -1;
}

void IShapesGraphicProperties::insertCurvesGraphicsProperties(ICurveGraphicProperties * newCurveGraphicProperties)
{
	this->mCurvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

std::vector<ICurveGraphicProperties*> IShapesGraphicProperties::getCurvesPrimitivesContainerVector()
{
	return this->mCurvesPrimitivesContainer;
}

void IShapesGraphicProperties::setBoundaryTypeCurvesContainer(int boundaryBentleyType)
{
	this->mCurvesBoundaryType = ShapesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum IShapesGraphicProperties::getBoundaryTypeCurvesContainer()
{
	return this->mCurvesBoundaryType;
}

ShapesTypeEnum IShapesGraphicProperties::getCurvesShapeTypeEnum()
{
	return this->mCurvesShapeTypeEnum;
}

void IShapesGraphicProperties::setFaceBoundID(int newFaceidentifier)
{
	this-> mFaceBoundIdentifier.push_back(newFaceidentifier);
}

std::vector<int> IShapesGraphicProperties::getFacesBoundIDs()
{
	return this->mFaceBoundIdentifier;
}

void IShapesGraphicProperties::setIsFilled(bool value)
{
	this->mIsFilled = value;
}

bool IShapesGraphicProperties::getIsFilled()
{
	return this->mIsFilled;
}

bool IShapesGraphicProperties::getIsClosed() const
{
	return mIsClosed;
}

void IShapesGraphicProperties::setIsClosed(bool isClosed)
{
	this->mIsClosed = isClosed;
}

DVec3d IShapesGraphicProperties::getNormal() const
{
	return this->mNormal;
}

void IShapesGraphicProperties::setNormal(DVec3d normal)
{
	this->mNormal = normal;
}

void IShapesGraphicProperties::setStartEndPoints(DPoint3d start, DPoint3d end)
{
	this->mStartPoint = start;
	this->mEndPoint = end;
}

DPoint3d IShapesGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d IShapesGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}

void IShapesGraphicProperties::setNodeId(int id)
{
	this->mNodeId = id;
}

int IShapesGraphicProperties::getNodeId()
{
	return this->mNodeId;
}

IShapesGraphicProperties::~IShapesGraphicProperties()
{
}
