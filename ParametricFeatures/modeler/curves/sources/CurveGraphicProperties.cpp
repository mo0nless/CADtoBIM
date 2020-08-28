#include "../headers/CurveGraphicProperties.h"

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
	this->mControlPoints = vector<DPoint3d>();
	this->mUVcontrolPoints = vector<DPoint3d>();
	this->mStartPoint = DPoint3d();
	this->mEndPoint = DPoint3d();
	this->mUVstartPoint = DPoint3d();
	this->mUVendPoint = DPoint3d();
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints)
{
	if(!this->mControlPoints.empty())
		this->mControlPoints.clear();
	for (auto p: newControlPoints)
		this->mControlPoints.push_back(p);
}
void CurveGraphicProperties::setControlPoints(vector<DPoint3d> newControlPoints)
{
	this->mControlPoints = newControlPoints;
}


vector<DPoint3d> CurveGraphicProperties::getControlPoints() 
{ 
	return this->mControlPoints;
}
void CurveGraphicProperties::setUVcontrolPoints(vector<DPoint3d> newControlPoints)
{
	this->mUVcontrolPoints = newControlPoints;
}

vector<DPoint3d> CurveGraphicProperties::getUVcontrolPoints()
{
	return this->mUVcontrolPoints;
}


CurvesPrimitivesTypeEnum CurveGraphicProperties::getCurvesTypeEnum() 
{ 
	return mCurvesTypeEnum; 
}

void CurveGraphicProperties::setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mStartPoint = sPoint;
	this->mEndPoint = ePoint;
}

void CurveGraphicProperties::setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint)
{
	this->mUVstartPoint = sPoint;
	this->mUVendPoint = ePoint;
}

DPoint3d CurveGraphicProperties::getUVstartPoint()
{
	return this->mUVstartPoint;
}

DPoint3d CurveGraphicProperties::getUVendPoint()
{
	return this->mUVendPoint;
}

DPoint3d CurveGraphicProperties::getStartPoint()
{
	return this->mStartPoint;
}

DPoint3d CurveGraphicProperties::getEndPoint()
{
	return this->mEndPoint;
}
