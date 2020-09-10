#pragma once


#include "SolidPrimitiveProperties.h"

class CylinderGraphicProperties:public SolidPrimitiveProperties {

private:
	double _radius;
	double _height;
	DPoint3d _baseOrigin;

public:
	CylinderGraphicProperties();

	double getRadius();
	void setRadius(double newRadius);

	double getHeight();
	void setHeight(double newHeight);

	DPoint3d getBaseOrigin();
	void setBaseOrigin(DPoint3d newBaseOrigin);

	string toString();
};