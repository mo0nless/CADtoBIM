#pragma once

#include "SolidPrimitiveProperties.h"

class SphereGraphicProperties : public SolidPrimitiveProperties {

private:
	double _radius;

public:
	SphereGraphicProperties();

	double getRadius();
	void setRadius(double newadius);

	string toString();
};