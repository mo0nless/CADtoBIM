#pragma once

//#include <DgnPlatform/DgnECInstance.h>
//#include <DgnPlatform/DgnECManager.h>
//
//USING_NAMESPACE_BENTLEY_ECOBJECT;
//USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include "SolidPrimitiveProperty.h"

class CylinderGraphicProperties:public SolidPrimitiveProperty {

private:
	double mRadius;
	double mHeight;
	DPoint3d baseOrigin;

public:
	CylinderGraphicProperties(PrimitiveTypeEnum newPrimitiveTypeEnum);

	double getRadius();
	void setRadius(double newRadius);

	double getHeight();
	void setHeight(double newHeight);

	DPoint3d getBaseOrigin();
	void setBaseOrigin(DPoint3d newBaseOrigin);
};