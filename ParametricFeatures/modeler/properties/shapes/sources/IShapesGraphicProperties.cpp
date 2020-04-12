#include "../headers/IShapesGraphicProperties.h"


IShapesGraphicProperties::IShapesGraphicProperties(CurvesShapeTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<ICurveGraphicProperties*>();
	this->mNormal = DVec3d();
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
	this->mCurvesBoundaryType = CurvesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum IShapesGraphicProperties::getBoundaryTypeCurvesContainer()
{
	return this->mCurvesBoundaryType;
}

CurvesShapeTypeEnum IShapesGraphicProperties::getCurvesShapeTypeEnum()
{
	return this->mCurvesShapeTypeEnum;
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
