#include "../headers/ShapesGraphicProperties.h"


ShapesGraphicProperties::ShapesGraphicProperties(ShapesTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<CurveGraphicProperties*>();
	this->mNormal = DVec3d();
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

DVec3d ShapesGraphicProperties::getNormal() const
{
	return this->mNormal;
}

void ShapesGraphicProperties::setNormal(DVec3d normal)
{
	this->mNormal = normal;
}

ShapesGraphicProperties::~ShapesGraphicProperties()
{
}
