#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/ShapesTypeEnumUtils.h"

class CurveGraphicProperties 
{
public:
	CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void setControlPoints(bvector<DPoint3d> newControlPoints);
	void setControlPoints(std::vector<DPoint3d> newControlPoints);
	std::vector<DPoint3d> getControlPoints();
	CurvesPrimitivesTypeEnum getCurvesTypeEnum();
	void setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint);
	DPoint3d getStartPoint();
	DPoint3d getEndPoint();
	virtual ~CurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	DPoint3d mStartPoint;
	DPoint3d mEndPoint;

	int mNumCPoints;
	std::vector<DPoint3d> mControlPoints;
	CurvesPrimitivesTypeEnum mCurvesTypeEnum;
};

