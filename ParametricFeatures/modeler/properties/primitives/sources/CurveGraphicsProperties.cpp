#include "../headers/CurveGraphicsProperties.h"


CurveGraphicProperties::CurveGraphicProperties()
{
}

void CurveGraphicProperties::setDegree(int newDegree)
{
	this->degree = newDegree;
}

int CurveGraphicProperties::getDegree()
{
	return this->degree;
}

void CurveGraphicProperties::setIsClosed(bool newIsClosed)
{
	this->isClosed = newIsClosed;
}

bool CurveGraphicProperties::getIsCLosed()
{
	return this->isClosed;
}

void CurveGraphicProperties::setIsSelfIntersect(bool newIsSelfIntersect)
{
	this->isSelfIntersect = newIsSelfIntersect;
}

bool CurveGraphicProperties::getIsSelfIntersect()
{
	return this->isSelfIntersect;
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
	this->controlPoints = newControlPoints;
}

bvector<DPoint3d> CurveGraphicProperties::getControlPoints()
{
	return this->controlPoints;
}
