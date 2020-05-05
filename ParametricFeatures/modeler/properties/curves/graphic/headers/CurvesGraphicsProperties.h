#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/ShapesTypeEnumUtils.h"

class CurveGraphicProperties 
{
public:
	CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);
	void addControlPoint(DPoint3d newControlPoint);
	std::vector<DPoint3d> getControlPoints();
	CurvesPrimitivesTypeEnum getCurvesTypeEnum();
	int getNumberControlPoints();
	virtual ~CurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	int mNumCPoints;
	std::vector<DPoint3d> controlPoints;
	CurvesPrimitivesTypeEnum mCurvesTypeEnum;
};

