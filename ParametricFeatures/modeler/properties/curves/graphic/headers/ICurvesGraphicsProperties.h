#pragma once

#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../../../common/utils/headers/CurvesTypeEnumUtils.h"

class ICurveGraphicProperties
{
public:

	void setControlPoints(bvector<DPoint3d> newControlPoints) {
		this->mControlPoints = newControlPoints;
	};
	bvector<DPoint3d> getControlPoints() { return mControlPoints; };

	void setCurvesTypeEnum(int curvesBentleyInt) {
		this->mCurvesTypeEnum = CurvesTypeEnumUtils::getCurvesTypeEnumByInt(curvesBentleyInt);
	};
	CurvesTypeEnum getCurvesTypeEnum() { return mCurvesTypeEnum; };

	virtual ~ICurveGraphicProperties() {}; //Needed for dynamic cast at least one virtual function

private:
	bvector<DPoint3d> mControlPoints;
	CurvesTypeEnum mCurvesTypeEnum;
};

