#pragma once

//#include <DgnPlatform/ElementGraphics.h>
#include <DgnPlatform/ElementGeometry.h>
#include "../../../../../common/enums/headers/CurvesTypeEnum.h"

class CurveGraphicProperties
{
public:
	CurveGraphicProperties();

	void setOrder(size_t newOrder);
	int getOrder();

	int getDegree();

	void setIsClosed(bool newIsClosed);
	bool getIsCLosed();

	void setIsSelfIntersect(bool newIsSelfIntersect);
	bool getIsSelfIntersect();

	void setControlPoints(bvector<DPoint3d> newControlPoints);
	bvector<DPoint3d> getControlPoints();

	void setCurvesTypeEnum(std::string newElementDescriptor);
	CurvesTypeEnum::CurvesTypeEnum getCurvesTypeEnum();

private:
	int mDegree;
	int mOrder;
	bool mIsClosed;
	bool mIsSelfIntersect;
	bvector<DPoint3d> mControlPoints;
	CurvesTypeEnum::CurvesTypeEnum mCurvesTypeEnum;
};
