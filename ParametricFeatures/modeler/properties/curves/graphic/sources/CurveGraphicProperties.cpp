#include "../headers/CurveGraphicProperties.h"

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
	this->mControlPoints = std::vector<DPoint3d>();
	this->mStartPoint = DPoint3d();
	this->mEndPoint = DPoint3d();
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
	this->mControlPoints.clear();
	for (auto p: newControlPoints)
		this->mControlPoints.push_back(p);
};

std::vector<DPoint3d> CurveGraphicProperties::getControlPoints() 
{ 
	return this->mControlPoints;
};

CurvesPrimitivesTypeEnum CurveGraphicProperties::getCurvesTypeEnum() 
{ 
	return mCurvesTypeEnum; 
}

void CurveGraphicProperties::setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mStartPoint = sPoint;
	this->mEndPoint = ePoint;
}

DPoint3d CurveGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d CurveGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}
