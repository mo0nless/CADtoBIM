#include "../headers/ShapesGraphicProperties.h"


ShapesGraphicProperties::ShapesGraphicProperties(ShapesTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = vector<CurveGraphicProperties*>();
	this->mShapesGraphicsContainer = vector<ShapesGraphicProperties*>();
	this->mHasShapesGraphicsContainer = false;
	this->mIsSingleCurve = false;
	this->mNormal = DVec3d();
	this->mFaceBoundIdentifier = vector<int>();
	this->mNodeId = -1;
}

void ShapesGraphicProperties::insertCurvesGraphicsProperties(CurveGraphicProperties * newCurveGraphicProperties)
{
	this->mCurvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

vector<CurveGraphicProperties*> ShapesGraphicProperties::getCurvesPrimitivesContainerVector()
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

void ShapesGraphicProperties::addFaceBoundID(int newFaceidentifier)
{
	this-> mFaceBoundIdentifier.push_back(newFaceidentifier);
}

vector<int> ShapesGraphicProperties::getFacesBoundIDs()
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

vector<ShapesGraphicProperties*> ShapesGraphicProperties::getShapesGraphicsContainer()
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

void ShapesGraphicProperties::setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mUVstartPoint = sPoint;
	this->mUVendPoint = ePoint;
}

DPoint3d ShapesGraphicProperties::getUVstartPoint()
{
	return this->mUVstartPoint;
}

DPoint3d ShapesGraphicProperties::getUVendPoint()
{
	return this->mUVendPoint;
}

void ShapesGraphicProperties::setNodeId(int id)
{
	this->mNodeId = id;
}

int ShapesGraphicProperties::getNodeId()
{
	return this->mNodeId;
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
