#pragma once


#include "SolidPrimitiveProperty.h"

class CylinderGraphicProperties:public SolidPrimitiveProperty {

private:
	double mRadius;
	double mHeight;
	DPoint3d baseOrigin;

public:
	CylinderGraphicProperties();

	double getRadius();
	void setRadius(double newRadius);

	double getHeight();
	void setHeight(double newHeight);

	DPoint3d getBaseOrigin();
	void setBaseOrigin(DPoint3d newBaseOrigin);
};