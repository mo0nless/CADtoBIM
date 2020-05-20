#include "../headers/CurvesGraphicsProperties.h"

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
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
int CurveGraphicProperties::getNumberControlPoints()
{
	return this->mNumCPoints;
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
