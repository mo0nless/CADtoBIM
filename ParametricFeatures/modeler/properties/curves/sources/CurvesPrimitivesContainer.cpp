#include "../headers/CurvesPrimitivesContainer.h"


CurvesPrimitivesContainer::CurvesPrimitivesContainer()
{
	this->mCurvesBoundaryType = CurvesBoundaryTypeEnum::NONE_BOUNDARY;
	this->mContainerDescriptorType = CurvesContainerTypeEnum::NONE_CONTAINER;
	this->mIsFilled = false;
	this->mIsClosed = false;
	this->mCurvesPrimitivesContainer = std::vector<ICurveGraphicProperties*>();
	this->mCentroIDxy = DPoint3d();
	this->mArea = 0.0;
	this->mDirectionX = DVec3d();
	this->mDirectionY = DVec3d();
	this->mDirectionZ = DVec3d();
	this->mNormal = DVec3d();

}

void CurvesPrimitivesContainer::insertCurvesGraphicsProperties(ICurveGraphicProperties * newCurveGraphicProperties)
{
	this->mCurvesPrimitivesContainer.push_back(newCurveGraphicProperties);
}

std::vector<ICurveGraphicProperties*> CurvesPrimitivesContainer::getCurvesPrimitivesContainerVector()
{
	return this->mCurvesPrimitivesContainer;
}

void CurvesPrimitivesContainer::setBoundaryTypeCurvesContainer(int boundaryBentleyType)
{
	this->mCurvesBoundaryType = CurvesTypeEnumUtils::getCurvesBoundaryTypeEnumByInt(boundaryBentleyType);
}

CurvesBoundaryTypeEnum CurvesPrimitivesContainer::getBoundaryTypeCurvesContainer()
{
	return this->mCurvesBoundaryType;
}

void CurvesPrimitivesContainer::setElementContainerDescriptor(std::string newElementContainerDescriptor)
{
	this->mContainerDescriptorType = CurvesTypeEnumUtils::getCurvesContainerTypeEnumByDescriptor(newElementContainerDescriptor);
}

CurvesContainerTypeEnum CurvesPrimitivesContainer::getContainerTypeEnum()
{
	return this->mContainerDescriptorType;
}

void CurvesPrimitivesContainer::setIsFilled(bool value)
{
	this->mIsFilled = value;
}

bool CurvesPrimitivesContainer::getIsFilled()
{
	return this->mIsFilled;
}

void CurvesPrimitivesContainer::setArea(double newArea)
{
	this->mArea = newArea;
}

double CurvesPrimitivesContainer::getArea()
{
	return this->mArea;
}

DPoint3d CurvesPrimitivesContainer::getCentroIDxy() const
{
    return mCentroIDxy;
}

void CurvesPrimitivesContainer::setCentroIDxy(DPoint3d mCentroID)
{
    this->mCentroIDxy = mCentroID;
}


bool CurvesPrimitivesContainer::getIsClosed() const
{
    return mIsClosed;
}

void CurvesPrimitivesContainer::setIsClosed(bool isClosed)
{
    this->mIsClosed = isClosed;
}


DVec3d CurvesPrimitivesContainer::getNormal() const
{
    return mNormal;
}

void CurvesPrimitivesContainer::setNormal(DVec3d normal)
{
    this->mNormal = normal;
}

void CurvesPrimitivesContainer::setDirectionXY(DVec3d newDirX, DVec3d newDirY)
{
	this->mDirectionX = newDirX;
	this->mDirectionY = newDirY;
	this->mDirectionZ.CrossProduct(newDirX, newDirY);
}

DVec3d CurvesPrimitivesContainer::getDirectionX()
{
	return this->mDirectionX;
}

DVec3d CurvesPrimitivesContainer::getDirectionY()
{
	return this->mDirectionY;
}

DVec3d CurvesPrimitivesContainer::getDirectionZ()
{
	return this->mDirectionZ;
}

