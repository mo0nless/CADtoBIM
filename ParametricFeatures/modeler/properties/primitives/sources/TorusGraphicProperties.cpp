#include "../headers/TorusGraphicProperties.h"

TorusGraphicProperties::TorusGraphicProperties()
{
	this->minorRadius = 0;
	this->majorRadius = 0;
	this->sweepRadians = 0;
}

double TorusGraphicProperties::getMinorRadius()
{
	return this->minorRadius;
}

void TorusGraphicProperties::setMinorRadius(double newMinorRadius)
{
	this->minorRadius = newMinorRadius;
}

double TorusGraphicProperties::getMajorRadius()
{
	return this->majorRadius;
}

void TorusGraphicProperties::setMajorRadius(double newMajorRadius)
{
	this->majorRadius = newMajorRadius;
}

double TorusGraphicProperties::getSweepRadians()
{
	return this->sweepRadians;
}

void TorusGraphicProperties::setSweepRadians(double newSweepRadians)
{
	this->sweepRadians = newSweepRadians;
}
