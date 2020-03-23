#include "../headers/CurveGraphicProperties.h"


CurveGraphicProperties::CurveGraphicProperties()
{
}

void CurveGraphicProperties::setDegree(int newDegree)
{
	this->mDegree = newDegree;
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
