#pragma once

#include "SolidPrimitiveProperty.h"


class TorusGraphicProperties: public SolidPrimitiveProperty {

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