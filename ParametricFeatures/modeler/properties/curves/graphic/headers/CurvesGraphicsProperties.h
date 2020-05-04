#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/ShapesTypeEnumUtils.h"

class CurveGraphicProperties 
{
public:
	CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void setControlPoints(bvector<DPoint3d> newControlPoints);
	bvector<DPoint3d> getControlPoints();
	CurvesPrimitivesTypeEnum getCurvesTypeEnum();
	int getNumberControlPoints();
	virtual ~CurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	int mNumCPoints;
	bvector<DPoint3d> mControlPoints;
	CurvesPrimitivesTypeEnum mCurvesTypeEnum;
};

