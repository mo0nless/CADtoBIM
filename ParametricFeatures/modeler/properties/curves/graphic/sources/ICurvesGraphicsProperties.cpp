#include "../headers/ICurvesGraphicsProperties.h"

ICurveGraphicProperties::ICurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType)
{
	this->mCurvesTypeEnum = newCurveType;
}

void ICurveGraphicProperties::setControlPoints(bvector<DPoint3d> newControlPoints) 
{
	this->mControlPoints = newControlPoints;
	this->mNumCPoints = (int)newControlPoints.size();
};

bvector<DPoint3d> ICurveGraphicProperties::getControlPoints() 
{ 
	return this->mControlPoints; 
};

CurvesPrimitivesTypeEnum ICurveGraphicProperties::getCurvesTypeEnum() 
{ 
	return mCurvesTypeEnum; 
}
int ICurveGraphicProperties::getNumberControlPoints()
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
