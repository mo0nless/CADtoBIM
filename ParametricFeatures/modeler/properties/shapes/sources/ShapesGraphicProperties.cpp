#include "../headers/ShapesGraphicProperties.h"


ShapesGraphicProperties::ShapesGraphicProperties(ShapesTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<CurveGraphicProperties*>();
	this->mShapesGraphicsContainer = std::vector<ShapesGraphicProperties*>();
	this->mHasShapesGraphicsContainer = false;
	this->mIsSingleCurve = false;
	this->mNormal = DVec3d();
	this->mFaceBoundIdentifier = std::vector<int>();
	this->mNodeId = -1;
}

void ShapesGraphicProperties::insertCurvesGraphicsProperties(CurveGraphicProperties * newCurveGraphicProperties)
{
	this->mCurvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

std::vector<CurveGraphicProperties*> ShapesGraphicProperties::getCurvesPrimitivesContainerVector()
{
	return this->mCurvesPrimitivesContainer;
}

void ShapesGraphicProperties::setBoundaryTypeCurvesContainer(int boundaryBentleyType)
{
	this->mCurvesBoundaryType = ShapesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum ShapesGraphicProperties::getBoundaryTypeCurvesContainer()
{
	return this->mCurvesBoundaryType;
}

ShapesTypeEnum ShapesGraphicProperties::getCurvesShapeTypeEnum()
{
	return this->mCurvesShapeTypeEnum;
}

void ShapesGraphicProperties::setFaceBoundID(int newFaceidentifier)
{
	this-> mFaceBoundIdentifier.push_back(newFaceidentifier);
}

std::vector<int> ShapesGraphicProperties::getFacesBoundIDs()
{
	return this->mFaceBoundIdentifier;
}

void ShapesGraphicProperties::setIsFilled(bool value)
{
	this->mIsFilled = value;
}

bool ShapesGraphicProperties::getIsFilled()
{
	return this->mIsFilled;
}

bool ShapesGraphicProperties::getIsClosed() const
{
	return mIsClosed;
}

void ShapesGraphicProperties::setIsClosed(bool isClosed)
{
	this->mIsClosed = isClosed;
}

bool ShapesGraphicProperties::hasShapesGraphicsContainer() const
{
	return this->mHasShapesGraphicsContainer;
}

std::vector<ShapesGraphicProperties*> ShapesGraphicProperties::getShapesGraphicsContainer()
{
	return this->mShapesGraphicsContainer;
}

DVec3d ShapesGraphicProperties::getNormal() const
{
	return this->mNormal;
}

void ShapesGraphicProperties::setNormal(DVec3d normal)
{
	this->mNormal = normal;
}

void ShapesGraphicProperties::setStartEndPoints(DPoint3d start, DPoint3d end)
{
	this->mStartPoint = start;
	this->mEndPoint = end;
}

DPoint3d ShapesGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d ShapesGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}

void ShapesGraphicProperties::setNodeId(int id)
{
	this->mNodeId = id;
}

int ShapesGraphicProperties::getNodeId()
{
	return this->mNodeId;
}

void ShapesGraphicProperties::setCentroid(DPoint3d newCenter)
{
	this->mCentroid = newCenter;
}

DPoint3d ShapesGraphicProperties::getCentroid()
{
	return this->mCentroid;
}

bool ShapesGraphicProperties::getHasSingleCurve()
{
	return this->mIsSingleCurve;
}

void ShapesGraphicProperties::setHasSingleCurve(bool value)
{
	this->mIsSingleCurve = value;
}

void ShapesGraphicProperties::insertShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->mShapesGraphicsContainer.push_back(newShapesGraphicProperties);
	this->mHasShapesGraphicsContainer = true;
}

ShapesGraphicProperties::~ShapesGraphicProperties()
{
}
