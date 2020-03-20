#pragma once

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

class ConeGraphicProperties {

private:
	double mBaseRadius;
	double mTopRadius;
	double mHeight;
	DPoint3d mTopOrigin;
	DPoint3d mBaseOrigin;

public:
	ConeGraphicProperties();

	double getBaseRadius();
	void setBaseRadius(double newBaseRadius);

	double getTopRadius();
	void setTopRadius(double newTopRadius);

	double getHeight();
	void setHeight(double newHeight);

	DPoint3d getTopOrigin();
	void setTopOrigin(DPoint3d newTopOrigin);

	DPoint3d getBaseOrigin();
	void setBaseOrigin(DPoint3d newBaseOrigin);
};