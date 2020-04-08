#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/CurvesTypeEnumUtils.h"

class ICurveGraphicProperties 
{
public:
	ICurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void setControlPoints(bvector<DPoint3d> newControlPoints);
	bvector<DPoint3d> getControlPoints();
	CurvesPrimitivesTypeEnum getCurvesTypeEnum();
	

	virtual ~ICurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	bvector<DPoint3d> mControlPoints;
	CurvesPrimitivesTypeEnum mCurvesTypeEnum;
};

