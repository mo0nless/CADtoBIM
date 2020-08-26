#pragma once

#include "SolidPrimitiveProperty.h"

class SphereGraphicProperties : public SolidPrimitiveProperty {

private:
	double mRadius;

public:
	SphereGraphicProperties();

	double getRadius();
	void setRadius(double newadius);
};