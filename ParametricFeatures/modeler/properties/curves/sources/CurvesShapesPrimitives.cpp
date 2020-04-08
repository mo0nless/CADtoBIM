#include "../headers/CurvesShapesPrimitives.h"


CurvesShapesPrimitives::CurvesShapesPrimitives(CurvesShapeTypeEnum newShapeType)
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mCurvesShapeTypeEnum = newShapeType;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<ICurveGraphicProperties*>();
	this->mNormal = DVec3d();

}

void CurvesShapesPrimitives::insertCurvesGraphicsProperties(ICurveGraphicProperties * newCurveGraphicProperties)
{
	this->mCurvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

std::vector<ICurveGraphicProperties*> CurvesShapesPrimitives::getCurvesPrimitivesContainerVector()
{
	return this->mCurvesPrimitivesContainer;
}

void CurvesShapesPrimitives::setBoundaryTypeCurvesContainer(int boundaryBentleyType)
{
	this->mCurvesBoundaryType = CurvesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum CurvesShapesPrimitives::getBoundaryTypeCurvesContainer()
{
	return this->mCurvesBoundaryType;
}

CurvesShapeTypeEnum CurvesShapesPrimitives::getCurvesShapeTypeEnum()
{
	return this->mCurvesShapeTypeEnum;
}

void CurvesShapesPrimitives::setIsFilled(bool value)
{
	this->mIsFilled = value;
}

bool CurvesShapesPrimitives::getIsFilled()
{
	return this->mIsFilled;
}

bool CurvesShapesPrimitives::getIsClosed() const
{
    return mIsClosed;
}

void CurvesShapesPrimitives::setIsClosed(bool isClosed)
{
    this->mIsClosed = isClosed;
}


DVec3d CurvesShapesPrimitives::getNormal() const
{
    return mNormal;
}

void CurvesShapesPrimitives::setNormal(DVec3d normal)
{
    this->mNormal = normal;
}
