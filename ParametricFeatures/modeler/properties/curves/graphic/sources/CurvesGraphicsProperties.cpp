#include "../headers/CurvesGraphicsProperties.h"

CurveGraphicProperties::CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
}

void CurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints) 
{
	this->mControlPoints = newControlPoints;
	this->mNumCPoints = (int)newControlPoints.size();
};

bvector<DPoint3d> CurveGraphicProperties::getControlPoints() 
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
;