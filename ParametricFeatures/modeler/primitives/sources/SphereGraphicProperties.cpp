#include "../headers/SphereGraphicProperties.h"

SphereGraphicProperties::SphereGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::SPHERE)
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
