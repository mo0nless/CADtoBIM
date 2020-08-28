#pragma once

#include "SolidPrimitiveProperties.h"

class SphereGraphicProperties : public SolidPrimitiveProperties {

private:
	double mRadius;

public:
	SphereGraphicProperties();

	double getRadius();
	void setRadius(double newadius);
};