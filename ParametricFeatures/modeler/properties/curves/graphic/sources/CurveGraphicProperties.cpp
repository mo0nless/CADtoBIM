#include "../headers/CurveGraphicProperties.h"


CurveGraphicProperties::CurveGraphicProperties()
{
	this->mDegree = 0;
	this->mCurvesTypeEnum = CurvesTypeEnum::NONE;
	this->mOrder = 0;
	this->mIsSelfIntersect = false;
}

void CurveGraphicProperties::setOrder(size_t newOrder)
{
	this->mOrder = int(newOrder);
	this->mDegree = mOrder - 1; // A spline function of order N is a piecewise polynomial function of degree N-1 
}

int CurveGraphicProperties::getOrder()
{
	return this->mOrder;
}

int CurveGraphicProperties::getDegree()
{
	return this->mDegree;
}

void CurveGraphicProperties::setIsClosed(bool newIsClosed)
{
	this->mIsClosed = newIsClosed;
}

bool CurveGraphicProperties::getIsCLosed()
{
	return this->mIsClosed;
}

void CurveGraphicProperties::setIsSelfIntersect(bool newIsSelfIntersect)
{
	this->mIsSelfIntersect = newIsSelfIntersect;
}

bool CurveGraphicProperties::getIsSelfIntersect()
{
	return this->mIsSelfIntersect;
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
	this->mControlPoints = newControlPoints;
}

bvector<DPoint3d> CurveGraphicProperties::getControlPoints()
{
	return this->mControlPoints;
}

void CurveGraphicProperties::setCurvesTypeEnum(std::string newElementDescriptor)
{
	this->mCurvesTypeEnum = CurvesTypeEnum::getCurvesTypeEnumByClassName(newElementDescriptor);
}

CurvesTypeEnum::CurvesTypeEnum CurveGraphicProperties::getCurvesTypeEnum()
{
	return this->mCurvesTypeEnum;
}
