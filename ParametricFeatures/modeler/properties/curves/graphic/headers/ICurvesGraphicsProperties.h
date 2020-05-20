#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/ShapesTypeEnumUtils.h"

class ICurveGraphicProperties 
{
public:
	ICurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void setControlPoints(bvector<DPoint3d> newControlPoints);
	bvector<DPoint3d> getControlPoints();
	CurvesPrimitivesTypeEnum getCurvesTypeEnum();
	int getNumberControlPoints();
	void setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint);
	DPoint3d getStartPoint();
	DPoint3d getEndPoint();
	virtual ~ICurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	DPoint3d mStartPoint;
	DPoint3d mEndPoint;

	int mNumCPoints;
	bvector<DPoint3d> mControlPoints;
	CurvesPrimitivesTypeEnum mCurvesTypeEnum;
};

