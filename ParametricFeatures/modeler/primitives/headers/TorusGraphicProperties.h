#pragma once

#include "SolidPrimitiveProperties.h"


class TorusGraphicProperties: public SolidPrimitiveProperties {

private:
	double _minorRadius;
	double _majorRadius;
	double _sweepRadians;
	DPoint3d _centerPointOfRotation;

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

	string toString();
};