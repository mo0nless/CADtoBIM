#include "../headers/CurvesGraphicsProperties.h"

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
}

void CurveGraphicProperties::addControlPoint(DPoint3d newControlPoint) 
{
	this->controlPoints.push_back(newControlPoint);
};

std::vector<DPoint3d> CurveGraphicProperties::getControlPoints() 
{ 
	return this->controlPoints; 
};

CurvesPrimitivesTypeEnum CurveGraphicProperties::getCurvesTypeEnum() 
{ 
	return mCurvesTypeEnum; 
}
int CurveGraphicProperties::getNumberControlPoints()
{
	return this->mNumCPoints;
}
void ICurveGraphicProperties::setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mStartPoint = sPoint;
	this->mEndPoint = ePoint;
}

DPoint3d ICurveGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d ICurveGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}
