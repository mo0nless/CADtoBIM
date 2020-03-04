#include "../headers/SphereGraphicProperties.h"

SphereGraphicProperties::SphereGraphicProperties()
{
	this->radius = 0;
}

double SphereGraphicProperties::getRadius()
{
	return this->radius;
}

void SphereGraphicProperties::setRadius(double newRadius)
{
	this->radius = newRadius;
}
