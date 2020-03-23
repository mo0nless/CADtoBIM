#include "../headers/SphereGraphicProperties.h"

SphereGraphicProperties::SphereGraphicProperties()
{
	this->mRadius = 0;
}

double SphereGraphicProperties::getRadius()
{
	return this->mRadius;
}

void SphereGraphicProperties::setRadius(double newRadius)
{
	this->mRadius = newRadius;
}
