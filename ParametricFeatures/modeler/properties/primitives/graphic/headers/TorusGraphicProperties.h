#pragma once

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

class TorusGraphicProperties {

private:
	double mMinorRadius;
	double mMajorRadius;
	double mSweepRadians;
	DPoint3d centerPointOfRotation;

public:
	TorusGraphicProperties();

	double getMinorRadius();
	void setMinorRadius(double newMinorRadius);

	double getMajorRadius();
	void setMajorRadius(double newMajorRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);
	
	DPoint3d getCenterPointOfRotation();
	void setCenterPointOfRotation(DPoint3d newCenterPointOfRotation);

};